#include "../UI/UI_List.h"
namespace Urho3D
{
	UI_List::UI_List(Context* context) :
		UI_Box(context)
	{
		
	}

	UI_List::~UI_List() = default;
	void UI_List::InitAttribute()
	{
		UI_Box::InitAttribute();
	}
}
