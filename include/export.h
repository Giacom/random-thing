#ifndef EXPORT_H
#define EXPORT_H

#include "raylib.h"

void ExportTexture(Texture2D texture, bool flip);
void WriteToPNG(const char *fileName, unsigned char *imgData, int width, int height, int compSize);
Texture2D TestImage(Texture2D);

#endif /* EXPORT_H */