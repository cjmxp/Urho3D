
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
		if (vary_) {
			UI_Clip::Update(timeStep);
			return;
		}
		
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
		if (layout_) {
			const IntVector2& size = GetSize();
			IntVector2 p = IntVector2(move.x_ - offset_, button->GetPosition().y_);
			if (p.x_ < 0) {
				p.x_ = 0;
			}
			if (p.x_ > size.x_ - button->GetWidth()) {
				p.x_ = size.x_ - button->GetWidth();
			}
			p.y_ = (GetHeight() - button->GetHeight()) / 2;
			button->SetPosition(p);
			layout_ = false;
		}
	}

	float UI_HSlider::GetValue() {
		int width = GetWidth() - button->GetWidth();
		int p = button->GetPosition().x_;
		return (float)p / width;
	}

	void UI_HSlider::SetValue(float value) {
		if (value < 0) {
			value = 0;
		}
		if (value > 1.0) {
			value = 1.0;
		}
		int width = GetWidth() - button->GetWidth();
		move.x_ = width * value;
		layout_ = true;
	}
}
