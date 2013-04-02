#ifndef __AGG_H__
#define __AGG_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define ROL16(x,xx) (((x)<<(xx)) | (((x)&0xFFFF)>>(16-(xx))))

struct entry
{
	unsigned char *buf;
	unsigned int size;
	unsigned short hash;
	char filename[15];
};

struct aggfile
{
	char *filename;
	FILE *fin;
	unsigned char *buf;
	unsigned int bufsize;
	unsigned short numentry;
	struct entry *allentry;
};


struct aggentry
{
	unsigned short hash;
	unsigned int off;
	unsigned int size;
	unsigned int another_size;
}__attribute__((packed));

struct aggfile *OpenAGG(char *filename);
unsigned short HashFilename(char *filename);
void CloseAGG(struct aggfile *agg);
void InfoAGG(struct aggfile *agg);
void fillentry(struct aggfile *agg);
void extractall(struct aggfile *agg, char *outputdir);

#endif // __AGG_H__

