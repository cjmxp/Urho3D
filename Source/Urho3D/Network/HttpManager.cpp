#include "HttpManager.h"

#include "../Core/CoreEvents.h"
#include "../Network/Network.h"
#include "../IO/File.h"
#include "../Network/TcpEvt.h"


namespace Urho3D
{

HttpManager::HttpManager(Context * c)
    : Object(c)
{
    SubscribeToEvent(E_BEGINFRAME, URHO3D_HANDLER(HttpManager, HandleBeginFrame));
}

HttpBuffer* HttpManager::Get(const String& url)
{
    SharedPtr<HttpBuffer> reques = SharedPtr<HttpBuffer>(new HttpBuffer(GetContext()));
    reques->SetUrl(url);
    quene_.Push(reques);
    return reques.Get();
}

HttpBuffer* HttpManager::SycGet(const String& url)
{
    SharedPtr<HttpBuffer> reques = SharedPtr<HttpBuffer>(new HttpBuffer(GetContext()));
    reques->SetUrl(url);
    quene_.Push(reques);
    return reques.Get();
}

void HttpManager::SendError(const String& msg) {
    using namespace RequestErr;

    VariantMap& eventData = GetEventDataMap();

    eventData[P_MSG] = msg;

    SendEvent(E_REQUESTERR, eventData);
}

void HttpManager::HandleBeginFrame(StringHash eventType, VariantMap& eventData)
{
    
    for (List<SharedPtr<HttpBuffer> >::Iterator it = quene_.Begin(); it != quene_.End(); ) {
        SharedPtr<HttpBuffer>& http = *it;
        const String& state = http->GetState();
        if(state=="Loading" || state=="Init"){
            http->Load();
        }
        else if(state=="Close")
        {
            
        }
        else if(state=="Ok")
        {
            
        }
        else if(state=="Free")
        {
            it = quene_.Erase(it);
            continue;
        }else{
            
            
        }
        it++;
        /*
        bool remove = false;

        if (info->request_->GetState() == HTTP_ERROR) {
            SendError(info->request_->GetError());
            remove = true;
        }
        else if (info->request_->IsEof()) {
            using namespace RequestOK;

            VariantMap& eventData = GetEventDataMap();

            eventData[P_REQUEST] = (HttpRequest*)info->request_.Get();

            if (info->type_ == GET) {
                VectorBuffer* buffer = (VectorBuffer*)info->serializer_;
                buffer->Seek(0);
                eventData[P_BUFFER] = buffer;
            }
            else {
                eventData[P_FILEPATH] = info->filepath_;
            }

            SendEvent(E_REQUESTOK, eventData);

            remove = true;
        }
        else {
            unsigned sz = info->request_->GetAvailableSize();

            if (sz != 0) {
                info->tempBuffer_.Clear();
                info->tempBuffer_.Resize(sz);

                info->request_->Read(info->tempBuffer_.GetModifiableData(), sz);
                info->serializer_->Write(info->tempBuffer_.GetData(), sz);
            }
        }

        if (remove) {
            info.Reset();
            it = quene_.Erase(it);
        }
        else {
            it++;
        }*/
    }
}

}
