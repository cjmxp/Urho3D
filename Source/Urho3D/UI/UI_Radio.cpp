
#include "../UI/UI_Radio.h"
#include "../UI/UIEvents.h"
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
	void UI_Radio::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, int button, int buttons, int qualifiers, Cursor* cursor)
	{
		if (selected_)return;
		if (!pressed_ && button == MOUSEB_LEFT)
		{
			SetIndex(2);
			pressed_ = true;
			hovering_ = true;
			using namespace Released;
			VariantMap& eventData = GetEventDataMap();
			eventData[P_ELEMENT] = this;
			SendEvent(E_PRESSED, eventData);
		}
	}
}
