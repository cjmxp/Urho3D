
#include "../UI/UI_Radio.h"

namespace Urho3D
{
    UI_Radio::UI_Radio(Context* context) :
    UI_Button(context)
    {
        SetEnabled(true);
    }
    UI_Radio::~UI_Radio() = default;
    const String& UI_Radio::GetValue()
    {
        return value_;
    }
    void UI_Radio::SetValue(const Urho3D::String &v){
        value_ = v;
    }
    bool UI_Radio::GetSelected(){
        return selected_;
    }
    void UI_Radio::SetSelected(bool v){
        selected_ = v;
    }
    void UI_Radio::SetSizeGrid(const String& rect){
        sizeGrid_ = IntRect::ZERO;
    }
    const IntVector2& UI_Radio::GetDrawRect(){
        return drawRect_;
    }
}
