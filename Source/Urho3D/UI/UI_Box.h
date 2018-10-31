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
		/// Perform UI element update.
		virtual void Update(float timeStep);
		int GetTop();
		void SetTop(int v);
		int GetLeft();
		void SetLeft(int v);
		int GetRight();
		void SetRight(int v);
		int GetBottom();
		void SetBottom(int v);
		int GetCenterX();
		void SetCenterX(int v);
		int GetCenterY();
		void SetCenterY(int v);


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
		virtual void InitAttribute();
		virtual void InitChilds();
	protected:
		virtual void Layout();
		Vector2 scale_{ Vector2::ONE };
		float rotation_{0.0f};
		bool layout_{ false };
		String grid_{ String::EMPTY };
		bool vary_{ false };
		String xml_str_{String::EMPTY};
		SharedPtr<XMLFile> xml_{ nullptr };
	private:
		HashMap<String, WeakPtr<UI_Box>> vars_;
		/// Hotspot for positioning and rotation.
		IntVector2 hotSpot_{ IntVector2::ZERO };
		/// Transform matrix.
		mutable Matrix3x4 transform_;
		int left_{ -1 };
		int top_{ -1 };
		int right_{ -1 };
		int bottom_{ -1 };
		int centerX_{ -1 };
		int centerY_{ -1 };
		void RefreshPosition();
		void RefreshSize();
	};
}
