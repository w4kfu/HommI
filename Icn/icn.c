#include "icn.h"

struct icn *openicn(char *filename)
{
	struct icn *newicn = NULL;
	FILE *fin = NULL;

	if (!filename)
		return NULL;

	if (!(fin = fopen(filename, "rb")))
	{
		perror("fopen()");
		return NULL;
	}
	if (!(newicn = malloc(sizeof (struct icn))))
	{
		perror("malloc()");
		fclose(fin);
		return NULL;
	}
	fseek(fin, 0, SEEK_END);
        newicn->filesize = ftell(fin);
        fseek(fin, 0, SEEK_SET);
	if (!(newicn->data = malloc(sizeof (char) * newicn->filesize)))
	{
		perror("malloc()");
		fclose(fin);
		free(newicn);
		return NULL;
	}
	if (fread(newicn->data, 1, newicn->filesize, fin) != newicn->filesize)
	{
		perror("fread()");
		fclose(fin);
		free(newicn);
		free(newicn->data);
		return NULL;
	}
	if (((*(unsigned int*)newicn->data + 2) != newicn->filesize) && !icnfillentry(newicn))
	{
		fclose(fin);
		free(newicn);
		free(newicn->data);
		return NULL;
	}
	fclose(fin);
	return newicn;
}

void closeicn(struct icn *icn)
{
	if (icn)
	{
		if (icn->entry)
			free(icn->entry);
		if (icn->data)
			free(icn->data);
		free(icn);
	}
}

void printicninfo(struct icn *icn)
{
	unsigned int i;

	if (!icn)
		return;

	printf("NumEntry = %X\n", icn->numentry);
	for (i = 0; i < icn->numentry; i++)
	{
		printf("Width = %X\n", icn->entry[i].width);
		printf("Height = %X\n", icn->entry[i].height);
		printf("Offset = %X\n", icn->entry[i].offset);
	}
}

int icngetmaxwidth(struct icn *icn)
{
	unsigned int width = 0;
	unsigned int i;

	if (!icn)
		return width;

	for (i = 0; i < icn->numentry; i++)
	{
		if (icn->entry[i].width > width)
			width = icn->entry[i].width;
	}
	return width;
}

int icngetmaxheight(struct icn *icn)
{
	unsigned int height = 0;
	unsigned int i;

	if (!icn)
		return height;

	for (i = 0; i < icn->numentry; i++)
	{
		if (icn->entry[i].height > height)
			height = icn->entry[i].height;
	}
	return height;
}

unsigned char *icnmakeimg(struct icn *icn, int numentry, unsigned short width, unsigned short height)
{
	unsigned char *imgbuf = NULL;
	unsigned char *simgbuf = NULL;
	unsigned char *databuf = NULL;
	unsigned char actual = 0;
	unsigned short actual_width = 0;
	struct color color1;
	struct color color2;
	unsigned int x;

	color1.r = 0xFF; color1.g = 0xFF; color1.b = 0xFF;
	color2.r = 0; color2.g = 0; color2.b = 0;
	if (!icn)
		return NULL;
	if (!(imgbuf = malloc(sizeof (char) * width * height * 3)))
	{
		perror("malloc()");
		return NULL;
	}
	memset(imgbuf, 0x3F, sizeof (char) * width * height * 3);
	simgbuf = imgbuf;
	databuf = icn->entry[numentry].offset + icn->data + 6;
	while (*databuf != 0x80)
	{
		actual = *databuf++;
		if (actual == 0)
		{
			// new line
			for (x = actual_width; x < width; x++)
			{
				memcpy(imgbuf, &color1, sizeof (struct color));
				imgbuf += 3;
			}
			actual_width = 0;
		}
		else if (actual > 0x80)
		{
			actual &= 0x7F;
			for (x = 0; x < actual; x++)
			{
				memcpy(imgbuf, &color1, sizeof (struct color));
				imgbuf += 3;
			}
			actual_width += actual;
		}
		else
		{
			for (x = 0; x < actual; x++)
			{
				memcpy(imgbuf, &color2, sizeof (struct color));
				imgbuf += 3;
			}
			actual_width += actual;
		}
		if (actual_width == width)
			actual_width = 0;
	}
	if ((imgbuf - simgbuf) != (width * height * 3))
	{
		x = (width * height * 3) - (imgbuf - simgbuf);
		x /= 3;
		for (; x > 0; x--)
		{
			memcpy(imgbuf, &color1, sizeof (struct color));
			imgbuf += 3;
		}
	}
	return simgbuf;
}

int icnfillentry(struct icn *icn)
{
	unsigned int i;

	if (!icn)
		return 0;

	icn->numentry = *(unsigned short*)icn->data;
	if (!(icn->entry = malloc(sizeof (struct icn) * icn->numentry)))
	{
		perror("malloc()");
		return 0;
	}
	for (i = 0; i < icn->numentry; i++)
	{
		memcpy(&icn->entry[i], icn->data + 2 + 4 + i * sizeof (struct icnentry), sizeof (struct icnentry));
	}
	return 1;
}
