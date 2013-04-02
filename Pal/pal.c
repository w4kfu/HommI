#include "pal.h"

unsigned char *init_palette(FILE *fin)
{
	unsigned char *pal = NULL;
	unsigned int filesize;

	if (!(pal = malloc(sizeof (struct color) * 256)))
	{
		perror("malloc()");
		return NULL;
	}
        fseek(fin, 0, SEEK_END);
        filesize = ftell(fin);
        fseek(fin, 0, SEEK_SET);
	if (filesize != (256 * 3))
	{
		fprintf(stderr, "[-] Palette not handled\n");
		free(pal);
		return NULL;
	}
	if (fread(pal, 1, filesize, fin) != filesize)
	{
		perror("fread()");
		free(pal);
		return NULL;
	}
	return pal;
}

unsigned char *expand_palette(unsigned char *pal, unsigned square_width, unsigned square_height)
{
	unsigned char *newpal = NULL;
	unsigned char *spal = NULL;
	unsigned int i, j, k, l;

	if (!(newpal = malloc(sizeof (char) * 256 * 3 * square_width * square_height)))
	{
		perror("malloc()");
		return NULL;
	}
	spal = newpal;
	for (i = 0; i < 16; i++)
	{
		for (j = 0; j < square_height; j++)
		{
			for (k = 0; k < 16; k++)
			{
				struct color *rgb;
				rgb = (struct color*)&pal[(k + (i * 16)) * 3];
				for (l = 0; l < square_width; l++)
				{
					memcpy(newpal, rgb, sizeof (struct color));
					newpal += 3;
				}
			}
		}
	}
	return spal;
}
