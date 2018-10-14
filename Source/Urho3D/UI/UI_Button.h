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
        const String& GetLable();
        void SetLable(const String& v);
        /// Perform UI element update.
        void Update(float timeStep) override;
		/// Return UI rendering batches.
		void GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override;
        /// React to mouse click begin.
        virtual void OnClickBegin (const IntVector2& position, const IntVector2& screenPosition, int button, int buttons, int qualifiers, Cursor* cursor) override;
        /// React to mouse click end.
        virtual void OnClickEnd (const IntVector2& position, const IntVector2& screenPosition, int button, int buttons, int qualifiers, Cursor* cursor, UIElement* beginElement) override;
    private:
        bool pressed_;
        SharedPtr<UI_Label> lable_;
    };
}
