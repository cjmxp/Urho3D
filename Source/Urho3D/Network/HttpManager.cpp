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

HttpRequest* HttpManager::Get(const String& url)
{
    SharedPtr<RequestInfo> request(new RequestInfo);
    request->type_ = GET;
    request->url_ = url;

    request->request_ = new HttpRequest(request->url_, "GET", StringVector(), "");
    request->serializer_ = new VectorBuffer();

    quene_.Push(request);

    return request->request_;
}

HttpRequest* HttpManager::Download(const String& url, const String& filepath)
{
    SharedPtr<RequestInfo> request(new RequestInfo);
    request->type_ = DOWNLOAD;
    request->url_ = url;
    request->filepath_ = filepath;

    request->serializer_ = new File(context_, request->filepath_, FILE_WRITE);
    if (!request->serializer_)
        return nullptr;

    request->request_ = new HttpRequest(request->url_, "GET", StringVector(), "");

    quene_.Push(request);

    return request->request_;
}

void HttpManager::SendError(const String& msg) {
    using namespace RequestErr;

    VariantMap& eventData = GetEventDataMap();

    eventData[P_MSG] = msg;

    SendEvent(E_REQUESTERR, eventData);
}

void HttpManager::HandleBeginFrame(StringHash eventType, VariantMap& eventData)
{
    
    for (List<SharedPtr<RequestInfo> >::Iterator it = quene_.Begin(); it != quene_.End(); ) {
        SharedPtr<RequestInfo>& info = *it;
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
        }
    }
}

}
