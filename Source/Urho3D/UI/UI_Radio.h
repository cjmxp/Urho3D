#pragma once

#include "../UI/UI_Button.h"

namespace Urho3D
{
    class URHO3D_API UI_Radio : public UI_Button
    {
        URHO3D_OBJECT(UI_Radio, UI_Button);
    public:
        /// Construct.
        explicit UI_Radio(Context* context);
        /// Destruct.
        ~UI_Radio() override;
        const String& GetValue();
        void SetValue(const String & v);
        bool GetSelected();
        void SetSelected(bool v);
        void SetSizeGrid(const String& rect);
        /// Perform UI element update.
        void Update(float timeStep) override;
        /// React to mouse click begin.
        virtual void OnClickBegin (const IntVector2& position, const IntVector2& screenPosition, int button, int buttons, int qualifiers, Cursor* cursor) override;
        /// React to mouse click end.
        virtual void OnClickEnd (const IntVector2& position, const IntVector2& screenPosition, int button, int buttons, int qualifiers, Cursor* cursor, UIElement* beginElement) override;
    private:
        const IntVector2& GetDrawRect();
        String value_;
        bool selected_;
    };
}
