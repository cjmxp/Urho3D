#pragma once
#include "../UI/UI_Label.h"
#include "../UI/UI_Clip.h"

namespace Urho3D
{
    class URHO3D_API UI_Button : public UI_Clip
    {
        URHO3D_OBJECT(UI_Button, UI_Clip);
    public:
        /// Construct.
        explicit UI_Button(Context* context);
        /// Destruct.
        ~UI_Button() override;
        const String& GetLable()const;
        void SetLable(const String& v);
        /// Perform UI element update.
        void Update(float timeStep) override;
		/// Return UI rendering batches.
		void GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override;
        /// React to mouse click begin.
        virtual void OnClickBegin (const IntVector2& position, const IntVector2& screenPosition, int button, int buttons, int qualifiers, Cursor* cursor) override;
        /// React to mouse click end.
        virtual void OnClickEnd (const IntVector2& position, const IntVector2& screenPosition, int button, int buttons, int qualifiers, Cursor* cursor, UIElement* beginElement) override;
		const String& GetColor()const { return color_; };
		void SetColor(const String& value);
		const String& GetFont()const { return font_; };
		void SetFont(const String& value);
		int GetFontSize() { return fontSize_; };
		void SetFontSize(int v);
		bool GetSelected();
		void SetSelected(bool v);
		const String& GetValue()const { return value_; };
		void SetValue(const String & v);
		virtual void InitAttribute(UI_Box* box = nullptr) override;
		virtual void SetDataSource(Variant& source) override;
	protected:
		int fontSize_{ 0 };
		String color_{ String::EMPTY };
		String font_{ String::EMPTY };
		bool selected_{ false };
		bool pressed_{ false };
		String value_{String::EMPTY};
		virtual void Layout() override;
		SharedPtr<UI_Label> lable_;
    };
}
