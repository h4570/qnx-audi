/*

                                                __         
                                               /\ \  __    
   __     ___    __  _         __     __  __   \_\ \/\_\   
 /'__`\ /' _ `\ /\ \/'\      /'__`\  /\ \/\ \  /'_` \/\ \  
/\ \L\ \/\ \/\ \\/>  </     /\ \L\.\_\ \ \_\ \/\ \L\ \ \ \ 
\ \___, \ \_\ \_\/\_/\_\    \ \__/.\_\\ \____/\ \___,_\ \_\
 \/___/\ \/_/\/_/\//\/_/     \/__/\/_/ \/___/  \/__,_ /\/_/
      \ \_\                                                
       \/_/                                                

# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#include "utils/debug.hh"
#include "modules/screen.hh"
#include "models/texture.hh"

#include <malloc.h>
#define STBI_ASSERT(x) Debug::_assert(x, "STBI Error", __FILE__, __LINE__)
#define STB_TRUETYPE_IMPLEMENTATION
#include "external/stb_truetype.h"

void render()
{
  Texture texture("/proj/car2.png", "car", TEX_TYPE_RGBA);

  GL_CHECK(glMatrixMode(GL_PROJECTION));
  GL_CHECK(glLoadIdentity());
  GL_CHECK(glOrthof(0, 512, 512, 0, 0, 1));
  GL_CHECK(glMatrixMode(GL_MODELVIEW));
  GL_CHECK(glClearColor(.7F, .7F, .7F, 1.0F));
  GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

  const GLfloat vertices[] = {0, 200, 0, 0, 200, 0, 200, 200};
  const GLfloat texCoords[] = {1, 1, 1, 0, 0, 0, 0, 1};
  const GLubyte indices[] = {0, 1, 2, 0, 2, 3};

  GLuint textureIds[1];
  GL_CHECK(glGenTextures(1, textureIds));
  int textureId = textureIds[0];
  GL_CHECK(glEnable(GL_TEXTURE_2D));
  GL_CHECK(glEnable(GL_BLEND));
  GL_CHECK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
  GL_CHECK(glBindTexture(GL_TEXTURE_2D, textureId));
  GL_CHECK(glColor4f(1.0f, 1.0f, 1.0f, 1.0f));
  GL_CHECK(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
  GL_CHECK(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
  GL_CHECK(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
  GL_CHECK(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
  GL_CHECK(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));

  GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, texture.getGlType(), texture.getWidth(), texture.getHeight(), 0, texture.getGlType(), GL_UNSIGNED_BYTE, texture.getData()));

  GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));
  GL_CHECK(glEnableClientState(GL_TEXTURE_COORD_ARRAY));
  GL_CHECK(glTexCoordPointer(2, GL_FLOAT, 0, texCoords));
  GL_CHECK(glVertexPointer(2, GL_FLOAT, 0, vertices));
  GL_CHECK(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices));
};

int main(int argc, char *argv[])
{
  Screen screen;
  screen.init();

  GL_CHECK(glDisable(GL_DEPTH_TEST));

  // do
  // for (int xd = 0; xd < 300; xd++)
  // {
  // if (xd % 100 == 0)
  // log("Im here!\n");
  render();
  GL_CHECK(glFinish());
  eglWaitGL();
  eglSwapBuffers(screen.Display, screen.Surface);
  // }
  // } while (1);

  screen.uninit();
  return EXIT_SUCCESS;
}
