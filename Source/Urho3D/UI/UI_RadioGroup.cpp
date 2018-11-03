#include "../UI/UI_Radio.h"
#include "../UI/UI_RadioGroup.h"
namespace Urho3D
{
	UI_RadioGroup::UI_RadioGroup(Context* context) :
		UI_Group(context)
	{
		
	}

	UI_RadioGroup::~UI_RadioGroup() = default;


	void UI_RadioGroup::SetLabels(const String& labels) {
		if (labels_ != labels) {
			labels_ = labels;
			for (unsigned i = 0; i < nodes_.Size(); i++)
			{
				nodes_[i]->SetVisible(false);
			}
			Vector<String> node = labels.Split(',');
			for (unsigned i = 0; i < node.Size(); i++)
			{
				if (i >= nodes_.Size()) {
					nodes_.Push(SharedPtr<UI_Button>(new UI_Radio(GetContext())));
					nodes_[i]->SetVisible(true);
					nodes_[i]->SetLable(node[i]);
					nodes_[i]->SetParent(this);
				}
				else {
					nodes_[i]->SetVisible(true);
					nodes_[i]->SetLable(node[i]);
				}
			}
			layout_ = true;
		}
	}
}
