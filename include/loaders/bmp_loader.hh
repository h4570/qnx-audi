/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#ifndef _QNX_AUDI_BMP_LOADER_
#define _QNX_AUDI_BMP_LOADER_

#include <stdio.h>
#include "models/texture.hh"

/** Class responsible for loading images in bmp format */
class BmpLoader
{

public:
    BmpLoader();
    ~BmpLoader();

    /**
     * @param t_subfolder Example "proj/" or "" if no subfolder
     * @param t_name Without extension. Example "skyfall2"
     * @param t_extension With dot and extension. Example ".BMP"
     */
    void load(Texture &o_texture, char *t_subfolder, char *t_name, char *t_extension);
};

#endif