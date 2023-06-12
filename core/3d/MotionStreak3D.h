/****************************************************************************
 Copyright (c) 2015-2016 Chukong Technologies Inc.
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
#ifndef __AX_MOTION_STREAK3D_H__
#define __AX_MOTION_STREAK3D_H__

#include "base/Protocols.h"
#include "2d/Node.h"
#include "renderer/CustomCommand.h"
#include "renderer/CallbackCommand.h"

#include <vector>

NS_AX_BEGIN

class Texture2D;

/**
 * @addtogroup _3d
 * @{
 */

/** @class MotionStreak3D.
 * @brief Creates a trailing path. It is created from a line segment sweeping along the path.
 */
class AX_DLL MotionStreak3D : public Node, public TextureProtocol
{
public:
    /** Creates and initializes a motion streak with fade in seconds, minimum segments, stroke's width, color, texture
     * filename.
     *
     * @param fade The fade time, in seconds.
     * @param minSeg The minimum segments.
     * @param stroke The width of stroke.
     * @param color The color of stroke.
     * @param path The texture file name of stoke.
     * @return An autoreleased MotionStreak3D object.
     */
    static MotionStreak3D* create(float fade, float minSeg, float stroke, const Color3B& color, std::string_view path);
    /** Creates and initializes a motion streak with fade in seconds, minimum segments, stroke's width, color, texture.
     *
     * @param fade The fade time, in seconds.
     * @param minSeg The minimum segments.
     * @param stroke The width of stroke.
     * @param color The color of stroke.
     * @param texture The texture name of stoke.
     * @return An autoreleased MotionStreak3D object.
     */
    static MotionStreak3D* create(float fade, float minSeg, float stroke, const Color3B& color, Texture2D* texture);

    /** Color used for the tint.
     *
     * @param colors The color used for the tint.
     */
    void tintWithColor(const Color3B& colors);

    /** Remove all living segments of the ribbon.
     */
    void reset();

    /** Get stroke.
     *
     * @return float stroke.
     */
    float getStroke() const { return _stroke; }
    /** Set stroke.
     *
     * @param stroke The width of stroke.
     */
    void setStroke(float stroke) { _stroke = stroke; }

    /** Is the starting position initialized or not.
     *
     * @return True if the starting position is initialized.
     */
    bool isStartingPositionInitialized() const { return _startingPositionInitialized; }
    /** Sets the starting position initialized or not.
     *
     * @param bStartingPositionInitialized True if initialized the starting position.
     */
    void setStartingPositionInitialized(bool bStartingPositionInitialized)
    {
        _startingPositionInitialized = bStartingPositionInitialized;
    }

    // Overrides
    virtual void setPosition(const Vec2& position) override;
    virtual void setPosition(float x, float y) override;
    virtual void setPosition3D(const Vec3& position) override;
    virtual void setRotation3D(const Vec3& rotation) override;
    virtual void setRotationQuat(const Quaternion& quat) override;

    virtual const Vec2& getPosition() const override;
    virtual void getPosition(float* x, float* y) const override;
    virtual void setPositionX(float x) override;
    virtual void setPositionY(float y) override;
    virtual float getPositionX() const override;
    virtual float getPositionY() const override;
    virtual Vec3 getPosition3D() const override;
    /**
     * @js NA
     * @lua NA
     */
    virtual void draw(Renderer* renderer, const Mat4& transform, uint32_t flags) override;
    /**
     * @lua NA
     */
    virtual void update(float delta) override;
    virtual Texture2D* getTexture() const override;
    virtual void setTexture(Texture2D* texture) override;
    /**
     * @js NA
     * @lua NA
     */
    virtual void setBlendFunc(const BlendFunc& blendFunc) override;
    /**
     * @js NA
     * @lua NA
     */
    virtual const BlendFunc& getBlendFunc() const override;
    virtual uint8_t getOpacity() const override;
    virtual void setOpacity(uint8_t opacity) override;
    virtual void setOpacityModifyRGB(bool value) override;
    virtual bool isOpacityModifyRGB() const override;

    /**
     * Set the direction of sweeping line segment.
     * @param sweepAxis Direction of sweeping line segment
     */
    void setSweepAxis(const Vec3& sweepAxis) { _sweepAxis = sweepAxis.getNormalized(); }

    /**
     * Get the direction of sweeping line segment
     */
    const Vec3& getSweepAxis() const { return _sweepAxis; }

    MotionStreak3D();
    virtual ~MotionStreak3D();

    /** initializes a motion streak with fade in seconds, minimum segments, stroke's width, color and texture filename
     */
    bool initWithFade(float fade, float minSeg, float stroke, const Color3B& color, std::string_view path);

    /** initializes a motion streak with fade in seconds, minimum segments, stroke's width, color and texture  */
    bool initWithFade(float fade, float minSeg, float stroke, const Color3B& color, Texture2D* texture);

protected:
    // renderer callback

    void initCustomCommand();

    struct VertexData
    {
        Vec3 pos;
        Color4B color;
        Tex2F texPos;
    };

    bool _startingPositionInitialized;

    /** texture used for the motion streak */
    Texture2D* _texture;
    BlendFunc _blendFunc;
    Vec3 _positionR;
    mutable Vec2 _positionR2D;
    Vec3 _sweepAxis;

    float _stroke;
    float _fadeDelta;
    float _minSeg;

    unsigned int _maxPoints;
    unsigned int _nuPoints;
    unsigned int _previousNuPoints;

    /** Pointers */
    std::vector<Vec3> _pointVertexes;
    std::vector<float> _pointState;

    std::vector<VertexData> _vertexData;

    CustomCommand _customCommand;

private:
    AX_DISALLOW_COPY_AND_ASSIGN(MotionStreak3D);

    //CallbackCommand _beforeCommand;
    //CallbackCommand _afterCommand;
    backend::UniformLocation _locMVP;
    backend::UniformLocation _locTexture;

    void onBeforeDraw();
    void onAfterDraw();

    backend::CullMode _rendererCullface;
    bool _rendererDepthTest;
};

// end of _3d group
/// @}

NS_AX_END

#endif  //__AX_MOTION_STREAK3D_H__