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
		SharedPtr<UI_Button> button{nullptr};
	};
}
