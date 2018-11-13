#pragma once
#include "../UI/UI_Box.h"
#include "../UI/UI_VScrollBar.h"
#include "../Core/Timer.h"
namespace Urho3D
{
	class URHO3D_API UI_List : public UI_Box
	{
		URHO3D_OBJECT(UI_List, UI_Box);
	public:
		/// Construct.
		explicit UI_List(Context* context);
		/// Destruct.
		~UI_List() override;
        /// Return whether the element could handle wheel input.
        bool IsWheelHandler() const override { return true; }
        virtual void OnScroll(float value) override;
        /// React to mouse click begin.
        virtual void OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, int button, int buttons, int qualifiers, Cursor* cursor) override;
        /// React to mouse click end.
        virtual void OnClickEnd(const IntVector2& position, const IntVector2& screenPosition, int button, int buttons, int qualifiers, Cursor* cursor, UIElement* beginElement) override;
        /// React to mouse drag begin.
        virtual void OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers, Cursor* cursor) override;
        /// React to mouse drag motion.
        virtual void OnDragMove(const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, int buttons, int qualifiers, Cursor* cursor) override;
        /// React to mouse drag end.
        virtual void OnDragEnd(const IntVector2& position, const IntVector2& screenPosition, int dragButtons, int releaseButton, Cursor* cursor) override;
        /// React to mouse wheel.
        virtual void OnWheel(int delta, MouseButtonFlags buttons, QualifierFlags qualifiers) override;
		int GetRepeatX() { return repeatX_;};
		void SetRepeatX(int v) { repeatX_ = v; vary_ = true; };
		int GetRepeatY() { return repeatY_; };
		void SetRepeatY(int v) { repeatY_ = v; vary_ = true; };
		int GetSpaceX() { return spaceX_; };
		void SetSpaceX(int v) { spaceX_ = v; vary_ = true; };
		int GetSpaceY() { return spaceY_; };
		void SetSpaceY(int v) { spaceY_ = v; vary_ = true; };
		Vector<Variant>& GetValue() { return list_; };
		void SetValue(const Vector<Variant>& list) { list_ = list; vary_ = true; };
        virtual void InitAttribute(UI_Box* box = nullptr) override;
        virtual void InitChilds(UI_Box* box = nullptr) override;
		virtual void SetDataSource(Variant& source) override;
	protected:
		virtual void Layout() override;
		Vector<Variant> list_;
		SharedPtr<UI_Box> itembox_{nullptr};
		SharedPtr<UI_HScrollBar> bar_{ nullptr };
        int distance_{0};
        unsigned time_{0};
		XMLElement render_xml_{ XMLElement::EMPTY };
		XMLElement scrollbar_xml_{ XMLElement::EMPTY };
		int repeatX_{ 1 };
		int repeatY_{ 1 };
		int spaceX_{ 0 };
		int spaceY_{ 0 };
	};
}
