#pragma once

#include "../Core/StringUtils.h"
#include "../Graphics/Texture.h"
#include "../Graphics/Texture2D.h"
#include "../Resource/ResourceCache.h"
#include "../UI/UI_Box.h"

namespace Urho3D
{
	class URHO3D_API UI_Clip : public UI_Box
	{
		URHO3D_OBJECT(UI_Clip, UI_Box);
	public:
		/// Construct.
		explicit UI_Clip(Context* context);
		/// Destruct.
		~UI_Clip() override;
        
        void SetSkin(const String& skin);
        const String& GetSkin();
        void SetSizeGrid(const String& rect);
        const String GetSizeGrid();
        void SetIndex(int);
        void SetClipX(int);
        void SetClipY(int);
        
        int GetIndex();
        int GetClipX();
        int GetClipY();

		/// Set texture.
		void SetTexture(Texture* texture);
		/// Set part of texture to use as the image.
		void SetImageRect(const IntRect& rect);
		/// Set blend mode.
		void SetBlendMode(BlendMode mode);
		/// Return texture.
		Texture* GetTexture() const { return texture_; }
		/// Return image rectangle.
		const IntRect& GetImageRect() const { return imageRect_; }
		/// Return blend mode.
		BlendMode GetBlendMode() const { return blendMode_; }
		/// Return whether is visible and inside a scissor rectangle and should be rendered.
		bool IsWithinScissor(const IntRect& currentScissor) override;
		/// Return UI rendering batches.
		void GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override;
        
    protected:
		virtual const IntVector2& GetDrawRect();
        String skin_;
		int clipX_{ 1 };
		int clipY_{ 1 };
		int index_{ 0 };
        IntVector2 drawRect_{IntVector2::ZERO};
		
		IntRect sizeGrid_{ IntRect::ZERO};
		/// Rotation angle.
		/// Texture.
		SharedPtr<Texture> texture_;
		/// Image rectangle.
		IntRect imageRect_;
		/// Blend mode flag.
		BlendMode blendMode_;
	};
}
