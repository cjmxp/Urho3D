
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

	const IntVector2& UI_CheckBox::GetDrawRect() {
		return drawRect_;
	}
	void UI_CheckBox::Layout() {
		if (layout_ || positionDirty_) {
			layout_ = false;
			int y = (drawRect_.y_ - lable_->textHeight) / 2;
			IntVector2 pos = GetPosition();
			lable_->SetPosition(IntVector2(pos.x_+drawRect_.x_+2, pos.y_+y+1));
			SetSize(drawRect_.x_ + lable_->textWidth, drawRect_.y_ > lable_->textHeight ? drawRect_.y_ : lable_->textHeight);
		}
	}

	void UI_CheckBox::Update(float timeStep) {
		UI_Clip::Update(timeStep);
		if (selected_)return;
		if (hovering_ && !pressed_) {
			SetIndex(1);
		}
		else if (!hovering_ && !pressed_) {
			SetIndex(0);
		}
	}

	void UI_CheckBox::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, int button, int buttons, int qualifiers, Cursor* cursor)
	{
		if (selected_)return;
		if (button == MOUSEB_LEFT)
		{
			if (pressed_) {
				SetIndex(1);
				pressed_ = false;
			}
			else {
				SetIndex(2);
				pressed_ = true;
			}
			hovering_ = true;
			if (enabled_) {
				using namespace Released;
				VariantMap& eventData = GetEventDataMap();
				eventData[P_ELEMENT] = this;
				SendEvent(E_PRESSED, eventData);
			}
		}
	}

	void UI_CheckBox::OnClickEnd(const IntVector2& position, const IntVector2& screenPosition, int button, int buttons, int qualifiers, Cursor* cursor, UIElement* beginElement)
	{
		if (selected_)return;
		if (button == MOUSEB_LEFT)
		{
			if (IsInside(screenPosition, true))
				hovering_ = true;
			if (enabled_) {
				using namespace Released;
				VariantMap& eventData = GetEventDataMap();
				eventData[P_ELEMENT] = this;
				SendEvent(E_RELEASED, eventData);
			}
		}
	}
}
