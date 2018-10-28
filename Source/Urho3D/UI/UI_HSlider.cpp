
#include "../UI/UI_HSlider.h"
namespace Urho3D
{
	UI_HSlider::UI_HSlider(Context* context) :
		UI_Clip(context)
	{
		SetEnabled(true);
		button = SharedPtr<UI_Button>(new UI_Button(GetContext()));
		button->SetClipX(1);
		button->SetClipY(3);
		button->SetParent(this);
	}

	UI_HSlider::~UI_HSlider() = default;
	void UI_HSlider::Update(float timeStep) {
		button->Update(timeStep);
		UI_Clip::Update(timeStep);
	}
	void UI_HSlider::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, int btn, int btns, int qualifiers, Cursor* cursor)
	{
		if (btn == MOUSEB_LEFT)
		{
			if (button->InRect(IntRect::ZERO, position)) {
				button->OnClickBegin(position, screenPosition, btn, btns, qualifiers, cursor);
				
			}
		}
	}
	void UI_HSlider::OnClickEnd(const IntVector2& position, const IntVector2& screenPosition, int btn, int btns, int qualifiers, Cursor* cursor, UIElement* beginElement)
	{
		if (btn == MOUSEB_LEFT)
		{
			if (button->InRect(IntRect::ZERO, position)) {
				button->OnClickEnd(position, screenPosition, btn, btns, qualifiers, cursor, beginElement);
			}
			else if (move == IntVector2::ZERO) {
				layout_ = true;
				move = position;
				offset_ = 0;
				Layout();
				move = IntVector2::ZERO;
			}
		}
	}
	void UI_HSlider::OnHover(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers, Cursor* cursor)
	{
		hovering_ = true;
		if (button->InRect(IntRect::ZERO, position)) {
			button->OnHover(position, screenPosition, buttons, qualifiers, cursor);
		}
	}
	void UI_HSlider::OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers,Cursor* cursor)
	{
		if (button->InRect(IntRect::ZERO, position)) {
			const IntVector2& post = button->GetPosition();
			offset_ = position.x_ - post.x_;
		}
		else {
			offset_ = button->GetWidth() / 2;
		}
		move = IntVector2::ZERO;
		button->SetSelected(true);
	}
	void UI_HSlider::OnDragMove(const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, int buttons, int qualifiers, Cursor* cursor)
	{
		layout_ = true;
		move = position;
		Layout();
	}
	void UI_HSlider::OnDragEnd(const IntVector2& position, const IntVector2& screenPosition, int dragButtons, int releaseButton,Cursor* cursor)
	{
		offset_ = 0;
		move = IntVector2::ZERO;
		button->SetSelected(false);
	}
	void UI_HSlider::SetSkin(const String& skin) {
		UI_Clip::SetSkin(skin);
		Vector<String> node = skin.Split('.',false); node.Pop();
		button->SetSkin(String::Joined(node, ".") + "$bar.png");
		layout_ = true;
	}

	void UI_HSlider::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor)
	{
		UI_Clip::GetBatches(batches, vertexData, currentScissor);
		button->GetBatches(batches, vertexData, currentScissor);
	}

	void UI_HSlider::Layout() {
		if (layout_ || isvalue_) {
			if (offset_ == 0) {
				offset_ = button->GetWidth() / 2;
			}
			const IntVector2& size = GetSize();
			IntVector2 p = IntVector2(0, 0);
			int width = GetWidth() - button->GetWidth();
			if (isvalue_) {
				p.x_ = width * value_;
			}
			else {
				p.x_ = move.x_ - offset_;
			}
			if (p.x_ < 0) {
				p.x_ = 0;
			}
			if (p.x_ > size.x_ - button->GetWidth()) {
				p.x_ = size.x_ - button->GetWidth();
			}
			p.y_ = (GetHeight() - button->GetHeight()) / 2;
			button->SetPosition(p);
			layout_ = false;
			isvalue_ = false;
			value_ = (float)p.x_ / width;
			if (value_ > 1.0)value_ = 1.0;
			if (value_ < 0.0)value_ = 0.0;
		}
	}

	float UI_HSlider::GetValue() {
		return value_;
	}

	void UI_HSlider::SetValue(float value) {
		if (value < 0) {
			value = 0;
		}
		if (value > 1.0) {
			value = 1.0;
		}
		value_ = value;
		isvalue_ = true;
	}
}
