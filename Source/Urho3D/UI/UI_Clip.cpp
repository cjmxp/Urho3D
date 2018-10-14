#include "../UI/UI_Clip.h"
namespace Urho3D
{
	UI_Clip::UI_Clip(Context* context) :
		UI_Box(context),
		sizeGrid_(IntRect::ZERO),
        imageRect_(IntRect::ZERO),
		blendMode_(BLEND_REPLACE)
	{
		
	}

	UI_Clip::~UI_Clip() = default;

	void UI_Clip::SetIndex(int i)
    {
		if (i < 0)i = 0;
		if (i >= clipX_ * clipY_) i = 0;
		
		index_ = i;
		if (texture_) {
			int tw = texture_->GetWidth()/ clipX_;
			int th = texture_->GetHeight()/ clipY_;
			int y = index_ / clipX_;
			int x = index_ % clipX_;
			SetImageRect(IntRect(x*tw, y*th, tw, th));
		}
	}
    const String& UI_Clip::GetSkin()
    {
        return skin_;
    }
    void UI_Clip::SetSkin(const String& skin)
    {
        if(skin_ != skin && skin!=""){
            skin_ = skin;
            auto* cache = GetSubsystem<ResourceCache>();
            auto* tex = cache->GetResource<Texture2D>(skin);
            SetTexture(tex);
        }
    }
    const String UI_Clip::GetSizeGrid(){
        return ToString("%d,%d,%d,%d",sizeGrid_.Min().x_,sizeGrid_.Min().y_,sizeGrid_.Max().x_,sizeGrid_.Max().y_);
    }
    
	void UI_Clip::SetSizeGrid(const String& value)
	{
        Rect ret = ToRect(value);
        sizeGrid_ = IntRect((int)ret.Min().x_, (int)ret.Min().y_, (int)ret.Max().x_, (int)ret.Max().y_);
		
	}
	void UI_Clip::SetClipX(int i) {
		if (i <= 0) {
			clipX_ = 1;
		}else {
			clipX_ = i;
		}
	}

	void UI_Clip::SetClipY(int i) {
		if (i <= 0) {
			clipY_ = 1;
		}
		else {
			clipY_ = i;
		}
	}

	int UI_Clip::GetIndex() {
		return index_;
	}
	
	int UI_Clip::GetClipX() {
		return clipX_;
	}

	int UI_Clip::GetClipY() {
		return clipY_;
	}

	void UI_Clip::SetTexture(Texture* texture)
	{
		texture_ = texture;
		if (imageRect_ == IntRect::ZERO) {
			if (texture_){
                if(drawRect_==IntVector2::ZERO){
                    drawRect_.x_ = texture_->GetWidth()/ clipX_;
                    drawRect_.y_ = texture_->GetHeight()/ clipY_;
                }
                if (GetWidth() <= 0 || GetHeight() <= 0) SetSize(drawRect_.x_,drawRect_.y_);
				SetIndex(index_);
			}
		}
	}
    const IntVector2& UI_Clip::GetDrawRect(){
        return GetSize();
    }
	void UI_Clip::SetImageRect(const IntRect& rect)
	{
		if (rect != IntRect::ZERO)
			imageRect_ = rect;
	}

	void UI_Clip::SetBlendMode(BlendMode mode)
	{
		blendMode_ = mode;
	}
	bool UI_Clip::IsWithinScissor(const IntRect& currentScissor)
	{
		/// \todo Implement properly, for now just checks visibility flag
		return visible_;
	}
	void UI_Clip::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor)
	{
		Refresh();
		bool allOpaque = true;
		if (GetDerivedOpacity() < 1.0f || colors_[C_TOPLEFT].a_ < 1.0f || colors_[C_TOPRIGHT].a_ < 1.0f ||
			colors_[C_BOTTOMLEFT].a_ < 1.0f || colors_[C_BOTTOMRIGHT].a_ < 1.0f)
			allOpaque = false;

		UIBatch batch(this, blendMode_ == BLEND_REPLACE && !allOpaque ? BLEND_ALPHA : blendMode_, currentScissor, texture_, &vertexData);
		
		// Calculate size of the inner rect, and texture dimensions of the inner rect
		const IntRect& uvBorder = sizeGrid_;
		int x = GetIndentWidth();
		IntVector2 size = GetDrawRect();
		size.x_ -= x;
		IntVector2 innerSize(
			Max(size.x_ - sizeGrid_.left_ - sizeGrid_.right_, 0),
			Max(size.y_ - sizeGrid_.top_ - sizeGrid_.bottom_, 0));
		IntVector2 innerUvSize(
			Max(imageRect_.right_  - uvBorder.left_ - uvBorder.right_, 0),
			Max(imageRect_.bottom_ - uvBorder.top_ - uvBorder.bottom_, 0));

		IntVector2 uvTopLeft(imageRect_.left_, imageRect_.top_);
		//uvTopLeft += offset;
		
		// Top
		if (sizeGrid_.top_)
		{
			if (sizeGrid_.left_)
				batch.AddQuad(GetTransform(), x, 0, sizeGrid_.left_, sizeGrid_.top_, uvTopLeft.x_, uvTopLeft.y_, uvBorder.left_, uvBorder.top_);
			if (innerSize.x_)
				batch.AddQuad(GetTransform(), x + sizeGrid_.left_, 0, innerSize.x_, sizeGrid_.top_, uvTopLeft.x_ + uvBorder.left_, uvTopLeft.y_,
					innerUvSize.x_, uvBorder.top_);//true
			if (sizeGrid_.right_)
				batch.AddQuad(GetTransform(), x + sizeGrid_.left_ + innerSize.x_, 0, sizeGrid_.right_, sizeGrid_.top_,
					uvTopLeft.x_ + uvBorder.left_ + innerUvSize.x_, uvTopLeft.y_, uvBorder.right_, uvBorder.top_);
		}
		// Middle
		if (innerSize.y_)
		{
			if (sizeGrid_.left_)
				batch.AddQuad(GetTransform(), x, sizeGrid_.top_, sizeGrid_.left_, innerSize.y_, uvTopLeft.x_, uvTopLeft.y_ + uvBorder.top_,
					uvBorder.left_, innerUvSize.y_);//false
			if (innerSize.x_)
				batch.AddQuad(GetTransform(), x + sizeGrid_.left_, sizeGrid_.top_, innerSize.x_, innerSize.y_, uvTopLeft.x_ + uvBorder.left_,
					uvTopLeft.y_ + uvBorder.top_, innerUvSize.x_, innerUvSize.y_);//false
			if (sizeGrid_.right_)
				batch.AddQuad(GetTransform(), x + sizeGrid_.left_ + innerSize.x_, sizeGrid_.top_, sizeGrid_.right_, innerSize.y_,
					uvTopLeft.x_ + uvBorder.left_ + innerUvSize.x_, uvTopLeft.y_ + uvBorder.top_, uvBorder.right_, innerUvSize.y_);//false
		}
		// Bottom
		if (sizeGrid_.bottom_)
		{
			if (sizeGrid_.left_)
				batch.AddQuad(GetTransform(), x, sizeGrid_.top_ + innerSize.y_, sizeGrid_.left_, sizeGrid_.bottom_, uvTopLeft.x_,
					uvTopLeft.y_ + uvBorder.top_ + innerUvSize.y_, uvBorder.left_, uvBorder.bottom_);
			if (innerSize.x_)
				batch.AddQuad(GetTransform(), x + sizeGrid_.left_, sizeGrid_.top_ + innerSize.y_, innerSize.x_, sizeGrid_.bottom_,
					uvTopLeft.x_ + uvBorder.left_, uvTopLeft.y_ + uvBorder.top_ + innerUvSize.y_, innerUvSize.x_, uvBorder.bottom_);//true
			if (sizeGrid_.right_)
				batch.AddQuad(GetTransform(), x + sizeGrid_.left_ + innerSize.x_, sizeGrid_.top_ + innerSize.y_, sizeGrid_.right_, sizeGrid_.bottom_,
					uvTopLeft.x_ + uvBorder.left_ + innerUvSize.x_, uvTopLeft.y_ + uvBorder.top_ + innerUvSize.y_, uvBorder.right_,
					uvBorder.bottom_);
		}

		UIBatch::AddOrMerge(batch, batches);

		// Reset hovering for next frame
		hovering_ = false;
	}
}
