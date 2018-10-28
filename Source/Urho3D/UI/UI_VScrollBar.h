#pragma once
#include "../UI/UI_VSlider.h"
#include "../UI/UI_Button.h"
#include "../UI/UI_HScrollBar.h"

namespace Urho3D
{
	class URHO3D_API UI_VScrollBar : public UI_HScrollBar
	{
		URHO3D_OBJECT(UI_VScrollBar, UI_HScrollBar);
	public:
		/// Construct.
		explicit UI_VScrollBar(Context* context);
		/// Destruct.
		~UI_VScrollBar() override;
		virtual void OnHover(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers, Cursor* cursor);
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
	protected:
		virtual void Layout();
		virtual void init() override;
	};
}
