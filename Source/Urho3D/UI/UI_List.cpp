#include "../UI/UI_List.h"
namespace Urho3D
{
	UI_List::UI_List(Context* context) :
		UI_Box(context)
	{
		
	}

	UI_List::~UI_List() = default;

	void UI_List::InitChilds(UI_Box* box_)
	{
		if (box_ == nullptr)box_ = this;
		XMLElement root = GetRoot();
		if (root.IsNull())return;
		XMLElement node = root.GetChild();
		while (!node.IsNull()) {
			String name = node.GetName().ToLower();
			if (node.HasAttribute("name")) {
				if (node.GetAttribute("name") == "render" && name == "box") {
					render_ = node;
					
				}else if (node.GetAttribute("name") == "scrollbar" && (name == "hscrollbar" || name == "vscrollbar")) {
					scrollbar_ = node;
				}
			}
			node = node.GetNext();
		}
	}
}
