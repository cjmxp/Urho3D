
#pragma once

#include "../Core/Object.h"
#include "../Container/List.h"
#include "../Network/HttpRequest.h"
#include "../IO/Serializer.h"
#include "../IO/VectorBuffer.h"

namespace Urho3D
{

class URHO3D_API HttpManager : public Object
{
    URHO3D_OBJECT(HttpManager, Object);

public:

    HttpManager(Context* c);

    HttpRequest* Get(const String& url);
    HttpRequest* Download(const String& url, const String& filepath);



private:

    void HandleBeginFrame(StringHash eventType, VariantMap& eventData);
    void SendError(const String & msg);

    enum RequestType {
        GET, DOWNLOAD,
    };

    struct RequestInfo : public RefCounted {
        RequestType type_;
        String url_;
        String filepath_;
        Serializer* serializer_;
        VectorBuffer tempBuffer_;
        SharedPtr<HttpRequest> request_;
        ~RequestInfo() {
            delete serializer_;
        }
    };

    List<SharedPtr<RequestInfo> > quene_;
};

}