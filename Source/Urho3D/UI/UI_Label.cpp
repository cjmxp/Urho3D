#include "../Core/StringUtils.h"
#include "../Resource/ResourceCache.h"
#include "../Graphics/Texture.h"
#include "../Graphics/Texture2D.h"
#include "../UI/UI_Label.h"
#include "../UI/Font.h"
#include "../UI/FontFace.h"
#include "../UI/UIEvents.h"

namespace Urho3D
{
    class Str {
    public:
        const char* s_{ 0 };
        const char* e_{ 0 };
        Str() {}
        Str(const char* s, const char* e) : s_(s), e_(e) {}
        void Set(const char* s, const char* e) {
            s_ = s;
            e_ = e;
        }

        bool Equal(const char* s) {
            return !strncmp(s_, s, e_ - s_);
        }

#define TOLOWER(x) ((x) | 0x20)
        unsigned GetC(const char* s) {
            return isdigit(*s) ? (*s) - '0' : TOLOWER(*s) - 'a' + 10;
        }
  
        float Get1(const char* s) {
            return (float)GetC(s) / 15.0f;
        }
        float Get2(const char* s) {
            return (float)(GetC(s) * 16 + GetC(s + 1)) / 255.0f;
        }

        Color GetColor(const char* s, int n) {
            Color c;

            if (n == 3 || n == 4) {
                c.r_ = Get1(s + 0);
                c.g_ = Get1(s + 1);
                c.b_ = Get1(s + 2);
                c.a_ = (n == 4) ? Get1(s + 3) : 1.0f;
            }
            else if (n == 6 || n == 8) {
                c.r_ = Get2(s + 0);
                c.g_ = Get2(s + 2);
                c.b_ = Get2(s + 4);
                c.a_ = (n == 8) ? Get2(s + 6) : 1.0f;
            }
            else {
                c.FromUInt(ToUInt(s, 16));
            }

            return c;
        }

        Color GetColor() {
            if (s_[0] == '0' && (s_[1] == 'x' || s_[1] == 'X')) {
                return GetColor(s_ + 2, e_ - s_ - 2);
            }
            return Color();
        }

        String GetString() {
            return String(s_, e_ - s_);
        }

        IntVector2 GetIntVector2() {
            return ToIntVector2(GetString());
        }

        int GetInt() {
            return ToInt(s_);
        }
        int GetFloat() {
            return ToFloat(s_);
        }
    };

    struct ParseCtx {
        const char* text;
        const char* start;
        bool htmlEnable_{ 1 };

        Block* currentBlock;
        HtmlBlockP* p{};
        HtmlBlockTextStart* style;
        UI_Label* r;

        List<HtmlBlockTextStart*> styleStack;

        template<typename T> T* AppendBlock() {
            return (T*)AppendBlock(new T());
        }

        Block* AppendBlock(Block* t) {
            currentBlock = t;
            t->SetTextRange(start, text);
            t->SetOwner(r);
            r->AppendBlock(t);
            t->Init();

            if (t->IsBreaker(nullptr)) {
                if (t->GetString() == "p") {
                    HtmlBlockPop* b = (HtmlBlockPop*)t;
                    b->head_ = p;
                }
                else if (t->GetString() == "text") {
                    HtmlBlockPop* b = (HtmlBlockPop*)t;
                    b->head_ = style;
                }
            }
            if (t->IsP())
                p = (HtmlBlockP*)t;

            if (t->IsStyle()) {
                style = (HtmlBlockTextStart*)t;
                styleStack.Push(style);
            }
            if (t->IsBreaker(style)) {
                styleStack.Pop();
                if (styleStack.Size() > 0)
                    style = styleStack.Back();
            }

            return t;
        }
    };


    void Block::MarkDirty() {
        if (owner_) {
            owner_->MarkDirty();
        }
    }

    void Block::SetProp(Str * k, Str * v) {
        if (k->Equal("width")) {
            fixedSize_.x_ = v->GetInt();
        }
        else if (k->Equal("height")) {
            fixedSize_.y_ = v->GetInt();
        }
    }
    void HtmlBlockLink::SetProp(Str * k, Str * v) {
        if (k->Equal("href")) {
            href_ = v->GetString();
        }
        HtmlBlockTextStart::SetProp(k, v);
    }
    void HtmlBlockLink::Init() {
        color_ = Color(9.0f/255.0f, 10.0f / 255.0f, 237/255.0f);
    }
    void HtmlBlockImg::Init()
    {
        element_ = new Sprite(owner_->GetContext());
        owner_->AddChild(element_);
    }
    void HtmlBlockImg::SetProp(Str * k, Str * v)
    {
        Block::SetProp(k, v);
        if (k->Equal("src")) {
            imagePath_ = v->GetString();
            auto* cache = GetElement()->GetSubsystem<ResourceCache>();
            auto* tex = cache->GetResource<Texture2D>(imagePath_);
            GetElement()->SetTexture(tex);

            if (fixedSize_.x_ == 0 && fixedSize_.y_ == 0)
                SetFixedSize(IntVector2(tex->GetWidth(), tex->GetHeight()));
        }
    }
    void HtmlBlockImg::ApplyAttributes() { 
        element_->ApplyAttributes();
        element_->SetSize(fixedSize_);
        element_->SetHotSpot(fixedSize_ / 2);
        element_->SetPosition(fixedSize_.x_/2, fixedSize_.y_/2);
    }
    void HtmlBlockP::SetProp(Str * k, Str * v) {
        if (k->Equal("align")) {
            if (v->Equal("right"))
                align_ = HA_RIGHT;
            else if (v->Equal("center"))
                align_ = HA_CENTER;
            else
                align_ = HA_LEFT;
        }
        else {
            Block::SetProp(k, v);
        }
    }
    void HtmlBlockTextStart::SetProp(Str * k, Str * v)
    {
        Block::SetProp(k, v);
        if (k->Equal("color")) {
            color_ = v->GetColor();
        }
        else if (k->Equal("font")) {
            fontName_ = v->GetString();
        }
        else if (k->Equal("size")) {
            fontSize_ = v->GetInt();
        }
        else if (k->Equal("shadowColor")) {
            effectColor_ = v->GetColor();
            textEffect_ = TE_SHADOW;
        }
        else if (k->Equal("shadowOffset")) {
            shadowOffset_ = v->GetIntVector2();
        }
        else if (k->Equal("strokeThickness")) {
            strokeThickness_ = v->GetInt();
        }
        else if (k->Equal("depthBias")) {
            effectDepthBias_ = v->GetFloat();
        }
        else if (k->Equal("strokeColor")) {
            effectColor_ = v->GetColor();
            textEffect_ = TE_STROKE;
        }
    }
    void HtmlBlockTextStart::ApplyAttributes() {
        auto* cache = owner_->GetSubsystem<ResourceCache>();
        if(color_==Color::WHITE){
            color_ = ToColor(owner_->color_);
        }
        if(fontSize_<=0){
            fontSize_ = owner_->fontSize_;
        }
        if(fontName_==String::EMPTY){
            fontName_ = owner_->font_;
        }
        font_ = cache->GetResource<Font>(fontName_);
        fontface_ = font_ ? font_->GetFace(fontSize_) : nullptr;
    }

    void HtmlBlockText::Draw(float dx, float dy, Color & color, PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor)
    {
        const Vector<SharedPtr<Texture2D> >& textures = style_->fontface_->GetTextures();
        for (unsigned n = 0; n < unicodeText_.Size(); ++n)
        {
            GlyphLocation& glyphLocation = charLocations_[n];

            if (glyphLocation.glyph_) {
                // One batch per texture/page
                const FontGlyph& glyph = *glyphLocation.glyph_;
                UIBatch pageBatch(this->owner_, BLEND_ALPHA, currentScissor, textures[glyph.page_], &vertexData);
                pageBatch.SetColor(color);
				Vector2 scale = owner_->GetScale();
                pageBatch.AddQuad((dx + glyphLocation.x_ + glyph.offsetX_)+ glyph.width_*((1.0 - scale.x_)/2), (dy + glyphLocation.y_ + glyph.offsetY_) + glyph.texHeight_*((1.0 - scale.y_)/2), glyph.width_*scale.x_,
                    glyph.height_*scale.y_, glyph.x_, glyph.y_, glyph.texWidth_, glyph.texHeight_);

                UIBatch::AddOrMerge(pageBatch, batches);
            }
        }
    }

    void HtmlBlockText::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect & currentScissor) {
        switch (style_->textEffect_)
        {
        case TE_SHADOW:
            Draw(position_.x_ + style_->shadowOffset_.x_, position_.y_ + style_->shadowOffset_.y_, style_->effectColor_, batches, vertexData, currentScissor);
            break;
        case TE_STROKE:
            int thickness = Min(style_->strokeThickness_, style_->fontSize_);
            int x, y;
            for (x = -thickness; x <= thickness; ++x)
            {
                for (y = -thickness; y <= thickness; ++y)
                {
                    // Don't draw glyphs that aren't on the edges
                    if (x > -thickness && x < thickness &&
                        y > -thickness && y < thickness)
                        continue;

                    Draw(position_.x_ + x, position_.y_ + y, style_->effectColor_, batches, vertexData, currentScissor);
                }
            }
            break;
        }
        Draw(position_.x_, position_.y_, style_->color_, batches, vertexData, currentScissor);
    }

    void HtmlBlockText::ApplyAttributes() {
        text_ = String(s_, e_ - s_);
        UpdateText();
    }

    void HtmlBlockText::UpdateText()
    {
        float rowHeight_ = style_->fontface_->GetRowHeight();

        unicodeText_.Clear();
        for (unsigned i = 0; i < text_.Length();)
            unicodeText_.Push(text_.NextUTF8Char(i));

        charLocations_.Clear();
        unsigned numChars = unicodeText_.Size();
        charLocations_.Resize(numChars + 1);

        IntVector2 offset = style_->font_->GetTotalGlyphOffset(style_->fontSize_);
        float x = (float)Round(0 + offset.x_);
        float y = (float)Round(offset.y_);

        for (unsigned i = 0; i < unicodeText_.Size(); ++i)
        {

            unsigned c = unicodeText_[i];

            const FontGlyph* glyph = style_->fontface_->GetGlyph(c);
            //loc.size_ = Vector2(glyph ? glyph->advanceX_ : 0, rowHeight_);
            GlyphLocation loc(x, y, glyph);
            if (glyph)
            {
                x += glyph->advanceX_;
                if (i < unicodeText_.Size() - 1)
                    x += style_->fontface_->GetKerning(c, unicodeText_[i + 1]);
            }

            charLocations_[i] = loc;
        }

        size_.x_ = x;
        size_.y_ = rowHeight_;
    }

    static bool IsSpace(char c) {
        switch (c)
        {
        case ' ':
        case '\n': 
        case '\r':
        case '\t':
            return true;
        }
        return false;
    }

    static bool IsWordBreak(char c) {
        switch (c)
        {
        case 0:
        case '\"': case '\'': case '/': case '\\':
        case '[': case ']': case '{': case '}':
        case '(': case ')': case '>': case '<':
        case '-': case '+': case '*':
        case ',': case '.': case ';': case ':':
        case '&': case '|': case '#': case '!':
        case '=': case '^': case '~': case '?':
        case '@': case '$':
            return true;
        }

        return IsSpace(c);
    }
  
    static bool NextBlock(ParseCtx* ctx) {
        ctx->start = ctx->text;

            switch (ctx->text[0]) {
            case 0:
            {
                return true;
            }
            case '\r':
            {
                unsigned n = (ctx->text[1] == '\n') ? 2 : 1;
                ctx->text += n;
                ctx->AppendBlock<HtmlBlockBr>();
                return false;
            }
            case '\n':
            {
                ctx->text += 1;
                ctx->AppendBlock<HtmlBlockBr>();
                return false;
            }
            case '<':
            {
                if (ctx->htmlEnable_) {
                    if (*(ctx->text + 1) == '/') {
                        ctx->text += 2;
                        ctx->start = ctx->text;
                        while (!IsWordBreak(*ctx->text))
                            ctx->text++;
                        if (*ctx->text == '>') {
                            ctx->AppendBlock<HtmlBlockPop>();
                            ctx->text += 1;
                            return (*ctx->text == 0);
                        }
                        else if (ctx->text != ctx->start) {
                            ctx->AppendBlock<HtmlBlockText>();
                        }
                    }
                    else {

                        ctx->start = ctx->text;
                        ctx->text++;// skip <

                        if (!strncmp(ctx->text, "br", 2)) {
                            ctx->AppendBlock<HtmlBlockBr>();
                        }
                        else if (!strncmp(ctx->text, "p", 1)) {
                            ctx->AppendBlock<HtmlBlockP>();
                        }
                        else if (!strncmp(ctx->text, "a", 1)) {
                            ctx->AppendBlock<HtmlBlockLink>();
                        }
                        else if (!strncmp(ctx->text, "img", 3)) {
                            ctx->AppendBlock<HtmlBlockImg>();
                        }
                        else if (!strncmp(ctx->text, "text", 4)) {
                            ctx->AppendBlock<HtmlBlockTextStart>();
                        }
                        else {
                            ctx->text = ctx->start;
                            break;
                        }

                        while (!IsWordBreak(*ctx->text))
                            ctx->text++;

                        while (true) {
                            // skip space
                            while (IsSpace(*ctx->text))
                                ctx->text++;

                            if (IsWordBreak(*ctx->text)) {
                                if (*ctx->text == '/') {
                                    ctx->text++;
                                }

                                if (*ctx->text == '>') {
                                    ctx->text++;
                                }

                                break;
                            }

                            ctx->start = ctx->text;

                            while (!IsWordBreak(*ctx->text))
                                ctx->text++;

                            if (ctx->text[0] != '=') {
                                ctx->text = ctx->start;
                                break;
                            }

                            Str k(ctx->start, ctx->text);
                            Str v;

                            ctx->text++;

                            if (ctx->text[0] == '\"') {
                                ctx->start = ctx->text + 1;

                                while (true) {
                                    ctx->text++;

                                    if (*ctx->text == 0)
                                        break;

                                    if (*ctx->text == '\"')
                                        break;
                                }

                                if (*ctx->text == '\"') {
                                    v.Set(ctx->start, ctx->text);
                                    ctx->text++;
                                }
                            }
                            else {
                                ctx->start = ctx->text;
                                while (!IsWordBreak(*ctx->text))
                                    ctx->text++;

                                v.Set(ctx->start, ctx->text);
                            }

                            ctx->currentBlock->SetProp(&k, &v);
                        }
                        ctx->currentBlock->ApplyAttributes();
                        return (*ctx->text == 0);
                    }
                }
            }
            }

        ctx->start = ctx->text;

        unsigned char c = *ctx->text;
        if (c >= 0xc0) {
            String::DecodeUTF8(ctx->text);
        }
        else {
            while (true) {
                c = *ctx->text;
                if (IsWordBreak(c) || c >= 0xc0)
                    break;

                ctx->text++;
            }
        }

        if (ctx->text == ctx->start) {
            if (IsWordBreak(*ctx->text)) {
                ctx->text++;
            }
        }
            
        HtmlBlockText* textblock = ctx->AppendBlock<HtmlBlockText>();
        textblock->style_ = ctx->style;
        textblock->ApplyAttributes();

        return (*ctx->text == 0);
    }

    void UI_Label::AppendText(const String & str)
    {
        ParseCtx ctx;
        ctx.text = str.CString();
        ctx.r = this;
        ctx.htmlEnable_ = this->htmlEnable_;

        HtmlBlockTextStart* ts = ctx.AppendBlock<HtmlBlockTextStart>();
        ts->ApplyAttributes();

        while (true) {
            bool eof = NextBlock(&ctx);

            if (eof) {
                break;
            }
        }

        MarkDirty();
    }

    void UI_Label::ApplyAttributes() { MarkDirty(); }
    void UI_Label::OnResize(const IntVector2 & newSize, const IntVector2 & delta) { MarkDirty(); }
    void UI_Label::OnIndentSet() { MarkDirty(); }

    void UI_Label::OnClickBegin(const IntVector2 & position, const IntVector2 & screenPosition, int button, int buttons, int qualifiers, Cursor * cursor)
    {
        if (button == MOUSEB_LEFT)
        {
            Block* clickable = nullptr;
            bool ok = false;
            for (auto& blockptr : blocks_) {
                if (blockptr->IsClickAble()) {
                    clickable = blockptr.Get();
                }
                else if (blockptr->IsBreaker(clickable)) {
                    clickable = nullptr;
                }
                else if (clickable) {
                    IntRect rect(blockptr->GetPosition(), blockptr->GetPosition() + blockptr->GetSize());
                    if (rect.IsInside(position) == INSIDE) {
                        ok = true;
                        break;
                    }
                }
            }
            if (ok) {
				if (enabled_) {
					using namespace UIHtmlLinkClick;
					VariantMap& eventData = GetEventDataMap();
					eventData[P_HREF] = ((HtmlBlockLink*)clickable)->href_;
					SendEvent(E_UIHTMLLINKCLICK, eventData);
				}
            }
        }
    }

    void UI_Label::OnClickEnd(const IntVector2 & position, const IntVector2 & screenPosition, int button, int buttons, int qualifiers, Cursor * cursor, UIElement * beginElement)
    {
    }

    void UI_Label::OnHover(const IntVector2 & position, const IntVector2 & screenPosition, int buttons, int qualifiers, Cursor * cursor)
    {
    }

	void UI_Label::SetColor(const String& value) {
		if (color_ != value && value!=String::EMPTY) {
			color_ = value;
		}
		
	}

	void UI_Label::SetFont(const String& value) {
		if (font_ != value && value != String::EMPTY) {
			font_ = value;
		}
	}
	void UI_Label::SetFontSize(int value) {
		if (fontSize_ != value ) {
			fontSize_ = value;
		}
	}
    void UI_Label::SetText(const Urho3D::String &str){
        text_ = str;
        Clear();
        AppendText(str);
		Layout();
    }
    
    void UI_Label::MarkDirty() {
		dirty_ = true;
		positionDirty_ = true;
	}

    void UI_Label::Clear() {
        blocks_.Clear();
    }

    void UI_Label::AppendBlock(Block * block) {
        blocks_.Push(SharedPtr<Block>(block));
        MarkDirty();
    }

    static void DoLayout(int& textWidth, int& textHeight, HorizontalAlignment align, int x, int y, int maxWidth, bool wordWrap, List<SharedPtr<Block> >::Iterator from, List<SharedPtr<Block> >::Iterator to) {

        maxWidth = wordWrap ? maxWidth : 2147483647;

        textWidth = 0;
        textHeight = 0;

        while (true) {

            if (from == to)
                break;

            if ((*from)->IsP()) {
                HtmlBlockP* p = (HtmlBlockP*)(*from).Get();
                from++;
                for (auto iter1 = from; iter1 != to; iter1++) {
                    if ((*iter1)->IsBreaker(p)) {
                        int tw, th;
                        DoLayout(tw, th, p->align_, 0, y, p->GetSize().x_, wordWrap, from, iter1);
                        p->SetSize(IntVector2(tw, th));
                        from = iter1;
                        y += th;
                        break;
                    }
                }
            }

            int width = 0;
            int requireHeight = 0;
            int n = 0;
            for (auto iter1 = from; iter1 != to; iter1++) {
                auto& block = *iter1;
                if (block->IsP())
                    break;

                auto& size = block->GetSize();
                if (block->IsStyle() || !block->IsDisplay()) {
                    if (block->IsBreakLine()) {
                        break;
                    }
                    else {
                        continue;
                    }
                }

                width += size.x_;
                if (wordWrap && width > maxWidth && n >= 1) {
                    break;
                }
                n++;
                if (size.y_ > requireHeight) {
                    requireHeight = size.y_;
                }
            }

            y += requireHeight;
            textHeight = y;

            if (align == HA_RIGHT)
                x = maxWidth - width;
            else if (align == HA_CENTER)
                x = maxWidth/2 - width/2;
            else
                x = 0;
            width = 0;
            n = 0;

            for (; from != to; from++) {
                auto& block = *from;
                if (block->IsP())
                    break;
                if (block->IsStyle() || !block->IsDisplay()) {
                    if (block->IsBreakLine()) {
                        from++;
                        break;
                    }
                    continue;
                }

                auto& size = block->GetSize();

                width += size.x_;
                if (wordWrap && width > maxWidth && n >= 1) {
                    break;
                }
                else {
                    block->SetPosition(IntVector2(x, y - size.y_));
                    x += size.x_;
                    n++;
                }
            }

            textWidth = Max(width, textWidth);
        }
    }
	void UI_Label::Update(float timeStep) {
		if (dirty_) Layout();
	}
    void UI_Label::Layout() {
        DoLayout(textWidth, textHeight, HA_LEFT, 0, 0, GetSize().x_, wordWrap_, blocks_.Begin(), blocks_.End());
		dirty_ = false;
    }

    void UI_Label::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor)
    {
        for (auto& block : blocks_) {
            block->GetBatches(batches, vertexData, currentScissor);
        }
    }

}
