#pragma once

#include "../UI/UI_Button.h"

namespace Urho3D
{
    class URHO3D_API UI_CheckBox : public UI_Button
    {
        URHO3D_OBJECT(UI_CheckBox, UI_Button);
    public:
        /// Construct.
        explicit UI_CheckBox(Context* context);
        /// Destruct.
        ~UI_CheckBox() override;
        
        /// Perform UI element update.
        void Update(float timeStep) override;
        /// React to mouse click begin.
        virtual void OnClickBegin (const IntVector2& position, const IntVector2& screenPosition, int button, int buttons, int qualifiers, Cursor* cursor) override;
        /// React to mouse click end.
        virtual void OnClickEnd (const IntVector2& position, const IntVector2& screenPosition, int button, int buttons, int qualifiers, Cursor* cursor, UIElement* beginElement) override;
		virtual void InitAttribute() override;
	protected:
		virtual void Layout() override;
		virtual const IntVector2& GetDrawRect();
		
    };
}
