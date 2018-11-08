
#include "../UI/UI_HScrollBar.h"
namespace Urho3D
{
	UI_HScrollBar::UI_HScrollBar(Context* context) :
		UI_Box(context)
	{
		SetEnabled(true);
	}

	UI_HScrollBar::~UI_HScrollBar() = default;

	void UI_HScrollBar::InitAttribute(UI_Box* box)
	{
		UI_Box::InitAttribute(box);
		XMLElement root = GetRoot();
		Vector<String> names = root.GetAttributeNames();
		for (int i = 0; i < names.Size(); i++) {
			String name = names[i].ToLower();
			if (name == "skin") {
				SetSkin(root.GetAttribute(names[i]));
			}
			else if (name == "value") {
				SetValue(ToFloat(root.GetAttribute(names[i])));
			}
		}
	}
	void UI_HScrollBar::SetSkin(const String& skin)
	{
		init();
		if (skin_ != skin && skin!=String::EMPTY) {
			skin_ = skin;
			slider_->SetSkin(skin_);
			Vector<String> node = skin_.Split('.', false); node.Pop();
			up_->SetSkin(String::Joined(node, ".") + "$up.png");
			down_->SetSkin(String::Joined(node, ".") + "$down.png");
			layout_ = true;
		}
	}

	void UI_HScrollBar::init() {
		if (slider_ == nullptr) {
			up_ = SharedPtr<UI_Button>(new UI_Button(GetContext()));
			up_->SetParent(this);
			up_->SetClipX(1);
			up_->SetClipY(3);
			slider_ = SharedPtr<UI_HSlider>(new UI_HSlider(GetContext()));
			slider_->SetParent(this);
			down_ = SharedPtr<UI_Button>(new UI_Button(GetContext()));
			down_->SetParent(this);
			down_->SetClipX(1);
			down_->SetClipY(3);
		}
	}

	const String& UI_HScrollBar::GetSkin() {
		return skin_;
	}

	float UI_HScrollBar::GetValue() {
		return slider_->GetValue();
	}

	void UI_HScrollBar::SetValue(float value) {
		init();
        if(max_>0)
        {
           slider_->SetValue(value);
        }
	}

	void UI_HScrollBar::Update(float timeStep) {
		up_->Update(timeStep);
		slider_->Update(timeStep);
		down_->Update(timeStep);
		Layout();
	}

	void UI_HScrollBar::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, int button, int buttons, int qualifiers, Cursor* cursor)
	{
		if (up_->InRect(IntRect::ZERO, position)) {
			up_->OnClickBegin(position, screenPosition, button, buttons, qualifiers, cursor);
            if(max_>0){
                slider_->SetValue(slider_->GetValue() - 0.1);
                if(parent_!=nullptr && parent_->GetTypeName()!="UIElement"){
                    UI_Box* parent = static_cast<UI_Box *>(parent_);
                    parent->OnScroll(slider_->GetValue());
                }
            }
			return;
		}
		if (slider_->InRect(IntRect::ZERO, position)) {
            if(max_>0){
                pos_.x_ -= up_->GetWidth();
                slider_->OnClickBegin(pos_, screenPosition, button, buttons, qualifiers, cursor);
                if(parent_!=nullptr && parent_->GetTypeName()!="UIElement"){
                    UI_Box* parent = static_cast<UI_Box *>(parent_);
                    parent->OnScroll(slider_->GetValue());
                }
            }
			return;
		}
		if (down_->InRect(IntRect::ZERO, position)) {
			down_->OnClickBegin(position, screenPosition, button, buttons, qualifiers, cursor);
            if(max_>0){
                slider_->SetValue(slider_->GetValue() + 0.1);
                if(parent_!=nullptr && parent_->GetTypeName()!="UIElement"){
                    UI_Box* parent = static_cast<UI_Box *>(parent_);
                    parent->OnScroll(slider_->GetValue());
                }
            }
			return;
		}
	}

	void UI_HScrollBar::OnClickEnd(const IntVector2& position, const IntVector2& screenPosition, int button, int buttons, int qualifiers, Cursor* cursor, UIElement* beginElement)
	{
		if (up_->InRect(IntRect::ZERO, position)) {
			up_->OnClickEnd(position, screenPosition, button, buttons, qualifiers, cursor, beginElement);
			return;
		}
		if (slider_->InRect(IntRect::ZERO, position) && max_>0) {
			pos_ = position;
			pos_.x_ -= up_->GetWidth();
			slider_->OnClickEnd(pos_, screenPosition, button, buttons, qualifiers, cursor, beginElement);
            if(parent_!=nullptr && parent_->GetTypeName()!="UIElement"){
                UI_Box* parent = static_cast<UI_Box *>(parent_);
                parent->OnScroll(slider_->GetValue());
            }
			return;
		}
		if (down_->InRect(IntRect::ZERO, position)) {
			down_->OnClickEnd(position, screenPosition, button, buttons, qualifiers, cursor, beginElement);
			return;
		}
	}

	void UI_HScrollBar::OnHover(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers, Cursor* cursor)
	{
		if (up_->InRect(IntRect::ZERO, position)) {
			up_->OnHover(position, screenPosition, buttons, qualifiers, cursor);
			return;
		}
		if (slider_->InRect(IntRect::ZERO, position)) {
			pos_ = position;
			pos_.x_ -= up_->GetWidth();
			slider_->OnHover(pos_, screenPosition, buttons, qualifiers, cursor);
			return;
		}
		if (down_->InRect(IntRect::ZERO, position)) {
			down_->OnHover(position, screenPosition, buttons, qualifiers, cursor);
			return;
		}
	}

	void UI_HScrollBar::OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers,Cursor* cursor)
	{
        if(max_<=0)return;
		if (slider_->InRect(IntRect::ZERO, position)) {
			pos_ = position;
			pos_.x_ -= up_->GetWidth();
			slider_->OnDragBegin(pos_, screenPosition, buttons, qualifiers, cursor);
            if(parent_!=nullptr && parent_->GetTypeName()!="UIElement"){
                UI_Box* parent = static_cast<UI_Box *>(parent_);
                parent->OnScroll(slider_->GetValue());
            }
			onDrag_ = true;
		}
	}

	void UI_HScrollBar::OnDragMove(const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, int buttons, int qualifiers, Cursor* cursor)
	{
        if(max_<=0)return;
		if (onDrag_) {
			pos_ = position;
			pos_.x_ -= up_->GetWidth();
			slider_->OnDragMove(pos_, screenPosition, deltaPos, buttons, qualifiers, cursor);
            if(parent_!=nullptr && parent_->GetTypeName()!="UIElement"){
                UI_Box* parent = static_cast<UI_Box *>(parent_);
                parent->OnScroll(slider_->GetValue());
            }
		}
	}
	void UI_HScrollBar::OnDragEnd(const IntVector2& position, const IntVector2& screenPosition, int dragButtons, int releaseButton, Cursor* cursor)
	{
        if(max_<=0)return;
		if (onDrag_) {
			pos_ = position;
			pos_.x_ -= up_->GetWidth();
			slider_->OnDragEnd(pos_, screenPosition, dragButtons, releaseButton, cursor);
            if(parent_!=nullptr && parent_->GetTypeName()!="UIElement"){
                UI_Box* parent = static_cast<UI_Box *>(parent_);
                parent->OnScroll(slider_->GetValue());
            }
			onDrag_ = false;
		}
	}

	void UI_HScrollBar::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor)
	{
		slider_->GetBatches(batches, vertexData, currentScissor);
		up_->GetBatches(batches, vertexData, currentScissor);
		down_->GetBatches(batches, vertexData, currentScissor);
	}

	void UI_HScrollBar::Layout() {
		if (layout_ && GetParent()!=nullptr) {
			if (skin_ != String::EMPTY) {
				slider_->SetSkin(skin_);
				Vector<String> node = skin_.Split('.', false); node.Pop();
				up_->SetSkin(String::Joined(node, ".") + "$up.png");
				down_->SetSkin(String::Joined(node, ".") + "$down.png");
			}
			layout_ = false;
			SetSize(GetParent()->GetWidth(), up_->GetHeight());
			int width = GetWidth();
			up_->SetPosition(0, 0);
			down_->SetPosition(width - down_->GetWidth(),0);
			slider_->SetPosition(up_->GetWidth(),0);
			slider_->SetSize(width - up_->GetWidth() - down_->GetWidth(), up_->GetHeight());
		}
	}
	void UI_HScrollBar::SetDataSource(Variant& source)
	{
		dataSource_ = source;
		if (source.GetTypeName() == "Float") {
			SetValue(source.GetFloat());
		}
	}
}
