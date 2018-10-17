#include "../UI/UI_Group.h"
namespace Urho3D
{
	UI_Group::UI_Group(Context* context) :
		UI_Box(context),
		blendMode_(BLEND_REPLACE)
	{
		
	}

	UI_Group::~UI_Group() = default;

	
    const String& UI_Group::GetSkin()
    {
        return skin_;
    }

	void UI_Group::SetLabels(const String& labels) {
		if (labels_ != labels) {
			labels_ = labels;
		}
		Layout();
	}
	const String& UI_Group::GetLabels() {
		return labels_;
	}

	void UI_Group::SetDirection(Direction d) {
		if (dir_ != d) {
			dir_ = d;
		}
	}

	Direction UI_Group::GetDirection() {
		return dir_;
	}

    void UI_Group::SetSkin(const String& skin)
    {
        if(skin_ != skin && skin!=""){
            skin_ = skin;
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
		
	}

	void UI_Group::SetClipX(int i) {
		if (i <= 0) {
			clipX_ = 1;
		}else {
			clipX_ = i;
		}
	}

	void UI_Group::SetClipY(int i) {
		if (i <= 0) {
			clipY_ = 1;
		}
		else {
			clipY_ = i;
		}
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
		Layout();
	}
}
