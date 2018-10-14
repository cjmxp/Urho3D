
#include "../UI/UI_CheckBox.h"
#include "../UI/UIEvents.h"
namespace Urho3D
{
	UI_CheckBox::UI_CheckBox(Context* context) :
    UI_Button(context)
    {
        SetEnabled(true);
    }
	UI_CheckBox::~UI_CheckBox() = default;
    bool UI_CheckBox::GetSelected(){
        return selected_;
    }
    void UI_CheckBox::SetSelected(bool v){
        selected_ = v;
    }
    void UI_CheckBox::SetSizeGrid(const String& rect){
        sizeGrid_ = IntRect::ZERO;
    }
	const IntVector2& UI_CheckBox::GetDrawRect() {
		return drawRect_;
	}
	void UI_CheckBox::Layout() {
		if (layout_) {
			layout_ = false;
			int y = (drawRect_.y_ - lable_->textHeight) / 2;
			lable_->SetPosition(drawRect_.x_, y);
		}
	}

	void UI_CheckBox::Update(float timeStep) {
		if (hovering_ && !selected_) {
			SetIndex(1);
		}
		else if (!hovering_ && !selected_) {
			SetIndex(0);
		}
		if (!hovering_ && pressed_) {
			pressed_ = false;
			using namespace Pressed;
			VariantMap& eventData = GetEventDataMap();
			eventData[P_ELEMENT] = this;
			SendEvent(E_PRESSED, eventData);
		}
	}

	void UI_CheckBox::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, int button, int buttons, int qualifiers, Cursor* cursor)
	{
		if (button == MOUSEB_LEFT)
		{
			if (selected_) {
				selected_ = false;
				SetIndex(1);
			}
			else {
				selected_ = true;
				SetIndex(2);
			}
			pressed_ = true;
			hovering_ = true;
			using namespace Released;
			VariantMap& eventData = GetEventDataMap();
			eventData[P_ELEMENT] = this;
			SendEvent(E_PRESSED, eventData);
		}
	}

	void UI_CheckBox::OnClickEnd(const IntVector2& position, const IntVector2& screenPosition, int button, int buttons, int qualifiers, Cursor* cursor, UIElement* beginElement)
	{
		if (pressed_ && button == MOUSEB_LEFT)
		{
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
