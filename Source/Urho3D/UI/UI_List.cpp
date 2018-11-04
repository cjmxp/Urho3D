#include "../UI/UI_List.h"
namespace Urho3D
{
	UI_List::UI_List(Context* context) :
		UI_Box(context)
	{
		SetClipChildren(true);
	}

	UI_List::~UI_List() = default;
	void UI_List::InitAttribute(UI_Box* box_) {
		UI_Box::InitAttribute(box_);
		XMLElement root = GetRoot();
		Vector<String> names = root.GetAttributeNames();
		if (box_ == nullptr)box_ = this;
		for (unsigned i = 0; i < names.Size(); i++) {
			String name = names[i].ToLower();
			if (name == "repeax") {
				SetRepeaX(ToInt(root.GetAttribute(names[i]).CString()));
			}
			else if (name == "repeay") {
				SetRepeaY(ToInt(root.GetAttribute(names[i]).CString()));
			}
			else if (name == "speacex") {
				SetSpeaceX(ToInt(root.GetAttribute(names[i]).CString()));
			}
			else if (name == "speacey") {
				SetSpeaceY(ToInt(root.GetAttribute(names[i]).CString()));
			}
		}
	}
	void UI_List::InitChilds(UI_Box* box_)
	{
		if (box_ == nullptr)box_ = this;
		if (itembox_ == nullptr) {
			SharedPtr<UI_Box> itembox_ = SharedPtr<UI_Box>(new UI_Box(GetContext()));
			AddChild(itembox_);
		}
		XMLElement root = GetRoot();
		if (root.IsNull())return;
		XMLElement node = root.GetChild();
		while (!node.IsNull()) {
			String name = node.GetName().ToLower();
			if (node.HasAttribute("name")) {
				if (node.GetAttribute("name") == "render" && name == "box") {
					render_xml_ = node;
					
				}else if (node.GetAttribute("name") == "scrollbar" && (name == "hscrollbar" || name == "vscrollbar")) {
					scrollbar_xml_ = node;
					if (bar_ == nullptr) {
						if (name == "hscrollbar") {
							SharedPtr<UI_HScrollBar> bar_ = SharedPtr<UI_HScrollBar>(new UI_HScrollBar(GetContext()));
						}
						else {
							SharedPtr<UI_HScrollBar> bar_ = SharedPtr<UI_HScrollBar>(new UI_VScrollBar(GetContext()));
						}
						AddChild(bar_);
					}
				}
			}
			node = node.GetNext();
		}
	}
	void UI_List::Layout() {
		UI_Box::Layout();
		if (vary_ && list_.Size()>0) {
			const Vector<SharedPtr<UIElement>>& childs = itembox_->GetChildren();
			for (unsigned i = 0; i < childs.Size(); i++) {
				childs[i]->SetVisible(false);
			}
			int x = 0;
			int y = 0;
			int w = 0;
			int h = 0;
			UI_Box* node = nullptr;
			for (unsigned i = 0; i < list_.Size(); i++) {
				if (i >= childs.Size()) {
					node = new UI_Box(GetContext());
					node->SetXml(render_xml_);
					x = i % repeaX_;
					y = i / repeaX_;
					x = x * node->GetWidth() + x * speaceX_;
					y = y * node->GetHeight() + y * speaceY_;
					node->SetPosition(x,y);
					node->SetVisible(true);
					if (x > w)w = x;
					if (y > h)h = y;
					itembox_->AddChild(node);
				}
				else {
					node = static_cast<UI_Box*>(childs[i].Get());
				}
				node->SetDataSource(list_[i]);
			}
			vary_ = false;
		}
	}
	void UI_List::SetDataSource(Variant& source)
	{
		dataSource_ = source;
		if (source.GetTypeName() == "VariantVector") {
			const VariantVector& value = source.GetVariantVector();
			SetValue(value);
		}
	}
}
