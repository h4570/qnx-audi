/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#include "loaders/bmp_loader.hh"
#include "utils/debug.hh"
#include <cstdlib>
#include <xstring>

// ----
// Constructors/Destructors
// ----

BmpLoader::BmpLoader() {}

BmpLoader::~BmpLoader() {}

// ----
// Methods
// ----

void BmpLoader::load(Texture &o_texture, char *t_subfolder, char *t_name, char *t_extension)
{
    // How to copy files to Neutrino?
    std::string path = "/proj/";
    path.append(t_subfolder);
    path.append(t_name);
    path.append(t_extension);

    FILE *file = fopen(path.c_str(), "rb");
    assert(file != NULL, "Failed to load .bmp file!");

    unsigned char header[54];
    fread(header, sizeof(unsigned char), 54, file);

    uint32_t width = (uint32_t)header[18];
    uint32_t height = (uint32_t)header[22];
    uint32_t bits = (uint32_t)header[28];
    uint32_t dataOffset = (uint32_t)header[10];

    assert(bits == 24, "Invalid bits per pixel in .bmp file - expected 24!");

    o_texture.allocateMemory(width, height, TEX_TYPE_RGB);
    o_texture.setName(t_name);
    printf("BMPLoader - width: %d | height: %d | bits: %d\n", width, height, bits);

    uint64_t rowPadded = (width * 3 + 3) & (~3);

    unsigned char *row = new unsigned char[rowPadded];

    //Offset file stream to raster data
    fseek(file, dataOffset, SEEK_SET);

    uint32_t x = 0;
    for (uint32_t i = 0; i < height; i++)
    {
        fread(row, sizeof(unsigned char), rowPadded, file);
        for (uint32_t j = 0; j < width * 3; j += 3)
        {
            // Convert (B, G, R) to (R, G, B)
            o_texture.setData(x, row[j + 2]);
            o_texture.setData(x + 1, row[j + 1]);
            o_texture.setData(x + 2, row[j]);
            x += 3;
        }
    }
    path.erase();
    fclose(file);
    delete[] row;
}