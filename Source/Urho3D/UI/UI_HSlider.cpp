
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
			IntVector2 pos = button->GetPosition();
			int y = (GetHeight() - button->GetHeight())/2;
			button->SetPosition(pos.x_, y);
			return;
		}
		
	}
	void UI_HSlider::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, int btn, int btns, int qualifiers, Cursor* cursor)
	{
		if (btn == MOUSEB_LEFT)
		{
			if (button->InRect(IntRect::ZERO, position)) {
				button->OnClickBegin(position, screenPosition, btn, btns, qualifiers, cursor);
				button->
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

	void UI_HSlider::SetSkin(const String& skin) {
		UI_Clip::SetSkin(skin);
		Vector<String> node = skin.Split('.',false); node.Pop();
		button->SetSkin(String::Joined(node, ".") + "$bar.png");
	}

	void UI_HSlider::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor)
	{
		UI_Clip::GetBatches(batches, vertexData, currentScissor);
		button->GetBatches(batches, vertexData, currentScissor);
	}
}
