#pragma once
#include "../Core/StringUtils.h"
#include "../UI/UIElement.h"

namespace Urho3D
{
    class UI_Label;
    class UI_Clip;
    class UI_Button;
    class UI_CheckBox;
    class UI_HScrollBar;
    class UI_VScrollBar;
    class UI_HSlider;
    class UI_VSlider;
    class UI_Radio;
    class UI_RadioGroup;
    class UI_Tab;
    class UI_Dialog;
    class UI_View;
    class UI_List;
    
    class URHO3D_API UI_Box : public UIElement
    {
        URHO3D_OBJECT(UI_Box, UIElement);
	public:
		/// Construct.
		explicit UI_Box(Context* context);
		/// Destruct.
		~UI_Box() override;
		/// Manually update layout. Should not be necessary in most cases, but is provided for completeness.
		void UpdateLayout();
		/// Perform UI element update.
		virtual void Update(float timeStep) override;
		int GetTop();
		void SetTop(int v);
		int GetLeft();
		void SetLeft(int v);
		int GetRight();
		void SetRight(int v);
		int GetBottom();
		void SetBottom(int v);
		int GetCenterX();
		void SetCenterX(int v);
		int GetCenterY();
		void SetCenterY(int v);


		/// Convert screen coordinates to element coordinates.
		IntVector2 ScreenToElement(const IntVector2& screenPosition) override;
		/// Convert element coordinates to screen coordinates.
		IntVector2 ElementToScreen(const IntVector2& position) override;
		const IntVector2& GetScreenPosition() const override;
		const Matrix3x4& GetTransform() const;
		/// Return rotation angle.
		float GetRotation() const { return rotation_; }
		/// Set rotation angle.
		void SetRotation(float angle);
		/// Return scale.
		const Vector2& GetScale() const { return scale_; }
		/// Set scale. Scale also affects child sprites.
		void SetScale(const Vector2& scale);
		/// Set scale. Scale also affects child sprites.
		void SetScale(float x, float y);
		/// Return UI rendering batches.
		virtual void GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override;
		/// Return hotspot.
		const IntVector2& GetHotSpot() const { return hotSpot_; }
		/// Set hotspot for positioning and rotation.
		void SetHotSpot(const IntVector2& hotSpot);
		/// Set hotspot for positioning and rotation.
		void SetHotSpot(int x, int y);
		bool GetVisible() { return visible_; }
		void SetParent(UIElement * parent) { parent_ = parent; };
		bool InRect(const IntRect& rect, const IntVector2& pos);
		const String& GetXml();
		virtual void SetXml(const String& str);
		virtual void SetXml(const XMLElement& xml);
		XMLElement GetRoot(const String& name = String::EMPTY);
		virtual void InitAttribute(UI_Box* box = nullptr);
		virtual void InitChilds(UI_Box* box = nullptr);
        virtual void OnScroll(float value);
        UI_Box* GetBox(const String& key) {
            if(UIElement::GetVar(key)==Variant::EMPTY)return nullptr;
            return static_cast<UI_Box*>(UIElement::GetVar(key).GetVoidPtr());
		};
        
        UI_Button* GetButton(const String& key) {
            if(UIElement::GetVar(key)==Variant::EMPTY)return nullptr;
            return static_cast<UI_Button*>(UIElement::GetVar(key).GetVoidPtr());
        };
        
        UI_CheckBox* GetCheckBox(const String& key) {
            if(UIElement::GetVar(key)==Variant::EMPTY)return nullptr;
            return static_cast<UI_CheckBox*>(UIElement::GetVar(key).GetVoidPtr());
        };
        
        UI_Clip* GetClip(const String& key) {
            if(UIElement::GetVar(key)==Variant::EMPTY)return nullptr;
            return static_cast<UI_Clip*>(UIElement::GetVar(key).GetVoidPtr());
        };
        
        UI_Dialog* GetDialog(const String& key) {
            if(UIElement::GetVar(key)==Variant::EMPTY)return nullptr;
            return static_cast<UI_Dialog*>(UIElement::GetVar(key).GetVoidPtr());
        };
        
        UI_HScrollBar* GetHScrollBar(const String& key) {
            if(UIElement::GetVar(key)==Variant::EMPTY)return nullptr;
            return static_cast<UI_HScrollBar*>(UIElement::GetVar(key).GetVoidPtr());
        };
        
        UI_HSlider* GetHSlider(const String& key) {
            if(UIElement::GetVar(key)==Variant::EMPTY)return nullptr;
            return static_cast<UI_HSlider*>(UIElement::GetVar(key).GetVoidPtr());
        };
        
        UI_Label* GetLabel(const String& key) {
            if(UIElement::GetVar(key)==Variant::EMPTY)return nullptr;
            return static_cast<UI_Label*>(UIElement::GetVar(key).GetVoidPtr());
        };
        
        UI_List* GetList(const String& key) {
            if(UIElement::GetVar(key)==Variant::EMPTY)return nullptr;
            return static_cast<UI_List*>(UIElement::GetVar(key).GetVoidPtr());
        };
        
        UI_Radio* GetRadio(const String& key) {
            if(UIElement::GetVar(key)==Variant::EMPTY)return nullptr;
            return static_cast<UI_Radio*>(UIElement::GetVar(key).GetVoidPtr());
        };
        
        UI_RadioGroup* GetRadioGroup(const String& key) {
            if(UIElement::GetVar(key)==Variant::EMPTY)return nullptr;
            return static_cast<UI_RadioGroup*>(UIElement::GetVar(key).GetVoidPtr());
        };
        
        UI_Tab* GetTab(const String& key) {
            if(UIElement::GetVar(key)==Variant::EMPTY)return nullptr;
            return static_cast<UI_Tab*>(UIElement::GetVar(key).GetVoidPtr());
        };
        
        UI_VScrollBar* GetVScrollBar(const String& key) {
            if(UIElement::GetVar(key)==Variant::EMPTY)return nullptr;
            return static_cast<UI_VScrollBar*>(UIElement::GetVar(key).GetVoidPtr());
        };
        
        UI_VSlider* GetVSlider(const String& key) {
            if(UIElement::GetVar(key)==Variant::EMPTY)return nullptr;
            return static_cast<UI_VSlider*>(UIElement::GetVar(key).GetVoidPtr());
        };
        
        UI_View* GetView(const String& key) {
            if(UIElement::GetVar(key)==Variant::EMPTY)return nullptr;
            return static_cast<UI_View*>(UIElement::GetVar(key).GetVoidPtr());
        };
        
		const Variant& GetDataSource() { return dataSource_; };
		virtual void SetDataSource(Variant& source);
		UI_Box* GetChild(const StringHash& name);
	protected:
		virtual void Layout();
		Vector2 scale_{ Vector2::ONE };
		float rotation_{0.0f};
		bool layout_{ false };
		String grid_{ String::EMPTY };
		bool vary_{ false };
		String xml_str_{String::EMPTY};
		XMLElement xml_{ XMLElement::EMPTY };
		Variant dataSource_{ Variant::EMPTY };
	private:
		SharedPtr<XMLFile> xmlfile_{nullptr};
		/// Hotspot for positioning and rotation.
		IntVector2 hotSpot_{ IntVector2::ZERO };
		/// Transform matrix.
		mutable Matrix3x4 transform_;
		int left_{ -1 };
		int top_{ -1 };
		int right_{ -1 };
		int bottom_{ -1 };
		int centerX_{ -1 };
		int centerY_{ -1 };
		void RefreshPosition();
		void RefreshSize();
	};
}
