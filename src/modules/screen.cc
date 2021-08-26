/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#include "modules/screen.hh"
#include "utils/debug.hh"

// ----
// Constructors/Destructors
// ----

Screen::Screen()
{
    m_layerIndex = 0;
    m_width = 0;
    m_height = 0;
    m_EGLConfigNumber = 0;
    m_isInitialized = false;

    m_attributes = new EGLint[11]();
    m_attributes[0] = EGL_NATIVE_VISUAL_ID;
    m_attributes[1] = 0;
    // m_attributes[?] = EGL_NATIVE_RENDERABLE;
    // m_attributes[?] = EGL_TRUE;
    m_attributes[2] = EGL_RED_SIZE;
    m_attributes[3] = 5;
    m_attributes[4] = EGL_GREEN_SIZE;
    m_attributes[5] = 5;
    m_attributes[6] = EGL_BLUE_SIZE;
    m_attributes[7] = 5;
    m_attributes[8] = EGL_DEPTH_SIZE;
    m_attributes[9] = 16;
    m_attributes[10] = EGL_NONE;
}

Screen::~Screen()
{
    delete[] m_attributes;
}

// ----
// Methods
// ----

void Screen::init()
{
    attachDevice();
    attachDisplay();
    setEGLDisplayConnection();
    attachLayer();
    initEGLDisplayConnection();
    searchForLayerAndEGLConfig();
    create3DTarget();
    enableLayer();
    createEGLContext();
    createEGLSurface();
    connectEGLContextWithSurface();
    m_isInitialized = true;
}

void Screen::uninit()
{
    assert(m_isInitialized, "Screen is not initialized");
    destroyEGLSurface();
    destroyEGLContext();
    free3DTarget();
    detachLayer();
    detachDisplay();
    detachDevice();
    m_isInitialized = false;
}

void Screen::attachDevice()
{
    int res = gf_dev_attach(&m_gfDevice, GF_DEVICE_INDEX(0), &m_gfDeviceInfo);
    if (res == GF_ERR_OK)
    {
        log("Device attached");
        return;
    }
    switch (res)
    {
    case GF_ERR_MEM:
        assert(false, "Failure to allocate memory for data structures");
        break;
    case GF_ERR_IODISPLAY:
        assert(false, "Could not access the /dev/io-display directory. Check to ensure that io-display is running");
        break;
    case GF_ERR_DEVICE:
        assert(false, "Could not find the requested device. Check the /dev/io-display directory to ensure the requested device is mounted");
        break;
    case GF_ERR_SHMEM:
        assert(false, "Could not open or map in the required shared memory");
        break;
    case GF_ERR_DLL:
        assert(false, "Error accessing the driver DLL or entrypoint");
        break;
    case GF_ERR_THREAD:
        assert(false, "Error registering thread");
        break;
    default:
        assert(false, "An unknown error occurred");
        break;
    }
}

void Screen::detachDevice()
{
    assert(m_gfDevice != NULL, "Device not attached");
    gf_dev_detach(m_gfDevice);
    log("Device detached");
}

void Screen::attachDisplay()
{
    int res = gf_display_attach(&m_gfDisplay, m_gfDevice, 0, &m_gfDisplayInfo);
    if (res == GF_ERR_OK)
    {
        m_layerIndex = m_gfDisplayInfo.main_layer_index;
        m_width = m_gfDisplayInfo.xres;
        m_height = m_gfDisplayInfo.yres;
        log("Display attached");
        return;
    }
    switch (res)
    {
    case GF_ERR_MEM:
        assert(false, "Memory allocation failure");
        break;
    case GF_ERR_IODISPLAY:
        assert(false, "Could not access the /dev/io-display directory. Check to ensure that io-display is running");
        break;
    case GF_ERR_PARM:
        assert(false, "The display index is out of bounds");
        break;
    case GF_ERR_CFG:
        assert(false, "Badly configured display; check the io-display configuration file");
        break;
    default:
        assert(false, "An unknown error occurred");
        break;
    }
}

void Screen::detachDisplay()
{
    assert(m_gfDisplay != NULL, "Display not attached");
    gf_display_detach(m_gfDisplay);
    log("Display detached");
}

void Screen::setEGLDisplayConnection()
{
    Display = eglGetDisplay(m_gfDevice);
    if (Display == NULL)
    {
        assert(false, "EGL display connection failed");
        return;
    }
    log("EGL display connected");
}

void Screen::attachLayer()
{
    int res = gf_layer_attach(&m_gfLayer, m_gfDisplay, m_layerIndex, GF_LAYER_ATTACH_PASSIVE);
    if (res == GF_ERR_OK)
    {
        log("Layer attached");
        return;
    }
    switch (res)
    {
    case GF_ERR_MEM:
        assert(false, "Memory allocation failure");
        break;
    case GF_ERR_PARM:
        assert(false, "Layer index is out of range for the specified display");
        break;
    case GF_ERR_INUSE:
        assert(false, "Layer is already in use; try attaching with the GF_LAYER_ATTACH_PASSIVE flag enabled");
        break;
    case GF_ERR_IODISPLAY:
        assert(false, "Error communicating with io-display. Check to ensure io-display is still running");
        break;
    default:
        assert(false, "An unknown error occurred");
        break;
    }
}

void Screen::detachLayer()
{
    assert(m_gfLayer != NULL, "Layer not attached");
    gf_layer_detach(m_gfLayer);
    log("Layer detached");
}

void Screen::initEGLDisplayConnection()
{
    EGLBoolean res = eglInitialize(Display, NULL, NULL);
    if (res != EGL_TRUE)
    {
        assert(false, "EGL display connection initialize failed");
        return;
    }
    log("EGL display connection initialized");
}

void Screen::searchForLayerAndEGLConfig()
{
    for (GLuint i = 0; i < 100; i++) // TODO
    {
        // Walk through all possible pixel formats for this layer
        bool layerFound = __searchForLayer(i);
        if (!layerFound)
            break;
        // We want the color buffer format to match the layer format, so request the layer format through EGL_NATIVE_VISUAL_ID.
        m_attributes[1] = m_gfLayerInfo.format;
        // Look for a compatible EGL frame buffer configuration
        bool eglConfigFound = __searchForEGLConfig();
        if (eglConfigFound)
            return;
    }
    assert(false, "Could not find a compatible EGL frame buffer configuration");
}

bool Screen::__searchForLayer(const int &t_formatIndex)
{
    int res = gf_layer_query(m_gfLayer, t_formatIndex, &m_gfLayerInfo);
    if (res == GF_ERR_OK)
    {
        log("Layer query was successful");
        return true;
    }
    switch (res)
    {
    case GF_ERR_IODISPLAY:
        assert(false, "Error communicating with io-display. Check to ensure io-display is still running");
        return false;
    case GF_ERR_PARM:
        assert(false, "An invalid layer parameter was passed, or an internal consistency error was encountered such as an invalid display number");
        return false;
    case GF_ERR_NOSUPPORT:
        assert(false, "A format index was passed that is out of range for the given layer");
        return false;
    default:
        assert(false, "An unknown error occurred");
        return false;
    }
}

bool Screen::__searchForEGLConfig()
{
    int res = eglChooseConfig(Display, m_attributes, &m_EGLConfig, 1, &m_EGLConfigNumber) == EGL_TRUE;
    if (res == EGL_TRUE)
    {
        if (m_EGLConfigNumber > 0)
        {
            log("EGL configuration found");
            return true;
        }
        return false;
    }
    assert(false, "EGL configuration search failed");
    return false;
}

void Screen::create3DTarget()
{
    int res = gf_3d_target_create(&m_gf3DTarget, m_gfLayer, NULL, 0, m_width, m_height, m_gfLayerInfo.format);
    if (res == GF_ERR_OK)
    {
        log("3D target created");
        return;
    }
    switch (res)
    {
    case GF_ERR_MEM:
        assert(false, "Memory allocation failure");
        break;
    default:
        assert(false, "An unknown error occurred");
        break;
    }
}

void Screen::free3DTarget()
{
    assert(m_gf3DTarget != NULL, "3D target not created");
    gf_3d_target_free(m_gf3DTarget);
    log("3D target freed");
}

void Screen::enableLayer()
{
    gf_layer_set_src_viewport(m_gfLayer, 0, 0, m_width - 1, m_height - 1);
    gf_layer_set_dst_viewport(m_gfLayer, 0, 0, m_width - 1, m_height - 1);
    gf_layer_enable(m_gfLayer);
    /*
	 * The layer settings haven't taken effect yet since we haven't
	 * called gf_layer_update() yet.  This is exactly what we want,
	 * since we haven't supplied a valid surface to display yet.
	 * Later, the OpenGL ES library calls will call gf_layer_update()
	 * internally, when  displaying the rendered 3D content.
	 */
    log("Layer enabled");
}

void Screen::createEGLContext()
{
    m_EGLContext = eglCreateContext(Display, m_EGLConfig, EGL_NO_CONTEXT, NULL);
    if (m_EGLContext == NULL)
    {
        assert(false, "EGL context creation failed");
        return;
    }
    log("EGL context created");
}

void Screen::destroyEGLContext()
{
    assert(m_EGLContext != NULL, "EGL context not created");
    eglDestroyContext(Display, m_EGLContext);
    log("EGL context destroyed");
}

void Screen::createEGLSurface()
{
    Surface = eglCreateWindowSurface(Display, m_EGLConfig, m_gf3DTarget, NULL);
    if (Surface == NULL)
    {
        assert(false, "EGL surface creation failed");
        return;
    }
    log("EGL surface created");
}

void Screen::destroyEGLSurface()
{
    assert(Surface != NULL, "EGL surface not created");
    eglDestroySurface(Display, Surface);
    log("EGL surface destroyed");
}

void Screen::connectEGLContextWithSurface()
{
    EGLBoolean res = eglMakeCurrent(Display, Surface, Surface, m_EGLContext);
    if (res == NULL)
    {
        assert(false, "EGL context connection with surface failed");
        return;
    }
    log("EGL context connected with surface");
}