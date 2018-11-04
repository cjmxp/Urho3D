#pragma once
#include "../UI/UI_Box.h"
#include "../UI/UI_VScrollBar.h"

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
		virtual void InitAttribute(UI_Box* box = nullptr);
		virtual void InitChilds(UI_Box* box = nullptr) override;
		int GetRepeaX() { return repeaX_;};
		void SetRepeaX(int v) { repeaX_ = v; vary_ = true; };
		int GetRepeaY() { return repeaY_; };
		void SetRepeaY(int v) { repeaY_ = v; vary_ = true; };
		int GetSpeaceX() { return speaceX_; };
		void SetSpeaceX(int v) { speaceX_ = v; vary_ = true; };
		int GetSpeaceY() { return speaceY_; };
		void SetSpeaceY(int v) { speaceY_ = v; vary_ = true; };
		Vector<Variant>& GetValue() { return list_; };
		void SetValue(const Vector<Variant>& list) { list_ = list; vary_ = true; };
		virtual void SetDataSource(Variant& source) override;
	protected:
		virtual void Layout() override;
		Vector<Variant> list_;
		SharedPtr<UI_Box> itembox_{nullptr};
		SharedPtr<UI_HScrollBar> bar_{ nullptr };
		
		XMLElement render_xml_{ XMLElement::EMPTY };
		XMLElement scrollbar_xml_{ XMLElement::EMPTY };
		int repeaX_{ 0 };
		int repeaY_{ 0 };
		int speaceX_{ 0 };
		int speaceY_{ 0 };
	};
}
