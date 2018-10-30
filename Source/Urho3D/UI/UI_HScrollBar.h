#pragma once
#include "../UI/UI_HSlider.h"
#include "../UI/UI_Button.h"
#include "../UI/UI_Box.h"
namespace Urho3D
{
	class URHO3D_API UI_HScrollBar : public UI_Box
	{
		URHO3D_OBJECT(UI_HScrollBar, UI_Box);
	public:
		/// Construct.
		explicit UI_HScrollBar(Context* context);
		/// Destruct.
		~UI_HScrollBar() override;
		virtual void OnHover(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers, Cursor* cursor);
		virtual void Update(float timeStep) override;
		/// React to mouse click begin.
		virtual void OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, int button, int buttons, int qualifiers, Cursor* cursor) override;
		/// React to mouse click end.
		virtual void OnClickEnd(const IntVector2& position, const IntVector2& screenPosition, int button, int buttons, int qualifiers, Cursor* cursor, UIElement* beginElement) override;
		/// React to mouse drag begin.
		virtual void OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers, Cursor* cursor);
		/// React to mouse drag motion.
		virtual void OnDragMove(const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, int buttons, int qualifiers, Cursor* cursor);
		/// React to mouse drag end.
		virtual void OnDragEnd(const IntVector2& position, const IntVector2& screenPosition, int dragButtons, int releaseButton, Cursor* cursor);
		/// Return UI rendering batches.
		void GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override;
		SharedPtr<UI_Button> up_{ nullptr };
		SharedPtr<UI_HSlider> slider_{ nullptr };
		SharedPtr<UI_Button> down_{ nullptr };
		void SetSkin(const String& skin);
		const String& GetSkin();
		float GetValue();
		void SetValue(float v);
		virtual void InitAttribute() override;
	protected:
		String skin_{String::EMPTY};
		IntVector2 pos_{ IntVector2::ZERO };
		bool onDrag_{ false };
		virtual void Layout();
		virtual void init();
	};
}
