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

		virtual void Update(float timeStep) override;
		virtual void SetLabels(const String& value);
		const String& GetLabels();
		/// Set blend mode.
		void SetBlendMode(BlendMode mode);
		/// Return blend mode.
		BlendMode GetBlendMode() const { return blendMode_; }
		/// React to mouse click begin.
		virtual void OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, int button, int buttons, int qualifiers, Cursor* cursor) override;
		/// React to mouse click end.
		virtual void OnClickEnd(const IntVector2& position, const IntVector2& screenPosition, int button, int buttons, int qualifiers, Cursor* cursor, UIElement* beginElement) override;
		/// Return UI rendering batches.
		void GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override;
		/// Set size.
		void SetSize(int width, int height);

	protected:
		int space_{ 1 };
		Vector<SharedPtr<UI_Button> > nodes_;
		Direction dir_{ Direction::Horizontal };
		String labels_{ String::EMPTY };
        String skin_{ String::EMPTY };
		int clipX_{ 1 };
		int clipY_{ 1 };
        IntVector2 drawRect_{IntVector2::ZERO};
		virtual void Layout() override;
		IntRect sizeGrid_{ IntRect::ZERO};
		/// Blend mode flag.
		BlendMode blendMode_;
	};
}
