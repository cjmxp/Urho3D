#pragma once
#include "../Core/StringUtils.h"
#include "../UI/UIElement.h"

namespace Urho3D
{
    class URHO3D_API UI_Box : public UIElement
    {
        URHO3D_OBJECT(UI_Box, UIElement);
	public:
		/// Construct.
		explicit UI_Box(Context* context);
		/// Destruct.
		~UI_Box() override;
		/// Manually update layout. Should not be necessary in most cases, but is provided for completeness.
		void UpdateLayout();
		void Margin(int l, int t, int r, int b, int cx, int cy);
		/// Convert screen coordinates to element coordinates.
		IntVector2 ScreenToElement(const IntVector2& screenPosition) override;
		/// Convert element coordinates to screen coordinates.
		IntVector2 ElementToScreen(const IntVector2& position) override;
		const IntVector2& GetScreenPosition() const override;
		const Matrix3x4& GetTransform() const;
		/// Return rotation angle.
		float GetRotation() const { return rotation_; }
		/// Set rotation angle.
		void SetRotation(float angle);
		/// Return scale.
		const Vector2& GetScale() const { return scale_; }
		/// Set scale. Scale also affects child sprites.
		void SetScale(const Vector2& scale);
		/// Set scale. Scale also affects child sprites.
		void SetScale(float x, float y);
		/// Return UI rendering batches.
		virtual void GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor);
		/// Return hotspot.
		const IntVector2& GetHotSpot() const { return hotSpot_; }
		/// Set hotspot for positioning and rotation.
		void SetHotSpot(const IntVector2& hotSpot);
		/// Set hotspot for positioning and rotation.
		void SetHotSpot(int x, int y);
		bool GetVisible() { return visible_; }
		void SetParent(UIElement * parent) { parent_ = parent; };
		bool InRect(const IntRect& rect, const IntVector2& pos);
		const String& GetXml();
		virtual void SetXml(const String& str);
		XMLElement GetRoot(const String& name = String::EMPTY);
	protected:
		virtual void InitXml() = 0;
		virtual void Layout();
		Vector2 scale_{ Vector2::ONE };
		float rotation_{0.0f};
		bool layout_{ false };
		String grid_{ String::EMPTY };
		bool vary_{ false };
		String xml_str_{String::EMPTY};
		SharedPtr<XMLFile> xml_{ nullptr };
	private:
		/// Hotspot for positioning and rotation.
		IntVector2 hotSpot_{ IntVector2::ZERO };
		/// Transform matrix.
		mutable Matrix3x4 transform_;
		int left_{ 0x7FFFFFFF };
		int top_{ 0x7FFFFFFF };
		int right_{ 0x7FFFFFFF };
		int bottom_{ 0x7FFFFFFF };
		int centerX_{ 0x7FFFFFFF };
		int centerY_{ 0x7FFFFFFF };
		void RefreshPosition();
		void RefreshSize();
	};
}
