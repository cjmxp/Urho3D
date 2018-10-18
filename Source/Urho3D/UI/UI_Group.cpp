#include "../UI/UI_Group.h"
namespace Urho3D
{
	UI_Group::UI_Group(Context* context) :
		UI_Box(context),
		blendMode_(BLEND_REPLACE)
	{
		
	}

	UI_Group::~UI_Group() = default;

	void UI_Group::Update(float timeStep) {
		if (vary_) {
			for (unsigned i = 0; i < nodes_.Size(); i++)
			{
				if (nodes_[i]->GetVisible()) {
					nodes_[i]->SetClipX(clipX_);
					nodes_[i]->SetClipY(clipY_);
					if (skin_ != String::EMPTY)nodes_[i]->SetSkin(skin_);
					if (grid_ != String::EMPTY)nodes_[i]->SetSizeGrid(grid_);
					nodes_[i]->Update(timeStep);
				}
			}
		}
		Layout();
		for (unsigned i = 0; i < nodes_.Size(); i++)
		{
			if (nodes_[i]->GetVisible()) {
				nodes_[i]->Update(timeStep);
			}
		}
	}

	void UI_Group::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, int button, int buttons, int qualifiers, Cursor* cursor)
	{
		if (button == MOUSEB_LEFT)
		{
		}
	}

	void UI_Group::OnClickEnd(const IntVector2& position, const IntVector2& screenPosition, int button, int buttons, int qualifiers, Cursor* cursor, UIElement* beginElement)
	{
	
	}
	void UI_Group::Layout() {
		if (layout_) {
			layout_ = false;
			UI_Box::Layout();
			int len = 0;
			int var = 0;
			const IntVector2& pos = GetPosition();
			for (unsigned i = 0; i < nodes_.Size(); i++)
			{
				if (nodes_[i]->GetVisible()) {
					if (dir_ == Direction::Horizontal) {
						nodes_[i]->SetPosition(pos.x_ + var + space_, pos.y_);
						var += nodes_[i]->GetWidth() + space_;
					}
					else {
						nodes_[i]->SetPosition(pos.x_, pos.y_ + var + space_);
						var += nodes_[i]->GetHeight() + space_;
					}
					len++;
				}
			}
		}

	}
    const String& UI_Group::GetSkin()
    {
        return skin_;
    }

	void UI_Group::SetLabels(const String& labels) {
		if (labels_ != labels) {
			labels_ = labels;
			vary_ = true;
			layout_ = true;
		}
	}
	const String& UI_Group::GetLabels() {
		return labels_;
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
