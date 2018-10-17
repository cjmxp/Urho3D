#pragma once

#include "../Core/StringUtils.h"
#include "../UI/UI_Button.h"
#include "../UI/UI_Box.h"

namespace Urho3D
{
	enum Direction
	{
		Vertical = 0,
		Horizontal
	};
	class URHO3D_API UI_Group : public UI_Box
	{
		URHO3D_OBJECT(UI_Group, UI_Box);
	public:
		/// Construct.
		explicit UI_Group(Context* context);
		/// Destruct.
		~UI_Group() override;
        
        void SetSkin(const String& skin);
        const String& GetSkin();
        void SetSizeGrid(const String& rect);
        const String GetSizeGrid();
        void SetClipX(int);
        void SetClipY(int);

        int GetClipX();
        int GetClipY();

		void SetDirection(Direction d);
		Direction GetDirection();

		virtual void SetLabels(const String& value);
		const String& GetLabels();
		/// Set blend mode.
		void SetBlendMode(BlendMode mode);
		/// Return blend mode.
		BlendMode GetBlendMode() const { return blendMode_; }
		/// Return UI rendering batches.
		void GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override;
		/// Set size.
		void SetSize(int width, int height);

    protected:
		Vector<SharedPtr<UI_Button> > nodes_;
		Direction dir_{ Direction::Vertical };
		String labels_{ String::EMPTY };
        String skin_{ String::EMPTY };
		int clipX_{ 1 };
		int clipY_{ 1 };
        IntVector2 drawRect_{IntVector2::ZERO};
		
		IntRect sizeGrid_{ IntRect::ZERO};
		/// Blend mode flag.
		BlendMode blendMode_;
	};
}
