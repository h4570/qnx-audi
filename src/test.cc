#include <cstdlib>
#include <iostream>

#include <stdio.h>

#include <gf/gf.h>
#include <gf/gf3d.h>
#include <GLES/gl.h>
#include <GLES/egl.h>

gf_dev_t gfdev;
gf_layer_t layer;
int layer_idx;
static EGLDisplay display;
static EGLSurface surface;
//////////////////////////////////////////////////////////////////////////////////////////

static EGLint attribute_list[] = {EGL_NATIVE_VISUAL_ID, 0,
                                  //    EGL_NATIVE_RENDERABLE, EGL_TRUE,
                                  EGL_RED_SIZE, 5,
                                  EGL_GREEN_SIZE, 5,
                                  EGL_BLUE_SIZE, 5,
                                  EGL_DEPTH_SIZE, 16,
                                  EGL_NONE};
//////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
using namespace std;

void log(const char *text)
{
    //return;
    ofstream myfile;
    myfile.open("/mnt/sdcard10t12/logs/log.txt", std::ios_base::app);
    myfile << text;
    myfile.close();
}

int init_scene()
{

    glDisable(GL_DEPTH_TEST);

    if (glGetError())
    {
        log("Oops! I screwed up my OpenGL ES calls somewhere\n");
        return -1;
    }

    return 1;
}
//////////////////////////////////////////////////////////////////////////////////////////

void render_scene()
{

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrthof(0, 512, 512, 0, 0, 1);
    glMatrixMode(GL_MODELVIEW);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    const GLfloat line[] = {
        0, 0,    //point A
        50, 200, //point B
    };

    glColor4f(0.0f, 1.0f, 0.0f, 1.0f); //line color
    glVertexPointer(2, GL_FLOAT, 0, line);
    glEnableClientState(GL_VERTEX_ARRAY);

    glDrawArrays(GL_LINES, 0, 2);
};
//////////////////////////////////////////////////////////////////////////////////////////

int REFACTOR_ME(int argc, char **argv)
{
    gf_dev_info_t info;
    gf_display_t gf_disp;
    gf_display_info_t disp_info;
    GLuint width, height;
    EGLConfig config;
    gf_layer_info_t linfo;
    EGLint num_config;
    gf_3d_target_t target;
    EGLContext econtext;

    log("Start\n");

    // pamietac o detach
    if (gf_dev_attach(&gfdev, GF_DEVICE_INDEX(0), &info) != GF_ERR_OK)
    {
        printf("ERROR: gf_dev_attach()\n");
        log("ERROR: gf_dev_attach()\n");
        return -1;
    }
    else
    {
        printf("SUCCESS: gf_dev_attach()\n");
        log("SUCCESS: gf_dev_attach()\n");
    }

    /* Setup the layer we will use */
    if (gf_display_attach(&gf_disp, gfdev, 0, &disp_info) != GF_ERR_OK)
    {
        fprintf(stderr, "ERROR: gf_display_attach()\n");
        log("ERROR: gf_display_attach()\n");
        return -1;
    }
    else
    {
        fprintf(stdout, "SUCCESS: gf_display_attach()\n");
        log("SUCCESS: gf_display_attach()\n");
    }

    layer_idx = disp_info.main_layer_index;

    /* get an EGL display connection */
    display = eglGetDisplay(gfdev);
    if (display == EGL_NO_DISPLAY)
    {
        fprintf(stderr, "ERROR: eglGetDisplay()\n");
        log("ERROR: eglGetDisplay()\n");
        return -1;
    }
    else
    {
        fprintf(stdout, "SUCCESS: eglGetDisplay()\n");
        log("SUCCESS: eglGetDisplay()\n");
    }

    width = disp_info.xres;
    height = disp_info.yres;

    int layer_attach = gf_layer_attach(&layer, gf_disp, layer_idx,
                                       GF_LAYER_ATTACH_PASSIVE);
    if (layer_attach != GF_ERR_OK)
    {
        if (layer_attach == GF_ERR_MEM)
        {
            fprintf(stderr, "ERROR: gf_layer_attach() - memory\n");
            log("ERROR: gf_layer_attach() - memory\n");
        }
        else if (layer_attach == GF_ERR_PARM)
        {
            fprintf(stderr, "ERROR: gf_layer_attach() - param\n");
            log("ERROR: gf_layer_attach() - param\n");
        }
        else if (layer_attach == GF_ERR_INUSE)
        {
            fprintf(stderr, "ERROR: gf_layer_attach() - in use\n");
            log("ERROR: gf_layer_attach() - in use\n");
        }
        else if (layer_attach == GF_ERR_IODISPLAY)
        {
            fprintf(stderr, "ERROR: gf_layer_attach() - io display\n");
            log("ERROR: gf_layer_attach() - io display\n");
        }
        return -1;
    }
    else
    {
        fprintf(stdout, "SUCCESS: gf_layer_attach()\n");
        log("SUCCESS: gf_layer_attach()\n");
    }

    /* initialize the EGL display connection */
    if (eglInitialize(display, NULL, NULL) != EGL_TRUE)
    {
        fprintf(stderr, "ERROR: eglInitialize: error 0x%x\n", eglGetError());
        log("ERROR: eglInitialize: error\n");
        return -1;
    }
    else
    {
        fprintf(stdout, "SUCCESS: eglInitialize()\n");
        log("SUCCESS: eglInitialize()\n");
    }

    GLuint it;
    // SIEDZI W NIESKONCZONYM LOOPIE!
    for (it = 0; it < 100; it++)
    {
        /* Walk through all possible pixel formats for this layer */
        if (gf_layer_query(layer, it, &linfo) == -1)
        {
            fprintf(stderr, "Couldn't find a compatible frame "
                            "buffer configuration on layer %d\n",
                    layer_idx);
            log("Couldn't find a compatible frame\n");
            return -1;
        }
        else
        {
            fprintf(stdout, "SUCCESS: gf_layer_query()\n");
            log("SUCCESS: gf_layer_query()\n");
        }

        /*
		 * We want the color buffer format to match the layer format,
		 * so request the layer format through EGL_NATIVE_VISUAL_ID.
		 */
        attribute_list[1] = linfo.format;

        /* Look for a compatible EGL frame buffer configuration */
        if (eglChooseConfig(display, attribute_list, &config, 1, &num_config) == EGL_TRUE)
        {
            fprintf(stdout, "SUCCESS: eglChooseConfig()\n");
            log("SUCCESS: eglChooseConfig()\n");

            if (num_config > 0)
            {
                fprintf(stdout, "SUCCESS: enum_config > 0\n");
                log("SUCCESS: enum_config > 0\n");
                break;
            }
        }
        else
        {
            fprintf(stderr, "ERROR: eglChooseConfig()\n");
            log("ERROR: eglChooseConfig()\n");
        }
    }

    /* create a 3D rendering target */
    int create_target = gf_3d_target_create(&target, layer, NULL, 0, width,
                                            height, linfo.format);
    if (create_target != GF_ERR_OK)
    {
        fprintf(stderr, "Unable to create rendering target\n");
        log("Unable to create rendering target\n");
        if (create_target == GF_ERR_MEM)
        {
            fprintf(stderr, "ERROR: gf_3d_target_create() - memory\n");
            log("ERROR: gf_3d_target_create()\n");
        }
        return -1;
    }
    else
    {
        fprintf(stdout, "SUCCESS: gf_3d_target_create()\n");
        log("SUCCESS: gf_3d_target_create()\n");
    };

    gf_layer_set_src_viewport(layer, 0, 0, width - 1, height - 1);
    gf_layer_set_dst_viewport(layer, 0, 0, width - 1, height - 1);
    gf_layer_enable(layer);

    /*
	 * The layer settings haven't taken effect yet since we haven't
	 * called gf_layer_update() yet.  This is exactly what we want,
	 * since we haven't supplied a valid surface to display yet.
	 * Later, the OpenGL ES library calls will call gf_layer_update()
	 * internally, when  displaying the rendered 3D content.
	 */

    /* create an EGL rendering context */
    econtext = eglCreateContext(display, config, EGL_NO_CONTEXT, NULL);
    if (econtext == EGL_NO_CONTEXT)
    {
        fprintf(stderr, "Create context failed: 0x%x\n", eglGetError());
        log("Create context failed\n");
        return -1;
    }
    else
    {
        fprintf(stdout, "SUCCESS: eglCreateContext()\n");
        log("SUCCESS: eglCreateContext()\n");
    };

    /* create an EGL window surface */
    surface = eglCreateWindowSurface(display, config, target, NULL);
    if (surface == EGL_NO_SURFACE)
    {
        fprintf(stderr, "Create surface failed: 0x%x\n", eglGetError());
        log("Create surface failed\n");
        return -1;
    }
    else
    {
        fprintf(stdout, "SUCCESS: eglCreateWindowSurface()\n");
        log("SUCCESS: eglCreateWindowSurface()\n");
    };

    /* connect the context to the surface */
    if (eglMakeCurrent(display, surface, surface, econtext) == EGL_FALSE)
    {
        fprintf(stderr, "Make current failed: 0x%x\n", eglGetError());
        log("Make current failed\n");
        return -1;
    }
    else
    {
        fprintf(stdout, "SUCCESS: eglMakeCurrent()\n");
        log("SUCCESS: eglMakeCurrent()\n");
    }

    log("End!\n");

    init_scene();

    for (int xd = 0; xd < 10000; xd++)
    //    do
    {
        if (xd % 1000 == 0)
            log("Im here!\n");
        render_scene();
        glFinish();
        eglWaitGL();
        eglSwapBuffers(display, surface);
        //    } while (1);
    }

    return 0;
}
