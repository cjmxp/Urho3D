#include "../UI/UI_Button.h"
#include "../UI/UI_Tab.h"
namespace Urho3D
{
	UI_Tab::UI_Tab(Context* context) :
		UI_Group(context)
	{
		
	}

	UI_Tab::~UI_Tab() = default;

	void UI_Tab::SetLabels(const String& labels) {
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
					nodes_.Push(SharedPtr<UI_Button>(new UI_Button(GetContext())));
					nodes_[i]->SetVisible(true);
					nodes_[i]->SetLable(node[i]);
				}
				else {
					nodes_[i]->SetVisible(true);
					nodes_[i]->SetLable(node[i]);
				}
			}
			layout_ = true;
		}
	}

	void UI_Tab::Layout() {
		if (layout_) {
			layout_ = false;
			UI_Box::Layout();
			int len = 0;
			for (unsigned i = 0; i < nodes_.Size(); i++)
			{
				if (nodes_[i]->GetVisible()) {
					nodes_[i]->SetClipX(clipX_);
					nodes_[i]->SetClipX(clipY_);
					if (skin_ != String::EMPTY)nodes_[i]->SetSkin(skin_);
					if (grid_ != String::EMPTY)nodes_[i]->SetSizeGrid(grid_);
					if (dir_ == Direction::Horizontal) {
						
					}
					len++;
				}
			}
		}
		
	}
	
}
