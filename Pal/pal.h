#ifndef __PAL_H__
#define __PAL_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct color
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
};

unsigned char *init_palette(FILE *fin);
unsigned char *expand_palette(unsigned char *pal, unsigned square_width, unsigned square_height);

#endif // __PAL_H__

