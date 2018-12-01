
#pragma once

#include "../Core/Object.h"
#include "../Network/HttpRequest.h"
#include "../IO/Serializer.h"
#include "../IO/VectorBuffer.h"

namespace Urho3D
{

class URHO3D_API HttpBuffer : public Object
{
    URHO3D_OBJECT(HttpBuffer, Object);
public:
    HttpBuffer(Context* c);
    ~HttpBuffer() override;
    const VectorBuffer& GetData();
    const String& GetUrl();
    void SetUrl(const String& url);
    const String& GetState();
    bool Load();
    void Free();
private:
    SharedPtr<HttpRequest> request_;
    String state_;
    VectorBuffer buff_;
    VectorBuffer temp_;
};

}
