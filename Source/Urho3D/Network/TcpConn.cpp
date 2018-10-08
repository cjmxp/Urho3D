#include "TcpConn.h"
#include "../IO/MemoryBuffer.h"
#include "../IO/VectorBuffer.h"

#include "../Core/Context.h"
#include "../Core/CoreEvents.h"
#include "../Core/Timer.h"
#include "../NetWork/TcpEvt.h"

#include "SDL/SDL_stdinc.h"
#include "SDL/SDL_net.h"


namespace Urho3D
{

enum {
    T_DATA = 0,
    T_ERR = 1,
    T_CONNECTED = 2,
};

class TCPClass
{
public:
    TCPsocket socket;
};

class TcpMsg : public RefCounted {
public:
    TcpMsg(const String& err) : 
        buffer(err.CString(), err.Length()),
        messageType(T_ERR)
    {
    }

    TcpMsg(const VectorBuffer& b) : 
        buffer(b),
        messageType(T_DATA)
    {
    }

    TcpMsg(int type) :
        messageType(type)
    {
    }

    VectorBuffer buffer;
    int messageType;
};

void TcpConn::StartUp()
{
    SDLNet_Init();
}

void TcpConn::ShutDown()
{
    SDLNet_Quit();
}

TcpConn::TcpConn(Context * c) :
    Object(c),
    shutdown_(false)
{

    socket_ = new(TCPClass);

    SubscribeToEvent(E_BEGINFRAME, URHO3D_HANDLER(TcpConn, HandleBeginFrame));
}

TcpConn::~TcpConn()
{
    Disconnect();
    delete socket_;
}

void TcpConn::HandleBeginFrame(StringHash eventType, VariantMap& eventData) {
    MutexLock lock(recvMutex_);

    if (recvChain_.Size() > 0) {
        SharedPtr<TcpMsg> msg(recvChain_.Front());
        recvChain_.PopFront();

        VariantMap& eventData = GetEventDataMap();

        switch (msg->messageType) {

        case T_DATA: 
        {
            using namespace TcpData;

            eventData[P_DATA] = &msg->buffer;
            SendEvent(E_TCPDATA, eventData);
            break;
        }
        case T_ERR:
        {
            using namespace TcpErr;
            eventData[P_ERROR] = String((const char*)msg->buffer.GetData(), msg->buffer.GetSize());
            SendEvent(E_TCPDATA, eventData);
        }
        case T_CONNECTED:
        {
            using namespace TcpConnected;
            SendEvent(E_TCPCONNECTED, eventData);
        }
        }
    }
}

bool TcpConn::Connect(const String& host, const int port) {
    this->host_ = host;
    this->port_ = port;
    
    return this->Run();
}

void TcpConn::Disconnect() {
    SDLNet_TCP_Close(socket_->socket);

    shutdown_ = true;

    Stop();
}

void TcpConn::Send(const char* buffer, unsigned int size) {
    SDLNet_TCP_Send(socket_->socket, buffer, size);
}

void TcpConn::SendError(const String& err) {
    MutexLock lock(recvMutex_);
    SharedPtr<TcpMsg> msg(new TcpMsg(err));
    recvChain_.Push(msg);
}


void TcpConn::ThreadFunction() {

    IPaddress addr;
    if (SDLNet_ResolveHost(&addr, host_.CString(), port_) != 0) {
        SendError(SDLNet_GetError());
        return;
    }

    socket_->socket = SDLNet_TCP_Open(&addr);
    if (socket_->socket == nullptr) {
        SendError(SDLNet_GetError());
        return;
    }

    recvMutex_.Acquire();
    recvChain_.Push(SharedPtr<TcpMsg>(new TcpMsg(T_CONNECTED)));
    recvMutex_.Release();

    Uint16 packageSize = 0;

    while (true) {
        if (shutdown_)
            break;

        if (SDLNet_TCP_Recv(socket_->socket, &packageSize, sizeof(packageSize)) > 0) {
            VectorBuffer buffer;

            buffer.Clear();
            buffer.Resize(packageSize);

            SDLNet_TCP_Recv(socket_->socket, buffer.GetModifiableData(), packageSize);

            recvMutex_.Acquire();
            recvChain_.Push(SharedPtr<TcpMsg>(new TcpMsg(buffer)));
            recvMutex_.Release();
        }

        Time::Sleep(0);
    }
}

void TcpConn::RegisterObject(Context* context)
{
    context->RegisterFactory<TcpConn>("TcpConn");
}
}