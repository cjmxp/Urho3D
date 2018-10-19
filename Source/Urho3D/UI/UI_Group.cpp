#include "../UI/UI_Group.h"
#include "../UI/UIEvents.h"
namespace Urho3D
{
	UI_Group::UI_Group(Context* context) :
		UI_Box(context),
		blendMode_(BLEND_REPLACE)
	{
		SetEnabled(true);
	}

	UI_Group::~UI_Group(){};

	void UI_Group::Update(float timeStep) {
		if (vary_) {
			for (unsigned i = 0; i < nodes_.Size(); i++)
			{
				if (nodes_[i]->GetVisible()) {
					nodes_[i]->SetClipX(clipX_);
					nodes_[i]->SetClipY(clipY_);
					if (skin_ != String::EMPTY)nodes_[i]->SetSkin(skin_);
					if (grid_ != String::EMPTY)nodes_[i]->SetSizeGrid(grid_);
					if (color_ != String::EMPTY)nodes_[i]->SetColor(color_);
					if (font_ != String::EMPTY)nodes_[i]->SetFont(font_);
					if (fontSize_> 0)nodes_[i]->SetFontSize(fontSize_);
					
					nodes_[i]->Update(timeStep);
				}
			}
		}
		Layout();
		if (vary_) {
			for (unsigned i = 0; i < nodes_.Size(); i++)
			{
				if (nodes_[i]->GetVisible()) {
					nodes_[i]->Update(timeStep);
					if (selectedindex_ != -1 && i == selectedindex_) {
						nodes_[i]->SetSelected(true);
						selectedvalue_ = nodes_[i]->GetValue();
					}
				}
			}
		}
		vary_ = false;
	}

	void UI_Group::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, int button, int buttons, int qualifiers, Cursor* cursor)
	{
		if (button == MOUSEB_LEFT)
		{
			for (unsigned i = 0; i < nodes_.Size(); i++)
			{
				nodes_[i]->SetSelected(false);
			}
			for (unsigned i = 0; i < nodes_.Size(); i++)
			{
				if (nodes_[i]->GetVisible()) {
					const IntVector2& post = nodes_[i]->GetPosition();
					IntRect rect(post, post + nodes_[i]->GetSize());
					if (rect.IsInside(position) == INSIDE) {
						nodes_[i]->SetSelected(true);
						selectedvalue_ = nodes_[i]->GetValue();
						if (enabled_) {
							using namespace Pressed;
							VariantMap& eventData = GetEventDataMap();
							eventData[P_ELEMENT] = this;
							SendEvent(E_PRESSED, eventData);
						}
						break;
					}
				}
			}
		}
	}
	void UI_Group::SetSelectedIndex(int v) {
		if (selectedindex_ != v) {
			selectedindex_ = v;
			vary_ = true;
		}
		
	}
	int UI_Group::GetSelectedIndex() {
		return selectedindex_;
	}
	void UI_Group::SetColor(const String& v) {
		if (color_ != v && v != String::EMPTY) {
			color_ = v;
			vary_ = true;
		}
	}
	void UI_Group::SetFont(const String& v) {
		if (font_ != v && v != String::EMPTY) {
			font_ = v;
			vary_ = true;
		}
	}
	void UI_Group::SetFontSize(int v) {
		if (fontSize_ != v) {
			fontSize_ = v;
			vary_ = true;
		}
	}
	void UI_Group::Layout() {
		if (layout_) {
			layout_ = false;
			UI_Box::Layout();
			int len = 0;
			int w = 0;
			int h = 0;
			for (unsigned i = 0; i < nodes_.Size(); i++)
			{
				if (nodes_[i]->GetVisible()) {
					if (dir_ == Direction::Horizontal) {
						nodes_[i]->SetPosition( w , 0);
						w += nodes_[i]->GetWidth() + space_;
						h = nodes_[i]->GetHeight();
					}
					else {
						nodes_[i]->SetPosition(0, + h);
						w = nodes_[i]->GetWidth();
						h += nodes_[i]->GetHeight() + space_;
					}
					len++;
				}
			}
			if (dir_ == Direction::Horizontal) {
				UI_Box::SetSize(w- space_, h);
			}
			else {
				UI_Box::SetSize(w, h - space_);
			}
			
		}

	}

	void UI_Group::SetLabels(const String& labels) {
		if (labels_ != labels) {
			labels_ = labels;
			vary_ = true;
			layout_ = true;
		}
	}

	void UI_Group::SetDirection(Direction d) {
		if (dir_ != d) {
			dir_ = d;
			layout_ = true;
		}
	}

	Direction UI_Group::GetDirection() {
		return dir_;
	}

    void UI_Group::SetSkin(const String& skin)
    {
        if(skin_ != skin && skin!=""){
            skin_ = skin;
			vary_ = true;
        }
    }

	void UI_Group::SetSize(int width, int height) {
		
	}

    const String UI_Group::GetSizeGrid(){
        return ToString("%d,%d,%d,%d",sizeGrid_.Min().x_,sizeGrid_.Min().y_,sizeGrid_.Max().x_,sizeGrid_.Max().y_);
    }
    
	void UI_Group::SetSizeGrid(const String& value)
	{
        Rect ret = ToRect(value);
        sizeGrid_ = IntRect((int)ret.Min().x_, (int)ret.Min().y_, (int)ret.Max().x_, (int)ret.Max().y_);
		vary_ = true;
	}

	void UI_Group::SetClipX(int i) {
		if (i <= 0) {
			clipX_ = 1;
		}else {
			clipX_ = i;
		}
		vary_ = true;
	}

	void UI_Group::SetClipY(int i) {
		if (i <= 0) {
			clipY_ = 1;
		}
		else {
			clipY_ = i;
		}
		vary_ = true;
	}

	
	int UI_Group::GetClipX() {
		return clipX_;
	}

	int UI_Group::GetClipY() {
		return clipY_;
	}


	void UI_Group::SetBlendMode(BlendMode mode)
	{
		blendMode_ = mode;
	}
	void UI_Group::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor)
	{
		if (labels_ == String::EMPTY)return;
		for (unsigned i = 0; i < nodes_.Size(); i++)
		{
			if (nodes_[i]->GetVisible()) {
				nodes_[i]->GetBatches(batches, vertexData, currentScissor);
			}
		}
	}
}
