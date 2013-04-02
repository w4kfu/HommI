#include <stdio.h>
#include <stdlib.h>
#include <png.h>

#include "bmp.h"

void setRGB(png_byte *ptr, unsigned char r, unsigned char g, unsigned char b)
{
	ptr[0] = r;
	ptr[1] = g;
	ptr[2] = b;
}

int writeImage(char* filename, int width, int height, unsigned char *buffer, char* title)
{
	FILE *fp;
	png_structp png_ptr;
	png_infop info_ptr;
	png_bytep row;

	if (!(fp = fopen(filename, "wb")))
	{
		perror("fopen()");
		return 0;
	}
	if (!(png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL)))
	{
		fprintf(stderr, "Could not allocate write struct\n");
		fclose(fp);
		return 0;
	}
	if (!(info_ptr = png_create_info_struct(png_ptr)))
	{
		fprintf(stderr, "Could not allocate info struct\n");
		fclose(fp);
		return 0;
	}
	if (setjmp(png_jmpbuf(png_ptr)))
	{
		fprintf(stderr, "Error during png creation\n");
		fclose(fp);
		return 0;
	}
	png_init_io(png_ptr, fp);

	png_set_IHDR(png_ptr, info_ptr, width, height,
			8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
			PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

	if (title != NULL)
	{
		png_text title_text;
		title_text.compression = PNG_TEXT_COMPRESSION_NONE;
		title_text.key = "Title";
		title_text.text = title;
		png_set_text(png_ptr, info_ptr, &title_text, 1);
	}

	png_write_info(png_ptr, info_ptr);

	row = (png_bytep) malloc(3 * width * sizeof(png_byte));

	int x, y;
	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			int a = (x + (y * width)) * 3;
			setRGB(&(row[x*3]), buffer[a], buffer[a + 1], buffer[a + 2]);
		}
		png_write_row(png_ptr, row);
	}

	png_write_end(png_ptr, NULL);

	if (fp != NULL)
		fclose(fp);
	if (info_ptr != NULL)
		png_free_data(png_ptr, info_ptr, PNG_FREE_ALL, -1);
	if (png_ptr != NULL)
		png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
	if (row != NULL)
		free(row);
	return 1;
}

int main(int argc, char *argv[])
{
	struct bmp *bmp = NULL;

	if (argc != 4)
	{
		fprintf(stderr, "%s <*.BMP|*.bmp|*.bkg> <*.pal> outfile\n");
		return EXIT_FAILURE;
	}

	if ((bmp = convertbmp(argv[1], argv[2])))
	{
		writeImage(argv[3], bmp->width, bmp->height, bmp->data, argv[3]);
		closebmp(bmp);
	}
	return 0;
}
