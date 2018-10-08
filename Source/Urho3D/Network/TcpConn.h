#pragma once

#include "../Core/Object.h"
#include "../Core/Thread.h"
#include "../Core/Mutex.h"
#include "../Container/List.h"

namespace Urho3D
{

class TcpMsg;
class TCPClass;

class URHO3D_API TcpConn : public Object, public Thread
{
    URHO3D_OBJECT(TcpConn, Object);

public:
    static void StartUp();
    static void ShutDown();

    TcpConn(Context * c);
    ~TcpConn();

    virtual void ThreadFunction();

    static void RegisterObject(Context * context);
    
    bool Connect(const String& host, const int port);
    void Disconnect();
    void Send(const char* buffer, unsigned int size);

private:
    void SendError(const String & error);
    void HandleBeginFrame(StringHash eventType, VariantMap& eventData);

private:
    bool shutdown_;
    String host_;
    int port_;
    TCPClass* socket_;
    Mutex recvMutex_;
    List<SharedPtr<TcpMsg>> recvChain_;
};

}