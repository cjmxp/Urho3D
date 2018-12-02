#pragma once

#include "../UI/UI_Clip.h"
namespace Urho3D
{

	class URHO3D_API UI_Dialog : public Object
	{
		URHO3D_OBJECT(UI_Dialog, Object);
	public:
		/// Construct.
		explicit UI_Dialog(Context* context);
		/// Destruct.
		~UI_Dialog() override;
		void Show(bool mode =false);
		void Close();
		void SetXml(const String& str);
		void InitAttribute();
		void InitChilds();
	private:
		bool mode_{ false };
		static int mode_count_;
		SharedPtr<UI_Box> box_{ nullptr };
	};
}
