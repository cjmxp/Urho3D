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
        const String& GetValue();
        void SetValue(const String & v);
       
    private:
        String value_;
    };
}
