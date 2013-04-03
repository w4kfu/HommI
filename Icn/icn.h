#ifndef __ICN_H__
#define __ICN_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Pal/pal.h"

struct icnentry
{
	unsigned short x;
	unsigned short y;
	unsigned short width;
	unsigned short height;
	unsigned int offset;
};

struct icn
{
	unsigned short numentry;
	struct icnentry *entry;
	unsigned char *data;
	unsigned int filesize;
};

struct icn *openicn(char *filename);
int icnfillentry(struct icn *icn);
void closeicn(struct icn *icn);
void printicninfo(struct icn *icn);

int icngetmaxheight(struct icn *icn);
int icngetmaxwidth(struct icn *icn);
unsigned char *icnmakeimg(struct icn *icn, int numentry, unsigned short width, unsigned short height,
			unsigned char *pal, unsigned int type);

#endif // __ICN_H__

