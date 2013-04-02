#ifndef __BMP_H__
#define __BMP_H__

#include <stdio.h>
#include <stdlib.h>

#include "../Pal/pal.h"

struct bmp
{
	unsigned short sig;
	unsigned short width;
	unsigned short height;
	unsigned char *buf;
	unsigned char *data;
};

struct bmp* convertbmp(char *filename, char *palettefile);
void closebmp(struct bmp *nbmp);


#endif // __BMP_H__

