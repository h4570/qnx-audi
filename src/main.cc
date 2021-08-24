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

#include <cstdlib>
#include "utils/debug.hh"
#include "modules/screen.hh"

void render()
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

int main(int argc, char *argv[])
{
  Screen screen;
  screen.init();

  glDisable(GL_DEPTH_TEST);
  if (glGetError())
    assert(false, "OpenGL calls gone wrong");

  // do
  for (int xd = 0; xd < 10000; xd++)
  {
    if (xd % 1000 == 0)
      log("Im here!\n");
    render();
    glFinish();
    eglWaitGL();
    eglSwapBuffers(screen.Display, screen.Surface);
  }
  // } while (1);

  screen.uninit();
  return EXIT_SUCCESS;
}
