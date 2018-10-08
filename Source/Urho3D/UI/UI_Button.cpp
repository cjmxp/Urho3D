#include "../UI/UI_Button.h"
#include "../UI/UIEvents.h"
#include "../UI/UI_Label.h"
namespace Urho3D
{
    UI_Button::UI_Button(Context* context) :
    UI_Clip(context)
    {
        SetEnabled(true);
    }
    
    UI_Button::~UI_Button() = default;
    
    const String& UI_Button::GetLable(){
        if(lable_!=nullptr)return lable_->GetText();
        return String::EMPTY;
    }
    
    void UI_Button::SetLable(const String& v){
        if(lable_==nullptr){
            lable_ = SharedPtr<UI_Label>(new UI_Label(GetContext()));
            lable_->SetEnabled(false);
            lable_->SetIsHtml(false);
            lable_->SetWordWrap(false);
            lable_->SetText(v);
        }
    }
   
    void UI_Button::Update(float timeStep){
        if(hovering_ && !pressed_){
            SetIndex(1);
        }else if(!hovering_ && pressed_){
            pressed_=false;
            using namespace Pressed;
            VariantMap& eventData = GetEventDataMap();
            eventData[P_ELEMENT] = this;
            SendEvent(E_PRESSED, eventData);
        }else if (!hovering_){
            SetIndex(0);
            scale_.x_ = 1.0f;
            scale_.y_ = 1.0f;
        }
        if(lable_!=nullptr){
            //size_.x_-lable_->GetTextSize()
            //lable_->SetPosition(<#int x#>, <#int y#>)
        }
    }
    void UI_Button::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, int button, int buttons, int qualifiers, Cursor* cursor)
    {
        if (button == MOUSEB_LEFT)
        {
            if(clipX_*clipY_>1){
                SetIndex(2);
            }else{
                scale_.x_ = 0.8f;
                scale_.y_ = 0.8f;
            }
            pressed_ = true;
            hovering_ = true;
            using namespace Released;
            VariantMap& eventData = GetEventDataMap();
            eventData[P_ELEMENT] = this;
            SendEvent(E_PRESSED, eventData);
        }
    }
    
    void UI_Button::OnClickEnd(const IntVector2& position, const IntVector2& screenPosition, int button, int buttons, int qualifiers, Cursor* cursor, UIElement* beginElement)
    {
        if (pressed_ && button == MOUSEB_LEFT)
        {
            
            if(clipX_*clipY_>1){
                SetIndex(0);
            }else{
                scale_.x_ = 1.0f;
                scale_.y_ = 1.0f;
            }
            pressed_ = false;
            if (IsInside(screenPosition, true))
                hovering_ = true;
            using namespace Released;
            VariantMap& eventData = GetEventDataMap();
            eventData[P_ELEMENT] = this;
            SendEvent(E_RELEASED, eventData);
        }
    }
}
