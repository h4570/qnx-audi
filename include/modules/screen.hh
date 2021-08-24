/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#ifndef _QNX_AUDI_SCREEN_
#define _QNX_AUDI_SCREEN_

#include <gf/gf.h>
#include <gf/gf3d.h>
#include <GLES/egl.h>

/** QNX screen */
class Screen
{

public:
    Screen();
    ~Screen();

    EGLDisplay Display;
    EGLSurface Surface;

    // ----
    // Getters
    // ----

    const GLuint &getWidth() const { return m_width; };
    const GLuint &getHeight() const { return m_height; };
    const bool &isInitialized() const { return m_isInitialized; };

    // ----
    //  Setters
    // ----

    // ----
    //  Other
    // ----

    /** Initialize QNX's device, display, layer, 3D rendering target, etc. */
    void init();

    /** Unitialize QNX rendering stuff */
    void uninit();

private:
    gf_dev_t m_gfDevice;
    gf_dev_info_t m_gfDeviceInfo;
    gf_display_t m_gfDisplay;
    gf_display_info_t m_gfDisplayInfo;
    gf_layer_t m_gfLayer;
    gf_layer_info_t m_gfLayerInfo;
    gf_3d_target_t m_gf3DTarget;

    EGLContext m_EGLContext;
    EGLConfig m_EGLConfig;

    bool m_isInitialized;
    int m_layerIndex;
    GLuint m_width, m_height;
    EGLint m_EGLConfigNumber;
    EGLint *m_attributes;

    void attachDevice();
    void attachDisplay();
    void setEGLDisplayConnection();
    void attachLayer();
    void initEGLDisplayConnection();
    void searchForLayerAndEGLConfig();
    void create3DTarget();
    void enableLayer();
    void createEGLContext();
    void createEGLSurface();
    void connectEGLContextWithSurface();

    void detachDevice();
    void detachDisplay();
    void detachLayer();
    void free3DTarget();
    void destroyEGLContext();
    void destroyEGLSurface();

    bool __searchForLayer(const int &t_formatIndex);
    bool __searchForEGLConfig();
};

#endif