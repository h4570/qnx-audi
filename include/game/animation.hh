/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#ifndef _QNX_AUDI_OBJECT_ANIMATION_
#define _QNX_AUDI_OBJECT_ANIMATION_

#include "models/texture.hh"
#include "utils/debug.hh"
#include "game/render_package.hh"
#include <GLES/egl.h>

enum AnimationState
{
    Once,
    Repeat
};

class Animation
{
public:
    Animation(const char *t_name, _Uint8t t_framesCount);
    ~Animation();

    void render(const RenderPackage &package, _Uint8t &animCounter);
    inline void setAnimationState(const AnimationState state) { m_state = state; }
    inline AnimationState getAnimationState() const { return m_state; }
    inline const _Uint8t &getFramesCount() const { return m_framesCount; }
    inline bool isFinished(_Uint8t &animCounter) const { return animCounter >= m_framesCount - 1; }

private:
    AnimationState m_state;
    _Uint8t m_framesCount;
    std::string m_path, m_name;
    Texture **m_textures;
    GLuint *m_textureIds;

    static const GLfloat TEXTURE_COORDINATES[];
    static const GLubyte INDICES[];
};

#endif