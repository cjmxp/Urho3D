#include "../UI/UI_Dialog.h"
#include "../UI/UI.h"
namespace Urho3D
{
	int UI_Dialog::mode_count_ = 0;
	UI_Dialog::UI_Dialog(Context* context) :
	Object(context)
	{
		box_ = SharedPtr<UI_Box>(new UI_Box(context));
		auto* ui = GetSubsystem<UI>();
		if (ui->GetRootModalElement()->GetNumChildren(false) == 0) {
			UI_Clip* mode = new UI_Clip(GetContext());
			mode->SetEnabled(true);
			mode->SetName("mode");
			mode->SetSkin("mode.png");
			mode->SetSize(ui->GetRootModalElement()->GetSize());
			ui->GetRootModalElement()->AddChild(mode);
		}
	}

	UI_Dialog::~UI_Dialog(){};
	void UI_Dialog::SetXml(const String& str) {
		box_->SetXml(str);
	}
	void UI_Dialog::InitAttribute() {
		box_->InitAttribute();
	}
	void UI_Dialog::InitChilds() {
		box_->InitChilds();
	}
	void UI_Dialog::Show(bool mode)
	{
		auto* ui = GetSubsystem<UI>();
		if(ui!=nullptr){
			if (box_->GetParent() != nullptr) {
				box_->Remove();
			}
			else if (mode) {
				mode_ = mode;
				ui->GetRootModalElement()->GetChild(0)->SetVisible(true);
				mode_count_++;
			}
			ui->GetRootModalElement()->AddChild(box_);
		}
	}

	void UI_Dialog::Close()
	{
		box_->Remove();
		if (mode_) {
			mode_count_--;
			mode_ = false;
		}
		if (mode_count_<=0) {
			auto* ui = GetSubsystem<UI>();
			ui->GetRootModalElement()->GetChild(0)->SetVisible(false);
		}
    }
}
