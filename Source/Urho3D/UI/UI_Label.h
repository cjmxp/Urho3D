#pragma once


#include "../UI/Text.h"
#include "../UI/Sprite.h"
#include "../Container/List.h"
#include "../UI/UI_Clip.h"

namespace Urho3D 
{
class Str;
class UI_Label;

class Block : public RefCounted
{
public:
    virtual ~Block() {};

    void SetSize(const IntVector2& sz) {
        size_ = sz;
    }
    virtual const IntVector2& GetSize() const {
        if (fixedSize_.x_ != 0 && fixedSize_.y_ != 0) {
            return fixedSize_;
        }
        return size_;
    }
    virtual bool IsBreakLine() { return false; }
    virtual bool IsStyle() { return false; }
    virtual bool IsClickAble() { return false; }
    virtual bool IsDisplay() { return true; }
    virtual bool IsSpace() { return false; }
    virtual bool IsText() { return false; }
    virtual bool IsP() { return false; }
    virtual bool IsBreaker(Block* head) { return false; }

    virtual void Init() {}
    virtual void GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) {}
    virtual void SetFixedSize(const IntVector2& fixsize) { fixedSize_ = fixsize; }
    virtual void SetPosition(const IntVector2& pos) { position_ = pos; }
    virtual void SetProp(Str* k, Str* v);
    virtual void SetTextRange(const char* s, const char* e) {
        s_ = s; e_ = e;
    }
    virtual void ApplyAttributes() {}

    const IntVector2& GetPosition() const { return position_; }
    const IntVector2& GetFixedSize() const { return fixedSize_; }

    void SetOwner(UI_Label* o) { owner_ = o; }
    String GetString() { return String(s_, e_ - s_); }
protected:
    friend class RichText;
    void MarkDirty();

    const char* s_{ 0 };
    const char* e_{ 0 };

    UI_Label* owner_{};
    IntVector2 position_;
    IntVector2 fixedSize_;
    IntVector2 size_;
};

class HtmlBlockPop : public Block {
public:
    virtual bool IsBreaker(Block* head) { return head_ == head; }
    virtual bool IsDisplay() { return false; }
    Block* head_{};
};

class HtmlBlockBr : public Block {
public:
    virtual bool IsBreakLine() { return true; }
    virtual bool IsDisplay() { return false; }
};

class HtmlBlockTextStart : public Block {
public:
    virtual bool IsStyle() { return true; }
    virtual void SetProp(Str* k, Str* v);
    virtual void ApplyAttributes();

    Color color_;
    String fontName_;
    float fontSize_;

    TextEffect textEffect_{ TE_NONE };
    IntVector2 shadowOffset_;
    Color effectColor_;
    int strokeThickness_;
    float effectDepthBias_;

    Font* font_{};
    FontFace* fontface_{};
};

class HtmlBlockLink : public HtmlBlockTextStart {
public:
    virtual void SetProp(Str* k, Str* v);
    virtual bool IsDisplay() { return false; }
    virtual bool IsClickAble() { return true; }
    virtual void Init();

    String href_;
};

class HtmlBlockP : public Block {
public:
    virtual bool IsBreakLine() { return true; }
    virtual bool IsP() { return true; }
    virtual void SetProp(Str* k, Str* v);

    HorizontalAlignment align_{ HA_LEFT };
};

template<typename T>
class UIElementBlock : public Block
{
public:
    ~UIElementBlock() { 
        element_->Remove();
    }
    virtual void SetFixedSize(const IntVector2& fixsize) {
        Block::SetFixedSize(fixsize);
        element_->SetSize(fixsize);
    }
    virtual void SetPosition(const IntVector2& pos) {
        Block::SetPosition(pos);
        IntVector2 pos1 = fixedSize_ / 2 + pos;
        element_->SetPosition((float)pos1.x_, (float)pos1.y_);
    }
    virtual void GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) {
        element_->GetBatches(batches, vertexData, currentScissor);
    }
    virtual void ApplyAttributes() {
        element_->ApplyAttributes();
    }

    T* GetElement() { return element_; }
protected:
    SharedPtr<T> element_;
};

class HtmlBlockImg : public UIElementBlock<Sprite> {
public:
    virtual void Init();
    virtual void SetProp(Str* k, Str* v);
    virtual void ApplyAttributes();
protected:
    String imagePath_;
};

class HtmlBlockText : public Block {
public:
    virtual bool IsText() { return true; }
    virtual void ApplyAttributes();
    virtual void GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor);
    virtual void UpdateText();

    void Draw(float dx, float dy, Color& color, PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor);

    HtmlBlockTextStart* style_;
    String text_;
    PODVector<unsigned> unicodeText_;
    PODVector<GlyphLocation> charLocations_;
};

class URHO3D_API UI_Label : public UI_Clip
{
    URHO3D_OBJECT(UI_Label, UI_Clip);
public:
    UI_Label(Context* c) : UI_Clip(c) {
        SetEnabled(true);
    }

    /// Apply attribute changes that can not be applied immediately.
    void ApplyAttributes() override;
    /// Return UI rendering batches.
    void GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override;
    /// React to resize.
    void OnResize(const IntVector2& newSize, const IntVector2& delta) override;
    /// React to indent change.
    void OnIndentSet() override;
    void OnClickBegin
    (const IntVector2& position, const IntVector2& screenPosition, int button, int buttons, int qualifiers, Cursor* cursor) override;
    /// React to mouse click end.
    void OnClickEnd
    (const IntVector2& position, const IntVector2& screenPosition, int button, int buttons, int qualifiers, Cursor* cursor,
        UIElement* beginElement) override;
    void OnHover(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers, Cursor* cursor) override;
	virtual void Update(float timeStep) override;
    void AppendText(const String& str);
    void Clear();
    void SetText(const String& str);
    const String& GetText() const {return text_;};
    void AppendBlock(Block* block);
	const String& GetColor()const { return color_; };
	void SetColor(const String& value);
	const String& GetFont()const { return font_; };
	void SetFont(const String& value);
	int GetFontSize() { return fontSize_; };
	void SetFontSize(int v);
    void MarkDirty();
    void Layout();
    bool GetWordWrap(){return wordWrap_;}
    void SetWordWrap(bool b) {
        wordWrap_ = b;
        MarkDirty();
    }
    bool GetIsHtml(){return htmlEnable_;}
    void SetIsHtml(bool b) {
        htmlEnable_ = b;
    }
    String color_{"1 0 0"};
    String font_{ "Fonts/kaiti.ttf" };
    int fontSize_{ 12 };
    int textWidth;
    int textHeight;
	virtual void InitAttribute() override;
protected:
	String text_{ String::EMPTY };
    bool htmlEnable_{ 1 };
    bool wordWrap_{ 1 };
    bool dirty_{0};
    List<SharedPtr<Block> > blocks_;
};


}
