#include "../UI/UI.h"
#include "../UI/UI_List.h"
namespace Urho3D
{
	UI_List::UI_List(Context* context) :
		UI_Box(context)
	{
        SetEnabled(true);
		SetClipChildren(true);
        SetEnabled(true);
        focusMode_ = FM_FOCUSABLE_DEFOCUSABLE;
        
	}

	UI_List::~UI_List() = default;
    
    void UI_List::OnScroll(float value)
    {
        if(bar_->GetName()=="hscrollbar"){
            int x = bar_->GetMax()*value;
            itembox_->SetPosition(-x,0);
        }else{
            int y = bar_->GetMax()*value;
            itembox_->SetPosition(0,-y);
        }
    }
    void UI_List::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, int button, int buttons, int qualifiers, Cursor* cursor)
    {
        if (bar_->InRect(IntRect::ZERO, position)) {
            bar_->OnClickBegin(position, screenPosition, button, buttons, qualifiers, cursor);
        }
    }
    
    void UI_List::OnClickEnd(const IntVector2& position, const IntVector2& screenPosition, int button, int buttons, int qualifiers, Cursor* cursor, UIElement* beginElement)
    {
        if (bar_->InRect(IntRect::ZERO, position)) {
            bar_->OnClickEnd(position, screenPosition, button, buttons, qualifiers, cursor, beginElement);
        }
        
    }
    
    void UI_List::OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers, Cursor* cursor)
    {
        if (bar_->InRect(IntRect::ZERO, position)) {
            bar_->OnDragBegin(position, screenPosition, buttons, qualifiers, cursor);
        }
        else{
            time_ = Time::GetSystemTime();
            if(bar_->GetName()=="hscrollbar")
            {
                distance_ = screenPosition.x_;
            }else{
                distance_ = screenPosition.y_;
            }
        }
    }
    
    void UI_List::OnDragMove(const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, int buttons, int qualifiers, Cursor* cursor)
    {
        if (bar_->InRect(IntRect::ZERO, position)) {
            bar_->OnDragMove(position, screenPosition, deltaPos, buttons, qualifiers, cursor);
        }
    }
    
    void UI_List::OnDragEnd(const IntVector2& position, const IntVector2& screenPosition, int dragButtons, int releaseButton, Cursor* cursor)
    {
        if (bar_->InRect(IntRect::ZERO, position)) {
            bar_->OnDragEnd(position, screenPosition, dragButtons, releaseButton, cursor);
        }
        else{
            time_ = Time::GetSystemTime() - time_;
            if(bar_->GetName()=="hscrollbar")
            {
                distance_ = abs(screenPosition.x_ - distance_);
            }else{
                distance_ = abs(screenPosition.y_ - distance_);
            }
            printf("距离:%u 时间:%d 平均:%f\n",distance_,time_,(float)distance_/time_);
        }
        
    }
    
    void UI_List::OnWheel(int delta, MouseButtonFlags buttons, QualifierFlags qualifiers) {
        bar_->OnWheel(delta,buttons,qualifiers);
    }
    
	void UI_List::InitAttribute(UI_Box* box_) {
		UI_Box::InitAttribute(box_);
		XMLElement root = GetRoot();
		Vector<String> names = root.GetAttributeNames();
		if (box_ == nullptr)box_ = this;
		for (unsigned i = 0; i < names.Size(); i++) {
			String name = names[i].ToLower();
			if (name == "repeatx") {
				SetRepeatX(ToInt(root.GetAttribute(names[i]).CString()));
			}
			else if (name == "repeaty") {
				SetRepeatY(ToInt(root.GetAttribute(names[i]).CString()));
			}
			else if (name == "spacex") {
				SetSpaceX(ToInt(root.GetAttribute(names[i]).CString()));
			}
			else if (name == "speacey") {
				SetSpaceY(ToInt(root.GetAttribute(names[i]).CString()));
			}
		}
	}
	void UI_List::InitChilds(UI_Box* box_)
	{
		if (box_ == nullptr)box_ = this;
        if (itembox_ == nullptr) {
            itembox_ = SharedPtr<UI_Box>(new UI_Box(GetContext()));
            itembox_->SetName("content");
            AddChild(itembox_);
        }
		XMLElement root = GetRoot();
		if (root.IsNull())return;
		XMLElement node = root.GetChild();
		while (!node.IsNull()) {
			String name = node.GetName().ToLower();
			if (node.HasAttribute("name")) {
				if (node.GetAttribute("name").ToLower() == "render" && name == "box") {
					render_xml_ = node;
				}else if (node.GetAttribute("name").ToLower() == "scrollbar" && (name == "hscrollbar" || name == "vscrollbar")) {
					scrollbar_xml_ = node;
					if (bar_ == nullptr) {
						if (name == "hscrollbar") {
							bar_ = SharedPtr<UI_HScrollBar>(new UI_HScrollBar(GetContext()));
                            bar_->SetName("hscrollbar");
						}
						else {
							bar_ = SharedPtr<UI_HScrollBar>(new UI_VScrollBar(GetContext()));
                            bar_->SetName("vscrollbar");
						}
                    
                        bar_->SetPriority(1);
                        bar_->SetXml(scrollbar_xml_);
                        bar_->InitAttribute(this);
						AddChild(bar_);
					}
				}
			}
			node = node.GetNext();
		}
	}
	void UI_List::Layout() {
		UI_Box::Layout();
		if (vary_ && list_.Size()>0 ) {
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
                    node->InitAttribute(this);
                    node->InitChilds(this);
                    x = (int)i % repeatX_;
                    y = (int)i / repeatX_;
                    x = (int)x * node->GetWidth() + x * spaceX_;
                    y = (int)y * node->GetHeight() + y * spaceY_;
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
            if(bar_->GetName()=="hscrollbar"){
                if(list_.Size() % repeatX_!=0)w+=node->GetWidth();
                itembox_->SetSize(w-spaceX_, h-spaceY_);
                int value = itembox_->GetWidth()-GetWidth();
                if(value<0)value=0;
                bar_->SetMax(value);
            }else{
                if(list_.Size() % repeatX_!=0)h+=node->GetHeight();
                itembox_->SetSize(w-spaceX_, h-spaceY_);
                int value = itembox_->GetHeight()-GetHeight();
                if(value<0)value=0;
                bar_->SetMax(value);
            }
			vary_ = false;
		}
	}
	void UI_List::SetDataSource(Variant& source)
	{
		dataSource_ = source;
		if (source.GetTypeName() == "VariantVector") {
			SetValue(source.GetVariantVector());
		}
	}
}
