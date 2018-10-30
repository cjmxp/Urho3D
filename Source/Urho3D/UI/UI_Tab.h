#pragma once

#include "../UI/UI_Group.h"

namespace Urho3D
{
	class URHO3D_API UI_Tab : public UI_Group
	{
		URHO3D_OBJECT(UI_Tab, UI_Group);
	public:
		/// Construct.
		explicit UI_Tab(Context* context);
		/// Destruct.
		~UI_Tab() override;
		virtual void SetLabels(const String& value) override;
		virtual void InitAttribute() override;
	};
}
