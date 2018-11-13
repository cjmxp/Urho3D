#pragma once

#include "../UI/UI_Box.h"

namespace Urho3D
{
	class URHO3D_API UI_Dialog : public UI_Box
	{
		URHO3D_OBJECT(UI_Dialog, UI_Box);
	public:
		/// Construct.
		explicit UI_Dialog(Context* context);
		/// Destruct.
		~UI_Dialog() override;
		void Show();
		void Close();
	};
}
