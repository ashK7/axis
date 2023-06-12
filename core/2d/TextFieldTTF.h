/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

https://axmolengine.github.io/

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#ifndef __AX_TEXT_FIELD_H__
#define __AX_TEXT_FIELD_H__

#include "2d/Label.h"
#include "base/IMEDelegate.h"

/**
 * @addtogroup ui
 * @{
 */
NS_AX_BEGIN

class TextFieldTTF;

/**
 * A input protocol for TextField.
 */
class AX_DLL TextFieldDelegate
{
public:
    /**
     * Destructor for TextFieldDelegate.
     * @js NA
     */
    virtual ~TextFieldDelegate() {}

    /**
     *@brief    If the sender doesn't want to attach to the IME, return true.
     */
    virtual bool onTextFieldAttachWithIME(TextFieldTTF* sender);
    /**
     *@brief    If the sender doesn't want to detach from the IME, return true.
     */
    virtual bool onTextFieldDetachWithIME(TextFieldTTF* sender);

    /**
     *@brief    If the sender doesn't want to insert the text, return true.
     */
    virtual bool onTextFieldInsertText(TextFieldTTF* sender, const char* text, size_t nLen);

    /**
     *@brief    If the sender doesn't want to delete the delText, return true.
     */
    virtual bool onTextFieldDeleteBackward(TextFieldTTF* sender, const char* delText, size_t nLen);

    /**
     *@brief    If the sender doesn't want to draw, return true.
     * @js NA
     */
    virtual bool onVisit(TextFieldTTF* sender, Renderer* renderer, const Mat4& transform, uint32_t flags);
};

/**
 *@brief    A simple text input field with TTF font.
 */
class AX_DLL TextFieldTTF : public Label, public IMEDelegate
{
public:
    /**
     * Default constructor.
     * @js ctor
     */
    TextFieldTTF();

    /**
     * Default destructor.
     * @js NA
     * @lua NA
     */
    virtual ~TextFieldTTF();

    /** Creates a TextFieldTTF from a fontname, alignment, dimension and font size.
     * @js NA
     */
    static TextFieldTTF* textFieldWithPlaceHolder(std::string_view placeholder,
                                                  const Vec2& dimensions,
                                                  TextHAlignment alignment,
                                                  std::string_view fontName,
                                                  float fontSize);

    /** Creates a TextFieldTTF from a fontname and font size.
     * @js NA
     */
    static TextFieldTTF* textFieldWithPlaceHolder(std::string_view placeholder,
                                                  std::string_view fontName,
                                                  float fontSize);

    /** Initializes the TextFieldTTF with a font name, alignment, dimension and font size. */
    bool initWithPlaceHolder(std::string_view placeholder,
                             const Vec2& dimensions,
                             TextHAlignment alignment,
                             std::string_view fontName,
                             float fontSize);

    /** Initializes the TextFieldTTF with a font name and font size. */
    bool initWithPlaceHolder(std::string_view placeholder, std::string_view fontName, float fontSize);

    /**
     *@brief    Open keyboard and receive input text.
     */
    virtual bool attachWithIME() override;

    /**
     *@brief    End text input and close keyboard.
     */
    virtual bool detachWithIME() override;

    //////////////////////////////////////////////////////////////////////////
    // properties
    //////////////////////////////////////////////////////////////////////////
    /**
     * @lua NA
     */
    TextFieldDelegate* getDelegate() const { return _delegate; }
    /**
     * @lua NA
     */
    void setDelegate(TextFieldDelegate* delegate) { _delegate = delegate; }

    /**
     * Query the currently inputed character count.
     *@return The total input character count.
     */
    std::size_t getCharCount() const { return _charCount; }

    /**
     * Query the color of place holder.
     *@return The place holder color.
     */
    virtual const Color4B& getColorSpaceHolder();

    /**
     *@brief Change input placeholder color.
     *@param color A color value in `Color3B`.
     */
    virtual void setColorSpaceHolder(const Color3B& color);

    /**
     * Change the placeholder color.
     *@param color The placeholder color in Color4B.
     */
    virtual void setColorSpaceHolder(const Color4B& color);

    /**
     * Change the color of input text.
     *@param textColor The text color in Color4B.
     */
    virtual void setTextColor(const Color4B& textColor) override;

    /**
     * Change input text of TextField.
     *@param text The input text of TextField.
     */
    virtual void setString(std::string_view text) override;

    /**
     * Append to input text of TextField.
     *@param text The append text of TextField.
     */
    virtual void appendString(std::string_view text);

    /**
     * Query the input text of TextField.
     *@return Get the input text of TextField.
     */
    virtual std::string_view getString() const override;

    /**
     * Change placeholder text.
     * place holder text displayed when there is no text in the text field.
     *@param text  The placeholder string.
     */
    virtual void setPlaceHolder(std::string_view text);

    /**
     * Query the placeholder string.
     *@return The placeholder string.
     */
    virtual std::string_view getPlaceHolder() const;

    /**
     * Set enable secure text entry representation.
     * If you want to display password in TextField, this option is very helpful.
     *@param value Whether or not to display text with secure text entry.
     * @js NA
     */
    virtual void setSecureTextEntry(bool value);
    virtual void setPasswordTextStyle(std::string_view text);
    std::string_view getPasswordTextStyle() const;

    /**
     * Query whether the currently display mode is secure text entry or not.
     *@return Whether current text is displayed as secure text entry.
     * @js NA
     */
    virtual bool isSecureTextEntry() const;

    virtual void visit(Renderer* renderer, const Mat4& parentTransform, uint32_t parentFlags) override;

    virtual void update(float delta) override;

    /**
     * Set enable cursor use.
     * @js NA
     */
    void setCursorEnabled(bool enabled);

    /**
     * Set char showing cursor.
     * @js NA
     */
    void setCursorChar(char cursor);

    /**
     * Set cursor position, if enabled
     * @js NA
     */
    void setCursorPosition(std::size_t cursorPosition);

    /**
     * Set cursor position to hit letter, if enabled
     * @js NA
     */
    void setCursorFromPoint(const Vec2& point, const Camera* camera);

protected:
    //////////////////////////////////////////////////////////////////////////
    // IMEDelegate interface
    //////////////////////////////////////////////////////////////////////////

    virtual bool canAttachWithIME() override;
    virtual bool canDetachWithIME() override;
    virtual void didAttachWithIME() override;
    virtual void didDetachWithIME() override;
    virtual void insertText(const char* text, size_t len) override;
    virtual void deleteBackward() override;
    virtual std::string_view getContentText() override;
    virtual void controlKey(EventKeyboard::KeyCode keyCode) override;

    TextFieldDelegate* _delegate;
    std::size_t _charCount;

    std::string _inputText;

    std::string _placeHolder;
    Color4B _colorSpaceHolder;
    Color4B _colorText;

    bool _secureTextEntry;
    std::string _passwordStyleText;

    // Need use cursor
    bool _cursorEnabled;
    // Current position cursor
    std::size_t _cursorPosition;
    // Char showing cursor
    char _cursorChar;
    // >0 - show, <0 - hide
    float _cursorShowingTime;

    bool _isAttachWithIME;

    void makeStringSupportCursor(std::string& displayText);
    void updateCursorDisplayText();
    void setAttachWithIME(bool isAttachWithIME);
    void setTextColorInternally(const Color4B& color);

private:
    class LengthStack;
    LengthStack* _lens;
};

NS_AX_END
// end of ui group
/// @}

#endif  // __AX_TEXT_FIELD_H__