
#include "../UI/UI_VSlider.h"
namespace Urho3D
{
	UI_VSlider::UI_VSlider(Context* context) :
		UI_VSlider(context)
	{
	}

	UI_VSlider::~UI_VSlider() = default;
	
	void UI_VSlider::OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers,Cursor* cursor)
	{
		if (button->InRect(IntRect::ZERO, position)) {
			offset_ = position.y_ - button->GetPosition().y_;
		}
		else {
			offset_ = button->GetHeight() / 2;
		}
	}

	void UI_VSlider::Layout() {
		if (layout_) {
			const IntVector2& size = GetSize();
			IntVector2 p = IntVector2(move.x_ - offset_, button->GetPosition().y_);
			if (p.y_ < 0) {
				p.y_ = 0;
			}
			if (p.y_ > size.y_ - button->GetHeight()) {
				p.y_ = size.y_ - button->GetHeight();
			}
			p.x_ = (GetWidth() - button->GetWidth()) / 2;
			button->SetPosition(p);
			layout_ = false;
		}
	}

	float UI_VSlider::GetValue() {
		int height = GetHeight() - button->GetHeight();
		int p = button->GetPosition().y_;
		return (float)p / height;
	}

	void UI_VSlider::SetValue(float value) {
		if (value < 0) {
			value = 0;
		}
		if (value > 1.0) {
			value = 1.0;
		}
		int height = GetHeight() - button->GetHeight();
		move.x_ = height * value;
		layout_ = true;
	}
}
