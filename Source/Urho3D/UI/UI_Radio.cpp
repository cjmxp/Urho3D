
#include "../UI/UI_Radio.h"

namespace Urho3D
{
    UI_Radio::UI_Radio(Context* context) :
		UI_CheckBox(context)
    {
    }
    UI_Radio::~UI_Radio() = default;
    const String& UI_Radio::GetValue()
    {
        return value_;
    }
    void UI_Radio::SetValue(const Urho3D::String &v){
        value_ = v;
    }
}
