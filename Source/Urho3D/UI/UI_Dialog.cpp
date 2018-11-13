#include "../UI/UI_Dialog.h"
#include "../UI/UI.h"
namespace Urho3D
{
	UI_Dialog::UI_Dialog(Context* context) :
	UI_Box(context)
	{
	}

	UI_Dialog::~UI_Dialog(){};

	void UI_Dialog::Show()
	{
		auto* ui = GetSubsystem<UI>();
		if(ui!=nullptr){
            ui->SetModalElement(this, true);
		}
	}

	void UI_Dialog::Close()
	{
        Remove();
    }
}
