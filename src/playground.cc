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

#include <termios.h>

#include <malloc.h>
#define STBTT_assert(x) Debug::_assert(x, "STBI Error", __FILE__, __LINE__)
#define STB_TRUETYPE_IMPLEMENTATION
#include "external/stb_truetype.h"

#include <stdio.h> // file

const float maxX = 512.0F;
const float maxY = 32.0F;

const GLfloat vertices[] = {0, maxY, 0, 0, maxX, 0, maxX, maxY};
const GLfloat texCoords[] = {
    0, 1, // 4
    0, 0, // 3
    1, 0, // 2
    1, 1  // 1
};
//    const GLfloat texCoords[] = {
// 1, 1,
//  1, 0,
//   0, 0,
//    0, 1};
const GLubyte indices[] = {0, 1, 2, 0, 2, 3};

void test()
{
  /* load font file */
  long size;
  unsigned char *fontBuffer;

  FILE *fontFile = fopen("/proj/righteous.ttf", "rb");
  fseek(fontFile, 0, SEEK_END);
  size = ftell(fontFile);       /* how long is the file ? */
  fseek(fontFile, 0, SEEK_SET); /* reset */

  fontBuffer = (unsigned char *)malloc(size);

  fread(fontBuffer, size, 1, fontFile);
  fclose(fontFile);

  /* prepare font */
  stbtt_fontinfo info;
  if (!stbtt_InitFont(&info, fontBuffer, 0))
  {
    printf("failed\n");
  }

  int b_w = 512; /* bitmap width */
  int b_h = 32;  /* bitmap height */
  int l_h = 32;  /* line height */

  /* create a bitmap for the phrase */
  unsigned char *bitmap = (unsigned char *)calloc(b_w * b_h, sizeof(unsigned char));

  /* calculate font scaling */
  float scale = stbtt_ScaleForPixelHeight(&info, l_h);

  char *word = "Lorem ipsum dolor sit amet, consectetur";

  int x = 0;

  int ascent, descent, lineGap;
  stbtt_GetFontVMetrics(&info, &ascent, &descent, &lineGap);

  ascent = (int)roundf(ascent * scale);
  descent = (int)roundf(descent * scale);

  // na przyszlosc
  //  stbtt_BakeFontBitmap(ttf_buffer,0, 64.0, temp_bitmap,1024,1024, 32,96, cdata);

  unsigned int i;
  for (i = 0; i < strlen(word); ++i)
  {
    /* how wide is this character */
    int ax;
    int lsb;
    stbtt_GetCodepointHMetrics(&info, word[i], &ax, &lsb);
    /* (Note that each Codepoint call has an alternative Glyph version which caches the work required to lookup the character word[i].) */

    /* get bounding box for character (may be offset to account for chars that dip above or below the line */
    int c_x1, c_y1, c_x2, c_y2;
    stbtt_GetCodepointBitmapBox(&info, word[i], scale, scale, &c_x1, &c_y1, &c_x2, &c_y2);

    /* compute y (different characters have different heights */
    int y = ascent + c_y1;

    /* render character (stride and offset is important here) */
    int byteOffset = x + roundf(lsb * scale) + (y * b_w);
    stbtt_MakeCodepointBitmap(&info, bitmap + byteOffset, c_x2 - c_x1, c_y2 - c_y1, b_w, scale, scale, word[i]);

    /* advance x */
    x += roundf(ax * scale);

    /* add kerning */
    int kern;
    kern = stbtt_GetCodepointKernAdvance(&info, word[i], word[i + 1]);
    x += roundf(kern * scale);
  }

  //

  GLuint textureIds[1];
  GL_CHECK(glGenTextures(1, textureIds));
  int textureId = textureIds[0];
  GL_CHECK(glEnable(GL_TEXTURE_2D));
  GL_CHECK(glEnable(GL_BLEND));
  GL_CHECK(glActiveTexture(GL_TEXTURE0));
  GL_CHECK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
  GL_CHECK(glBindTexture(GL_TEXTURE_2D, textureId));
  GL_CHECK(glColor4f(1.0f, 1.0f, 1.0f, 1.0f));
  GL_CHECK(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
  GL_CHECK(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
  GL_CHECK(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
  GL_CHECK(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
  GL_CHECK(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));

  GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, b_w, b_h, 0, GL_ALPHA, GL_UNSIGNED_BYTE, bitmap));

  GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));
  GL_CHECK(glEnableClientState(GL_TEXTURE_COORD_ARRAY));
  GL_CHECK(glTexCoordPointer(2, GL_FLOAT, 0, texCoords));
  GL_CHECK(glVertexPointer(2, GL_FLOAT, 0, vertices));
  GL_CHECK(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices));

  //

  free(fontBuffer);
  free(bitmap);
}

void render()
{
  Texture texture("/proj/car2.png", "car", TEX_TYPE_RGBA);

  GL_CHECK(glMatrixMode(GL_PROJECTION));
  GL_CHECK(glLoadIdentity());
  GL_CHECK(glOrthof(0, 512, 512, 0, 0, 1));
  GL_CHECK(glMatrixMode(GL_MODELVIEW));
  GL_CHECK(glClearColor(.7F, .7F, .7F, 1.0F));
  GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

  // GLuint textureIds[1];
  // GL_CHECK(glGenTextures(1, textureIds));
  // int textureId = textureIds[0];
  // GL_CHECK(glEnable(GL_TEXTURE_2D));
  // GL_CHECK(glEnable(GL_BLEND));
  // GL_CHECK(glActiveTexture(GL_TEXTURE0));
  // GL_CHECK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
  // GL_CHECK(glBindTexture(GL_TEXTURE_2D, textureId));
  // GL_CHECK(glColor4f(1.0f, 1.0f, 1.0f, 1.0f));
  // GL_CHECK(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
  // GL_CHECK(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
  // GL_CHECK(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
  // GL_CHECK(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
  // GL_CHECK(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));

  // GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, texture.getGlType(), texture.getWidth(), texture.getHeight(), 0, texture.getGlType(), GL_UNSIGNED_BYTE, texture.getData()));

  // GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));
  // GL_CHECK(glEnableClientState(GL_TEXTURE_COORD_ARRAY));
  // GL_CHECK(glTexCoordPointer(2, GL_FLOAT, 0, texCoords));
  // GL_CHECK(glVertexPointer(2, GL_FLOAT, 0, vertices));
  // GL_CHECK(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices));

  test();
};

#include <termios.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  Screen screen;
  screen.init();

  GL_CHECK(glDisable(GL_DEPTH_TEST));

  // int bytes_to_read;
  // char buf[1000];
  // struct termios termios_p;
  // // Set raw mode:
  // if (tcgetattr(1, &termios_p) == -1)
  //   assert(false, "tcgetattr");
  // if (cfmakeraw(&termios_p) == -1)
  //   assert(false, "cfmakeraw");
  // if (tcsetattr(1, TCSADRAIN, &termios_p) == -1)
  //   assert(false, "tcsetattr");

  for (int xd = 0; xd < 50; xd++)
  {
    if (xd % 20 == 0)
      logMessage("Im here!");

    // bytes_to_read = tcischars(1); // kbhit
    // if (bytes_to_read == -1)
    //   assert(false, "tcischars");

    // if (bytes_to_read > 0)
    // {
    //   fprintf(stdout, "kbhit %d", bytes_to_read);
    //   read(1, buf, bytes_to_read); // getch()
    // }

    render();
    GL_CHECK(glFinish());
    eglWaitGL();
    eglSwapBuffers(screen.Display, screen.Surface);
  }

  screen.uninit();
  return EXIT_SUCCESS;
}
