#pragma once

#include "../UI/UI_Group.h"

namespace Urho3D
{
	class URHO3D_API UI_RadioGroup : public UI_Group
	{
		URHO3D_OBJECT(UI_RadioGroup, UI_Group);
	public:
		/// Construct.
		explicit UI_RadioGroup(Context* context);
		/// Destruct.
		~UI_RadioGroup() override;
		virtual void SetLabels(const String& value) override;
	};
}
