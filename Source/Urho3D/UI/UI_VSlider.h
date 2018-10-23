#pragma once
#include "../UI/UI_HSlider.h"
namespace Urho3D
{
	class URHO3D_API UI_VSlider : public UI_HSlider
	{
		URHO3D_OBJECT(UI_VSlider, UI_HSlider);
	public:
		/// Construct.
		explicit UI_VSlider(Context* context);
		/// Destruct.
		~UI_VSlider() override;
		/// React to mouse drag begin.
		virtual void OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers, Cursor* cursor);
		float GetValue();
		void SetValue(float v);
	protected:
		virtual void Layout();
	};
}
