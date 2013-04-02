#include "bmp.h"

struct bmp *openbmp(char *filename)
{
	struct bmp *newbmp = NULL;
	FILE *fin = NULL;
	unsigned int filesize = 0;

	if (!(fin = fopen(filename, "rb")))
	{
		perror("fopen()");
		return NULL;
	}
	if (!(newbmp = malloc(sizeof (struct bmp))))
	{
		perror("malloc()");
		return NULL;
	}

        fseek(fin, 0, SEEK_END);
        filesize = ftell(fin);
        fseek(fin, 0, SEEK_SET);
	if (!(newbmp->buf = malloc(sizeof (char) * filesize)))
	{
		perror("malloc()");
		free(newbmp);
		fclose(fin);
		return NULL;
	}
	if (fread(newbmp->buf, 1, filesize, fin) != filesize)
	{
		perror("fread()");
		free(newbmp);
		fclose(fin);
		return NULL;
	}
	memcpy(newbmp, newbmp->buf, 3 * sizeof (unsigned short));
	if (newbmp->sig != 0x0021)
	{
		fprintf(stderr, "[-] Wrong signature\n");
		free(newbmp->buf);
		free(newbmp);
		fclose(fin);
		return NULL;
	}
	newbmp->data = NULL;
	fclose(fin);
	return newbmp;
}

void closebmp(struct bmp *nbmp)
{
	if (nbmp)
	{
		if (nbmp->buf)
			free(nbmp->buf);
		if (nbmp->data)
			free(nbmp->data);
		free(nbmp);
	}
}

struct bmp* convertbmp(char *filename, char *palettefile)
{
	struct bmp *newbmp = NULL;
	unsigned char *pal = NULL;
	unsigned char *newdata = NULL;
	struct color *rgb = NULL;
	unsigned int y, x;

	if (!(pal = open_palette(palettefile)))
		return NULL;
	if (!(newbmp = openbmp(filename)))
	{
		free(pal);
		return NULL;
	}
	if (!(newdata = malloc(sizeof (char) * newbmp->width * newbmp->height * 3)))
	{
		perror("malloc()");
		free(pal);
		free(newbmp);
		return NULL;
	}
	newbmp->data = newdata;
	rgb = (struct color *)pal;
	for (y = 0; y < newbmp->height; y++)
	{
		for (x = 0; x < newbmp->width; x++)
		{
			memcpy(newdata, &rgb[*(newbmp->buf + (3 * 2) + (x + (y * newbmp->width)))], 3);
			newdata += 3;
		}
	}
	free(pal);
	return newbmp;
}
