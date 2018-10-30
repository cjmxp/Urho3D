#pragma once

#include "../UI/UI_CheckBox.h"

namespace Urho3D
{
    class URHO3D_API UI_Radio : public UI_CheckBox
    {
        URHO3D_OBJECT(UI_Radio, UI_CheckBox);
    public:
        /// Construct.
        explicit UI_Radio(Context* context);
        /// Destruct.
        ~UI_Radio() override;
		/// React to mouse click begin.
		virtual void OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, int button, int buttons, int qualifiers, Cursor* cursor) override;
		virtual void InitAttribute() override;
    };
}
