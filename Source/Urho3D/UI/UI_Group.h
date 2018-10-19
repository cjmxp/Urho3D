#pragma once

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
		const String& GetSkin()const { return skin_; };
        void SetSizeGrid(const String& rect);
        const String GetSizeGrid();
        void SetClipX(int);
        void SetClipY(int);
		int GetSelectedIndex();
		void SetSelectedIndex(int index);
		const String& GetSelectedValue()const { return selectedvalue_; };
        int GetClipX();
        int GetClipY();

		int GetSpace() { return space_; };
		void SetSpace(int v) { space_ = v; };
		void SetDirection(Direction d);
		Direction GetDirection();

		virtual void Update(float timeStep) override;
		virtual void SetLabels(const String& value);
		const String& GetLabels()const { return labels_; };
		/// Set blend mode.
		void SetBlendMode(BlendMode mode);
		/// Return blend mode.
		BlendMode GetBlendMode() const { return blendMode_; }
		/// React to mouse click begin.
		virtual void OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, int button, int buttons, int qualifiers, Cursor* cursor) override;
		/// Return UI rendering batches.
		void GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override;
		/// Set size.
		void SetSize(int width, int height);
		const String& GetColor()const { return color_; };
		void SetColor(const String& value);
		const String& GetFont()const { return font_; };
		void SetFont(const String& value);
		int GetFontSize() { return fontSize_; };
		void SetFontSize(int v);
	protected:
		int fontSize_{ 0 };
		String color_{ String::EMPTY };
		String font_{ String::EMPTY };
		String selectedvalue_{ String::EMPTY };
		int selectedindex_{ -1 };
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
