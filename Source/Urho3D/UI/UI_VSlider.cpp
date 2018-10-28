
#include "../UI/UI_VSlider.h"
namespace Urho3D
{
	UI_VSlider::UI_VSlider(Context* context) :
		UI_HSlider(context)
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
		move = IntVector2::ZERO;
		button->SetSelected(true);
	}

	void UI_VSlider::Layout() {
		if (layout_ || isvalue_) {
			if (offset_ == 0) {
				offset_ = button->GetHeight() / 2;
			}
			const IntVector2& size = GetSize();
			IntVector2 p = IntVector2(0, 0);
			int height = GetHeight() - button->GetHeight();
			if (isvalue_) {
				p.y_ = height * value_;
			}
			else {
				p.y_ = move.y_ - offset_;
			}
			if (p.y_ < 0) {
				p.y_ = 0;
			}
			if (p.y_ > size.y_ - button->GetHeight()) {
				p.y_ = size.y_ - button->GetHeight();
			}
			p.x_ = (GetWidth() - button->GetWidth()) / 2;
			button->SetPosition(p);
			layout_ = false;
			isvalue_ = false;
			value_ = (float)p.y_ / height;
			if (value_ > 1.0)value_ = 1.0;
			if (value_ < 0.0)value_ = 0.0;
		}
	}
}
