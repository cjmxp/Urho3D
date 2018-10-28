
#include "../UI/UI_VScrollBar.h"
namespace Urho3D
{
	UI_VScrollBar::UI_VScrollBar(Context* context) :
		UI_HScrollBar(context)
	{
	}

	UI_VScrollBar::~UI_VScrollBar() = default;
	
	void UI_VScrollBar::init() {
		if (slider_ == nullptr) {
			up_ = SharedPtr<UI_Button>(new UI_Button(GetContext()));
			up_->SetParent(this);
			up_->SetClipX(1);
			up_->SetClipY(3);
			slider_ = SharedPtr<UI_HSlider>(new UI_VSlider(GetContext()));
			slider_->SetParent(this);
			down_ = SharedPtr<UI_Button>(new UI_Button(GetContext()));
			down_->SetParent(this);
			down_->SetClipX(1);
			down_->SetClipY(3);
		}
	}
	void UI_VScrollBar::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, int button, int buttons, int qualifiers, Cursor* cursor)
	{
		if (up_->InRect(IntRect::ZERO, position)) {
			up_->OnClickBegin(position, screenPosition, button, buttons, qualifiers, cursor);
			slider_->SetValue(slider_->GetValue() - 0.1);
			return;
		}
		if (slider_->InRect(IntRect::ZERO, position)) {
			pos_ = position;
			pos_.y_ -= up_->GetHeight();
			slider_->OnClickBegin(pos_, screenPosition, button, buttons, qualifiers, cursor);
			return;
		}
		if (down_->InRect(IntRect::ZERO, position)) {
			down_->OnClickBegin(position, screenPosition, button, buttons, qualifiers, cursor);
			slider_->SetValue(slider_->GetValue() + 0.1);
			return;
		}
	}

	void UI_VScrollBar::OnClickEnd(const IntVector2& position, const IntVector2& screenPosition, int button, int buttons, int qualifiers, Cursor* cursor, UIElement* beginElement)
	{
		if (up_->InRect(IntRect::ZERO, position)) {
			up_->OnClickEnd(position, screenPosition, button, buttons, qualifiers, cursor, beginElement);
			return;
		}
		if (slider_->InRect(IntRect::ZERO, position)) {
			pos_ = position;
			pos_.y_ -= up_->GetHeight();
			slider_->OnClickEnd(pos_, screenPosition, button, buttons, qualifiers, cursor, beginElement);
			return;
		}
		if (down_->InRect(IntRect::ZERO, position)) {
			down_->OnClickEnd(position, screenPosition, button, buttons, qualifiers, cursor, beginElement);
			return;
		}
	}

	void UI_VScrollBar::OnHover(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers, Cursor* cursor)
	{
		if (up_->InRect(IntRect::ZERO, position)) {
			up_->OnHover(position, screenPosition, buttons, qualifiers, cursor);
			return;
		}
		if (slider_->InRect(IntRect::ZERO, position)) {
			pos_ = position;
			pos_.y_ -= up_->GetHeight();
			slider_->OnHover(pos_, screenPosition, buttons, qualifiers, cursor);
			return;
		}
		if (down_->InRect(IntRect::ZERO, position)) {
			down_->OnHover(position, screenPosition, buttons, qualifiers, cursor);
			return;
		}
	}

	void UI_VScrollBar::OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers,Cursor* cursor)
	{
		if (slider_->InRect(IntRect::ZERO, position)) {
			pos_ = position;
			pos_.y_ -= up_->GetHeight();
			slider_->OnDragBegin(pos_, screenPosition, buttons, qualifiers, cursor);
			onDrag_ = true;
		}
	}

	void UI_VScrollBar::OnDragMove(const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, int buttons, int qualifiers, Cursor* cursor)
	{
		if (onDrag_) {
			pos_ = position;
			pos_.y_ -= up_->GetHeight();
			slider_->OnDragMove(pos_, screenPosition, deltaPos, buttons, qualifiers, cursor);
		}
	}
	void UI_VScrollBar::OnDragEnd(const IntVector2& position, const IntVector2& screenPosition, int dragButtons, int releaseButton, Cursor* cursor)
	{
		if (onDrag_) {
			pos_ = position;
			pos_.y_ -= up_->GetHeight();
			slider_->OnDragEnd(pos_, screenPosition, dragButtons, releaseButton, cursor);
			onDrag_ = false;
		}
	}


	void UI_VScrollBar::Layout() {
		if (layout_ && GetParent()!=nullptr) {
			layout_ = false;
			SetSize(up_->GetWidth(),GetParent()->GetHeight());
			int width = GetWidth();
			int height = GetHeight();
			up_->SetPosition(width - up_->GetWidth(), 0);
			down_->SetPosition(width - up_->GetWidth(), height - down_->GetHeight());
			slider_->SetPosition(width - up_->GetWidth(), up_->GetHeight());
			slider_->SetSize(up_->GetWidth(), height - up_->GetHeight() - down_->GetHeight());
		}
	}
}
