#include "../UI/UI_Box.h"
#include "../UI/UIEvents.h"

namespace Urho3D
{
    UI_Box::UI_Box(Context* context) :
		UIElement(context),
		scale_(Vector2::ONE),
		rotation_(0.0f)
    {
        SetEnabled(false);
    }

    UI_Box::~UI_Box() = default;
   
    void UI_Box::UpdateLayout()
    {
        if (layoutNestingLevel_)
            return;
        // Prevent further updates while this update happens
        DisableLayoutUpdate();

        for (unsigned i = 0; i < children_.Size(); ++i)
        {
            children_[i]->UpdateLayout();
        }

        using namespace LayoutUpdated;

        VariantMap& eventData = GetEventDataMap();
        eventData[P_ELEMENT] = this;
        SendEvent(E_LAYOUTUPDATED, eventData);

        EnableLayoutUpdate();
    }

	void UI_Box::SetRotation(float angle)
	{
		if (angle != rotation_)
		{
			rotation_ = angle;
			MarkDirty();
		}
	}
	void UI_Box::SetScale(const Vector2& scale)
	{
		if (scale != scale_)
		{
			scale_ = scale;
			MarkDirty();
		}
	}
	void UI_Box::SetScale(float x, float y)
	{
		SetScale(Vector2(x, y));
	}
	const Matrix3x4& UI_Box::GetTransform() const {
		if (positionDirty_)
		{
			Matrix3x4 parentTransform = Matrix3x4::IDENTITY;
			if (parent_){
				const IntVector2& parentScreenPos = parent_->GetScreenPosition() + parent_->GetChildOffset();
				parentTransform.SetTranslation(Vector3((float)parentScreenPos.x_, (float)parentScreenPos.y_, 0.0f));
			}

			Matrix3x4 mainTransform(Vector3((float)position_.x_, (float)position_.y_, 0.0f), Quaternion(rotation_, Vector3::FORWARD), Vector3(scale_.x_, scale_.y_, 1.0f));

			transform_ = parentTransform * mainTransform;
			positionDirty_ = false;
			// Calculate an approximate screen position for GetElementAt(), or pixel-perfect child elements
			Vector3 topLeftCorner = transform_ * Vector3::ZERO;
			screenPosition_ = IntVector2((int)topLeftCorner.x_, (int)topLeftCorner.y_);
		}
		return transform_;
	}

	const IntVector2& UI_Box::GetScreenPosition() const
	{
		// This updates screen position for a sprite
		GetTransform();
		return screenPosition_;
	}

	IntVector2 UI_Box::ScreenToElement(const IntVector2& screenPosition)
	{
		Vector3 floatPos((float)screenPosition.x_, (float)screenPosition.y_, 0.0f);
		Vector3 transformedPos = GetTransform().Inverse() * floatPos;
		return IntVector2((int)transformedPos.x_, (int)transformedPos.y_);
	}

	IntVector2 UI_Box::ElementToScreen(const IntVector2& position)
	{
		Vector3 floatPos((float)position.x_, (float)position.y_, 0.0f);
		Vector3 transformedPos = GetTransform() * floatPos;
		return IntVector2((int)transformedPos.x_, (int)transformedPos.y_);
	}
	void UI_Box::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor)
	{
		Refresh();
		// Reset hovering for next frame
		hovering_ = false;
	}
    void UI_Box::Margin(int l,int t,int r,int b,int cx,int cy){
        left_ = l;
        top_ = t;
        right_ = r;
        bottom_ = b;
        centerX_ = cx;
        centerY_ = cy;
        Refresh();
    }
	void UI_Box::Refresh() {
		RefreshSize();
		RefreshPosition();
    }
    void UI_Box::RefreshPosition(){
        int x = position_.x_;
        int y = position_.y_;
        if(left_ !=0x7FFFFFFF)x=left_;
        if(top_ !=0x7FFFFFFF)y=top_;
        if(parent_!=nullptr){
            int pw = parent_->GetWidth();
            int ph = parent_->GetHeight();
			int w = GetWidth();
			int h = GetHeight();
            if(centerX_ !=0x7FFFFFFF){
                x = (pw-w)/2+centerX_;
            }else if(left_ == 0x7FFFFFFF && right_ !=0x7FFFFFFF){
                x=pw-w-right_;
            }
            if(centerY_ !=0x7FFFFFFF){
                y = (ph-h)/2+centerY_;
            }else if(top_ ==0x7FFFFFFF && bottom_ !=0x7FFFFFFF){
                y=ph-h-bottom_;
            }
        }
		UIElement::SetPosition(IntVector2(x, y));
    }
    void UI_Box::RefreshSize(){
        if(parent_==nullptr)return;
        int pw = parent_->GetWidth();
        int ph = parent_->GetHeight();
        int w = GetWidth();
        int h = GetHeight();
        if(left_ !=0x7FFFFFFF && right_ !=0x7FFFFFFF){
            w = pw-left_ -right_;
        }
        if(top_ !=0x7FFFFFFF && bottom_ !=0x7FFFFFFF){
            h = ph-top_ -bottom_;
        }
		UIElement::SetSize(IntVector2(w, h));
    }
}
