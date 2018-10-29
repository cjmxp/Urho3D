#pragma once

#include "../UI/UI_Box.h"

namespace Urho3D
{
	class URHO3D_API UI_List : public UI_Box
	{
		URHO3D_OBJECT(UI_List, UI_Box);
	public:
		/// Construct.
		explicit UI_List(Context* context);
		/// Destruct.
		~UI_List() override;
	};
}
