#include "../UI/UI_Box.h"
#include "../UI/UI_Clip.h"
#include "../UI/UI_Button.h"
#include "../UI/UI_CheckBox.h"
#include "../UI/UI_HScrollBar.h"
#include "../UI/UI_VScrollBar.h"
#include "../UI/UI_HSlider.h"
#include "../UI/UI_VSlider.h"
#include "../UI/UI_Radio.h"
#include "../UI/UI_RadioGroup.h"
#include "../UI/UI_Tab.h"
#include "../UI/UI_Dialog.h"
#include "../UI/UI_View.h"
#include "../UI/UI_List.h"
#include "../UI/UIEvents.h"

namespace Urho3D
{
    UI_Box::UI_Box(Context* context) :
		UIElement(context)
    {
		SetTraversalMode(TM_DEPTH_FIRST);
		SetEnabled(true);
    }

    UI_Box::~UI_Box() = default;
   
    void UI_Box::UpdateLayout()
    {
        if (layoutNestingLevel_)
            return;
        // Prevent further updates while this update happens
        DisableLayoutUpdate();

        for (unsigned i = 0; i < children_.Size(); ++i)
        {
            children_[i]->UpdateLayout();
        }

        using namespace LayoutUpdated;

        VariantMap& eventData = GetEventDataMap();
        eventData[P_ELEMENT] = this;
        SendEvent(E_LAYOUTUPDATED, eventData);

        EnableLayoutUpdate();
    }
	void UI_Box::Update(float timeStep)
	{
		Layout();
	}
	void UI_Box::SetHotSpot(const IntVector2& hotSpot)
	{
		if (hotSpot != hotSpot_)
		{
			hotSpot_ = hotSpot;
		}
	}

	void UI_Box::SetHotSpot(int x, int y)
	{
		SetHotSpot(IntVector2(x, y));
	}
	void UI_Box::SetRotation(float angle)
	{
		if (angle != rotation_)
		{
			rotation_ = angle;
			MarkDirty();
		}
	}
    void UI_Box::OnScroll(float value){}
	void UI_Box::InitAttribute(UI_Box* box_) {
		XMLElement root = GetRoot();
		Vector<String> names = root.GetAttributeNames();
		if (box_ == nullptr)box_ = this;
		for (int i = 0; i < names.Size(); i++) {
			String name = names[i].ToLower();
			if (name == "name") {
				SetName(root.GetAttribute(names[i]));
			}
			else if (name == "x") {
				SetPosition(ToInt(root.GetAttribute(names[i]).CString()), GetPosition().y_);
			}
			else if (name == "y") {
				SetPosition(GetPosition().x_, ToInt(root.GetAttribute(names[i]).CString()));
			}
			else if (name == "width") {
				SetWidth(ToInt(root.GetAttribute(names[i]).CString()));
			}
			else if (name == "height") {
				SetHeight(ToInt(root.GetAttribute(names[i]).CString()));
			}
			else if (name == "top") {
				SetTop(ToInt(root.GetAttribute(names[i]).CString()));
			}
			else if (name == "left") {
				SetLeft(ToInt(root.GetAttribute(names[i]).CString()));
			}
			else if (name == "right") {
				SetRight(ToInt(root.GetAttribute(names[i]).CString()));
			}
			else if (name == "bottom") {
				SetBottom(ToInt(root.GetAttribute(names[i]).CString()));
			}
			else if (name == "centerX") {
				SetCenterX(ToInt(root.GetAttribute(names[i]).CString()));
			}
			else if (name == "centerY") {
				SetCenterY(ToInt(root.GetAttribute(names[i]).CString()));
			}
			else if (name == "disabled")  {
				SetEnabled(ToBool(root.GetAttribute(names[i]).CString()));
			}
			else if (name == "scaleX") {
				SetScale(ToFloat(root.GetAttribute(names[i]).CString()), GetScale().y_);
			}
			else if (name == "scaleY") {
				SetScale(GetScale().x_, ToFloat(root.GetAttribute(names[i]).CString()));
			}
			else if (name == "scale") {
				float scale = ToFloat(root.GetAttribute(names[i]).CString());
				SetScale(scale, scale);
			}
			else if (name == "visible") {
				SetVisible(ToBool(root.GetAttribute(names[i]).CString()));
			}
			else if (name == "var") {
				box_->SetVar(root.GetAttribute(names[i]), this);
			}
		}
	}
	void UI_Box::InitChilds(UI_Box* box_)
	{
		if (box_ == nullptr)box_ = this;
		XMLElement root = GetRoot();
		if (root.IsNull())return;
		XMLElement node = root.GetChild();
		while (!node.IsNull()) {
			String name = node.GetName().ToLower();
			if (name == "clip" || name == "image") {
				UI_Clip * box = new UI_Clip(GetContext());
				box->SetXml(node);
				box->InitAttribute(box_);
				box->InitChilds(box_);
				AddChild(box);
			}
			else if (name == "box") {
				UI_Box* box = new UI_Box(GetContext());
				box->SetXml(node);
				box->InitAttribute(box_);
				box->InitChilds(box_);
				AddChild(box);
			}
            else if (name == "list") {
                UI_List * box = new UI_List(GetContext());
                box->SetXml(node);
                box->InitAttribute(box_);
                box->InitChilds(box_);
                AddChild(box);
            }
            else if (name == "tab") {
                UI_Tab * box = new UI_Tab(GetContext());
                box->SetXml(node);
                box->InitAttribute(box_);
                box->InitChilds(box_);
                AddChild(box);
            }
			else if (name == "button") {
				UI_Button * box = new UI_Button(GetContext());
				box->SetXml(node);
				box->InitAttribute(box_);
				box->InitChilds(box_);
				AddChild(box);
			}
			else if (name == "checkbox") {
				UI_CheckBox * box = new UI_CheckBox(GetContext());
				box->SetXml(node);
				box->InitAttribute(box_);
				box->InitChilds(box_);
				AddChild(box);
			}
			else if (name == "hscrollbar") {
				UI_HScrollBar * box = new UI_HScrollBar(GetContext());
				box->SetXml(node);
				box->InitAttribute(box_);
				box->InitChilds(box_);
				AddChild(box);
			}
			else if (name == "vscrollbar") {
				UI_VScrollBar * box = new UI_VScrollBar(GetContext());
				box->SetXml(node);
				box->InitAttribute();
				box->InitChilds();
				AddChild(box);
			}
			else if (name == "hslider") {
				UI_HSlider * box = new UI_HSlider(GetContext());
				box->SetXml(node);
				box->InitAttribute(box_);
				box->InitChilds(box_);
				AddChild(box);
			}
			else if (name == "vslider") {
				UI_VSlider * box = new UI_VSlider(GetContext());
				box->SetXml(node);
				box->InitAttribute(box_);
				box->InitChilds(box_);
				AddChild(box);
			}
			else if (name == "label") {
				UI_Label * box = new UI_Label(GetContext());
				box->SetXml(node);
				box->InitAttribute(box_);
				box->InitChilds(box_);
				AddChild(box);
			}
			else if (name == "radio") {
				UI_Radio * box = new UI_Radio(GetContext());
				box->SetXml(node);
				box->InitAttribute(box_);
				box->InitChilds(box_);
				AddChild(box);
			}
			else if (name == "radiogroup") {
				UI_RadioGroup * box = new UI_RadioGroup(GetContext());
				box->SetXml(node);
				box->InitAttribute(box_);
				box->InitChilds(box_);
				AddChild(box);
			}
			node = node.GetNext();
		}
	}
	const String& UI_Box::GetXml() {
		return xml_str_;
	}
	void UI_Box::SetXml(const XMLElement& xml) {
		xml_ = xml;
	}
	void UI_Box::SetXml(const String& str) {
		if (xml_str_ != str && str != String::EMPTY) {
			xml_str_ = str;
			if (xmlfile_ == nullptr) {
				xmlfile_ = SharedPtr<XMLFile>(new XMLFile(GetContext()));
			}
			xmlfile_->FromString(str);
			xml_ = xmlfile_->GetRoot();
		}
	}
	XMLElement UI_Box::GetRoot(const String& name) {
		return xml_;
	}
	void UI_Box::SetScale(const Vector2& scale)
	{
		if (scale != scale_)
		{
			scale_ = scale;
			MarkDirty();
		}
	}
	void UI_Box::SetScale(float x, float y)
	{
		SetScale(Vector2(x, y));
	}
	const Matrix3x4& UI_Box::GetTransform() const {
		if (positionDirty_)
		{
			Matrix3x4 parentTransform = Matrix3x4::IDENTITY;
			if (parent_){
				const IntVector2& parentScreenPos = parent_->GetScreenPosition() + parent_->GetChildOffset();
				parentTransform.SetTranslation(Vector3((float)parentScreenPos.x_, (float)parentScreenPos.y_, 0.0f));
			}
			float px = (float)position_.x_;// IntVector2::ZERO
			float py = (float)position_.y_;
			if (scale_.x_ != 1.0 || scale_.y_!=1.0) {
				px += hotSpot_.x_;
				py += hotSpot_.y_;
			}
			Matrix3x4 mainTransform(Vector3(px, py, 0.0f), Quaternion(rotation_, Vector3::FORWARD), Vector3(scale_.x_, scale_.y_, 1.0f));
			transform_ = parentTransform * mainTransform;
			positionDirty_ = false;
			// Calculate an approximate screen position for GetElementAt(), or pixel-perfect child elements
			Vector3 topLeftCorner = transform_ * Vector3::ZERO;
			screenPosition_ = IntVector2((int)topLeftCorner.x_, (int)topLeftCorner.y_);
		}
		return transform_;
	}

	const IntVector2& UI_Box::GetScreenPosition() const
	{
		// This updates screen position for a sprite
		GetTransform();
		return screenPosition_;
	}

	IntVector2 UI_Box::ScreenToElement(const IntVector2& screenPosition)
	{
		Vector3 floatPos((float)screenPosition.x_, (float)screenPosition.y_, 0.0f);
		Vector3 transformedPos = GetTransform().Inverse() * floatPos;
		return IntVector2((int)transformedPos.x_, (int)transformedPos.y_);
	}

	IntVector2 UI_Box::ElementToScreen(const IntVector2& position)
	{
		Vector3 floatPos((float)position.x_, (float)position.y_, 0.0f);
		Vector3 transformedPos = GetTransform() * floatPos;
		return IntVector2((int)transformedPos.x_, (int)transformedPos.y_);
	}
	bool UI_Box::InRect(const IntRect& rect, const IntVector2& pos) {
		if (rect == IntRect::ZERO) {
			return IntRect(GetPosition(), GetPosition()+GetSize()).IsInside(pos);
		}
		return rect.IsInside(pos);
	}
	void UI_Box::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor)
	{
		
		// Reset hovering for next frame
		hovering_ = false;
	}
	int UI_Box::GetTop()
	{
		return top_;
	}
	void UI_Box::SetTop(int v)
	{
		top_ = v;
		layout_ = true;
	}
	int UI_Box::GetLeft() {
		return left_;
	}
	void UI_Box::SetLeft(int v)
	{
		left_ = v;
		layout_ = true;
	}
	int UI_Box::GetRight()
	{
		return right_;
	}
	void UI_Box::SetRight(int v)
	{
		right_ = v;
		layout_ = true;
	}
	int UI_Box::GetBottom()
	{
		return bottom_;
	}
	void UI_Box::SetBottom(int v)
	{
		bottom_ = v;
		layout_ = true;
	}
	int UI_Box::GetCenterX()
	{
		return centerX_;
	}
	void UI_Box::SetCenterX(int v)
	{
		centerX_ = v;
		layout_ = true;
	}
	int UI_Box::GetCenterY()
	{
		return centerY_;
	}
	void UI_Box::SetCenterY(int v)
	{
		centerY_ = v;
		layout_ = true;
	}

	void UI_Box::Layout() {
		if (layout_ || positionDirty_) {
			RefreshSize();
			RefreshPosition();
		}
		layout_ = false;
    }
    void UI_Box::RefreshPosition(){
        int x = position_.x_;
        int y = position_.y_;
		if (left_ >= 0)x = left_;
        if(top_ >= 0)y=top_;
        if(parent_!=nullptr){
            int pw = parent_->GetWidth();
            int ph = parent_->GetHeight();
			int w = GetWidth();
			int h = GetHeight();
            if(centerX_ >= 0){
                x = (pw-w)/2+centerX_;
            }else if(left_ < 0 && right_ >= 0){
                x=pw-w-right_;
            }
            if(centerY_ >= 0){
                y = (ph-h)/2+centerY_;
            }else if(top_ < 0 && bottom_ >= 0){
                y=ph-h-bottom_;
            }
        }
		SetPosition(IntVector2(x, y));
    }
    void UI_Box::RefreshSize(){
        if(parent_==nullptr)return;
        int pw = parent_->GetWidth();
        int ph = parent_->GetHeight();
        int w = GetWidth();
        int h = GetHeight();
        if(left_ >= 0 && right_ >= 0){
            w = pw-left_ -right_;
        }
        if(top_ >= 0 && bottom_ >= 0){
            h = ph-top_ -bottom_;
        }
		SetSize(IntVector2(w, h));
    }
	UI_Box* UI_Box::GetChild(const StringHash& name)
	{
		for (unsigned i = 0;i<children_.Size();i++)
		{
			if (children_[i]->GetName().ToHash() == name.ToHash()) {
				UI_Box* node = static_cast<UI_Box*>(children_[i].Get());
				return node;
			}
			
		}
		return nullptr;
	}
	void UI_Box::SetDataSource(Variant& source)
	{
		dataSource_ = source;
		if (source.GetTypeName() == "VariantMap") {
			const VariantMap& map = source.GetVariantMap();
			Vector<StringHash> keys = map.Keys();
			UI_Box* node = nullptr;
			for(unsigned i = 0;i<keys.Size();i++)
			{
				node = GetChild(keys[i]);
				if (node != nullptr) {
					Variant* value = map[keys[i]];
					node->SetDataSource(*value);
				}
			
			}
		}
	}
}
