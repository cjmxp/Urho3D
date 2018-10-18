#include "../UI/UI_Button.h"
#include "../UI/UIEvents.h"
#include "../UI/UI_Label.h"
namespace Urho3D
{
    UI_Button::UI_Button(Context* context) :
    UI_Clip(context)
    {
        SetEnabled(true);
    }
    
    UI_Button::~UI_Button() = default;
    
    const String& UI_Button::GetLable(){
        if(lable_!=nullptr)return lable_->GetText();
        return String::EMPTY;
    }
    
    void UI_Button::SetLable(const String& v){
        if(lable_==nullptr){
            lable_ = SharedPtr<UI_Label>(new UI_Label(GetContext()));
            lable_->SetEnabled(false);
            lable_->SetIsHtml(false);
            lable_->SetWordWrap(false);
        }
		lable_->SetText(v);
		layout_ = true;
    }

	void UI_Button::Layout() {
		if (layout_ || positionDirty_) {
			layout_ = false;
			const IntVector2& size = GetSize();
			if (size.x_ < lable_->textWidth + 4)SetWidth(lable_->textWidth + 4);
			if (size.y_ < lable_->textHeight + 4)SetHeight(lable_->textHeight + 4);
			int x = (size.x_ - lable_->textWidth) / 2;
			int y = (size.y_ - lable_->textHeight) / 2;
			IntVector2 pos = GetPosition();
			lable_->SetPosition(IntVector2(pos.x_ + x, pos.y_ + y));
		}
	}
   
	void UI_Button::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) {
		UI_Clip::GetBatches(batches, vertexData, currentScissor);
		if (lable_ != nullptr && lable_->GetText()!= String::EMPTY) {
			lable_->GetBatches(batches, vertexData, currentScissor);
		}
	}
	bool UI_Button::GetSelected() {
		return selected_;
	}
	void UI_Button::SetSelected(bool v) {
		selected_ = v;
		if (selected_) {
			SetIndex(2);
		}
		else if (hovering_) {
			SetIndex(1);
		}
		else {
			SetIndex(0);
		}
		SetScale(1.0f, 1.0f);
		if (lable_ != nullptr)lable_->SetScale(1.0f, 1.0f);
		SetHotSpot(0, 0);
	}
	void UI_Button::Update(float timeStep) {
		UI_Clip::Update(timeStep);
		if (selected_)return;
		if (hovering_ && !pressed_) {
			SetIndex(1);
		}
		else if (!hovering_ && pressed_) {
			pressed_ = false;
			using namespace Pressed;
			VariantMap& eventData = GetEventDataMap();
			eventData[P_ELEMENT] = this;
			SendEvent(E_PRESSED, eventData);
		}
		else if (!hovering_) {
			SetIndex(0);
			SetScale(1.0f, 1.0f);
			if (lable_ != nullptr)lable_->SetScale(1.0f, 1.0f);
			SetHotSpot(0, 0);
		}
	}

    void UI_Button::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, int button, int buttons, int qualifiers, Cursor* cursor)
    {
		if (selected_)return;
        if (button == MOUSEB_LEFT)
        {
			if (!pressed_) {
				if (clipX_*clipY_>1) {
					SetIndex(2);
				}
				else {
					SetScale(0.8f, 0.8f);
					if (lable_ != nullptr)lable_->SetScale(0.8f, 0.8f);
					const IntVector2 size = GetSize();
					SetHotSpot(size.x_ * 0.2 / 2, size.y_ * 0.2 / 2);
				}
				pressed_ = true;
				hovering_ = true;
				using namespace Released;
				VariantMap& eventData = GetEventDataMap();
				eventData[P_ELEMENT] = this;
				SendEvent(E_PRESSED, eventData);
			}
        }
    }
    
    void UI_Button::OnClickEnd(const IntVector2& position, const IntVector2& screenPosition, int button, int buttons, int qualifiers, Cursor* cursor, UIElement* beginElement)
    {
		if (selected_)return;
        if (pressed_ && button == MOUSEB_LEFT)
        {
            if(clipX_*clipY_>1){
                SetIndex(0);
            }else{
				SetScale(1.0f, 1.0f);
				if (lable_ != nullptr)lable_->SetScale(1.0f, 1.0f);
				SetHotSpot(0, 0);
            }
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
