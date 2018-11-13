#pragma once

#include "../UI/UI_Box.h"

namespace Urho3D
{
	class URHO3D_API UI_View : public UI_Box
	{
		URHO3D_OBJECT(UI_View, UI_Box);
	public:
		/// Construct.
		explicit UI_View(Context* context);
		/// Destruct.
		~UI_View() override;
	};
}
