#include "../Network/HttpBuffer.h"
#include "../Network/HttpRequest.h"

namespace Urho3D
{

HttpBuffer::HttpBuffer(Context * c):Object(c)
{
    
}
HttpBuffer::~HttpBuffer()
{
    ready_=false;
    buff_.Clear();
    temp_.Clear();
}
VectorBuffer* HttpBuffer::GetData()
{
    return &buff_;
}
const String& HttpBuffer::GetUrl()
{
    if(request_==nullptr){
        return request_->GetURL();
    }
    return String::EMPTY;
}
void HttpBuffer::SetUrl(const String& url)
{
    if(request_==nullptr){
        request_ = SharedPtr<HttpRequest>(new HttpRequest(url, "GET", StringVector(), ""));
        buff_.Clear();
        state_ = "Init";
    }
}
const String& HttpBuffer::GetState()
{
    return state_;
}
bool HttpBuffer::Load()
{
    if(request_!=nullptr){
        if (request_->GetState() == HTTP_ERROR)
        {
            state_ = request_->GetError();
            return true;
        }
        else if (request_->GetState() == HTTP_CLOSED)
        {
            state_ = "Close";
            return true;
        }
        else if (request_->IsEof())
        {
            state_ = "Ok";
            return true;
        }
        else
        {
            unsigned size = request_->GetAvailableSize();
            if (size != 0) {
                temp_.Clear();
                temp_.Resize(size);
                request_->Read(temp_.GetModifiableData(), size);
                buff_.Write(temp_.GetData(), size);
            }
            state_ = "Loading";
            return false;
        }
    }
    return false;
}
void HttpBuffer::Free()
{
    state_="Free";
}
}
