
#pragma once

#include "../Core/Object.h"
#include "../Container/List.h"
#include "../Network/HttpRequest.h"
#include "../Network/HttpBuffer.h"
#include "../IO/Serializer.h"
#include "../IO/VectorBuffer.h"

namespace Urho3D
{

class URHO3D_API HttpManager : public Object
{
    URHO3D_OBJECT(HttpManager, Object);

public:

    HttpManager(Context* c);

    HttpBuffer* Get(const String& url);
    HttpBuffer* SycGet(const String& url);



private:

    void HandleBeginFrame(StringHash eventType, VariantMap& eventData);
    void SendError(const String & msg);
    List<SharedPtr<HttpBuffer> > quene_;
};

}
