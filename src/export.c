#include "export.h"
#include "raylib.h"
#include <external/stb_image_write.h>
#include <stdio.h>

void ExportTexture(Texture2D texture, bool flip)
{
	printf("%i", texture.format);
	Image image = GetTextureData(texture);

	if (flip) {
		printf("Flipping the duck.\n");
		//ImageFlipVertical(&image);
		//ImageColorTint(&image, RED);
	}

	printf("Writing to test.png.\n%i, %i, %i\n", image.format, image.width, image.height);
	WriteToPNG("test.png", image.data, image.width, image.height, 3);
	printf("Finished writing image to disk.\n");
	UnloadImage(image);
}

Texture2D TestImage(Texture2D texture)
{
	Image image = GetTextureData(texture);
	Texture2D newTexture = LoadTextureFromImage(image);
	UnloadImage(image);
	return newTexture;
}

void WriteToPNG(const char *fileName, unsigned char *imgData, int width, int height, int compSize)
{
	stbi_write_png(fileName, width, height, compSize, imgData, width * compSize);
}