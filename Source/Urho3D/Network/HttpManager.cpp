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
    SharedPtr<HttpBuffer> http = SharedPtr<HttpBuffer>(new HttpBuffer(GetContext()));
    http->SetUrl(url);
    http->ready_ = false;
    while (true) {
        const String& state = http->GetState();
        if(state=="Loading" || state=="Init"){
            http->Load();
        }
        else if(state=="Ok")
        {
            http->ready_ = true;
            quene_.Push(http);
            return http.Get();
        }else{
            return nullptr;
        }
    }
    return nullptr;
}

HttpBuffer* HttpManager::SycGet(const String& url)
{
    SharedPtr<HttpBuffer> http = SharedPtr<HttpBuffer>(new HttpBuffer(GetContext()));
    http->SetUrl(url);
    http->ready_ = false;
    quene_.Push(http);
    return http.Get();
}
void HttpManager::HandleBeginFrame(StringHash eventType, VariantMap& eventData)
{
    for (List<SharedPtr<HttpBuffer> >::Iterator it = quene_.Begin(); it != quene_.End(); ) {
        SharedPtr<HttpBuffer>& http = *it;
        const String& state = http->GetState();
        if(!http->ready_)
        {
            if(state=="Loading" || state=="Init"){
                http->Load();
            }
            else if(state=="Ok")
            {
                http->ready_ = true;
                using namespace RequestOK;
                 VariantMap& eventData = GetEventDataMap();
                VectorBuffer* buffer = http->GetData();
                buffer->Seek(0);
                eventData[P_BUFFER] = buffer;
                SendEvent(E_REQUESTOK, eventData);
            }else{
                http->ready_ = true;
                using namespace RequestErr;
                VariantMap& eventData = GetEventDataMap();
                eventData[P_MSG] = state;
                SendEvent(E_REQUESTERR, eventData);
            }
        }
        else if(state=="Free")
        {
            it = quene_.Erase(it);
            continue;
        }
        it++;
    }
}

}
