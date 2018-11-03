
#include "../UI/UI_Radio.h"
#include "../UI/UIEvents.h"
namespace Urho3D
{
    UI_Radio::UI_Radio(Context* context) :
		UI_CheckBox(context)
    {
    }
    UI_Radio::~UI_Radio() = default;

	void UI_Radio::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, int button, int buttons, int qualifiers, Cursor* cursor)
	{
		if (selected_)return;
		if (!pressed_ && button == MOUSEB_LEFT)
		{
			SetIndex(2);
			pressed_ = true;
			hovering_ = true;
			if (enabled_) {
				using namespace Released;
				VariantMap& eventData = GetEventDataMap();
				eventData[P_ELEMENT] = this;
				SendEvent(E_PRESSED, eventData);
			}
		}
	}
}
