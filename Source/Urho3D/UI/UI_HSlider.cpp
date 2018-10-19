
#include "../UI/UI_HSlider.h"
namespace Urho3D
{
	UI_HSlider::UI_HSlider(Context* context) :
		UI_Clip(context)
	{
		button = SharedPtr<UI_Button>(new UI_Button(GetContext()));
	}

	UI_HSlider::~UI_HSlider() = default;

	

	
	
}
