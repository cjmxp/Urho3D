#pragma once
#include "../UI/UI_Clip.h"
#include "../UI/UI_Button.h"
namespace Urho3D
{
	class URHO3D_API UI_HSlider : public UI_Clip
	{
		URHO3D_OBJECT(UI_HSlider, UI_Clip);
	public:
		/// Construct.
		explicit UI_HSlider(Context* context);
		/// Destruct.
		~UI_HSlider() override;
		virtual void OnHover(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers, Cursor* cursor);
		virtual void Update(float timeStep) override;
		/// React to mouse click begin.
		virtual void OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, int button, int buttons, int qualifiers, Cursor* cursor) override;
		/// React to mouse click end.
		virtual void OnClickEnd(const IntVector2& position, const IntVector2& screenPosition, int button, int buttons, int qualifiers, Cursor* cursor, UIElement* beginElement) override;
		/// React to mouse drag begin.
		virtual void OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers, Cursor* cursor);
		/// React to mouse drag motion.
		virtual void OnDragMove (const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, int buttons, int qualifiers,Cursor* cursor);
		/// React to mouse drag end.
		virtual void OnDragEnd(const IntVector2& position, const IntVector2& screenPosition, int dragButtons, int releaseButton, Cursor* cursor);
		/// Return UI rendering batches.
		void GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override;
		void SetSkin(const String& skin);
		SharedPtr<UI_Button> button{nullptr};
		float GetValue();
		void SetValue(float v);
	protected:
		virtual void Layout();
		int offset_{ 0 };
		IntVector2 move{ IntVector2::ZERO};
	};
}
