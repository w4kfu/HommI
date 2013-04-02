#include "agg.h"

void CloseAGG(struct aggfile *agg)
{
	if (!agg)
		return;
	if (agg->filename)
		free(agg->filename);
	if (agg->buf)
		free(agg->buf);
	if (agg->allentry)
		free(agg->allentry);
	fclose(agg->fin);
	free(agg);
}

unsigned short HashFilename(char *filename)
{
	unsigned char actual;
	unsigned short result = 0;

	while (*filename)
	{
		actual = *filename++ & 0x7F;
		if (actual >= 0x60)
			actual = actual - 32;
		result = ROL16((result >> 8) | ((result & 0xFF) << 8), 1) - actual;
	}
	return result;
}

void fillentry(struct aggfile *agg)
{
	struct aggentry *aggentry = NULL;
	char *bufname = NULL;
	unsigned int i;

	agg->numentry = *(unsigned short*)agg->buf;
	if (!(agg->allentry = malloc(sizeof (struct entry) * agg->numentry)))
	{
		perror("malloc()");
		return;
	}
	printf("NUM_ENTRY = %X\n", agg->numentry);
	bufname = (char*)(agg->buf + agg->bufsize - (agg->numentry * 15));
	aggentry = (struct aggentry*)(agg->buf + 2);
	for (i = 0; i < agg->numentry; i++)
	{
		agg->allentry[i].hash = aggentry->hash;
		agg->allentry[i].buf = agg->buf + aggentry->off;
		agg->allentry[i].size = aggentry->size;
		strncpy(agg->allentry[i].filename, bufname, 15 - 1);
		bufname += 15;
		aggentry++;
	}
}

int direxists(char* absolutePath)
{
	if (access(absolutePath, 0) == 0)
	{
        	struct stat status;
        	stat(absolutePath, &status);
        	if ((status.st_mode & S_IFDIR) == 0)
			return 0;
		return 1;
    	}
    	return 0;
}

void dump_to_file(char *filename, unsigned char *buf, size_t size)
{
	FILE *fout;

	if (!(fout = fopen(filename, "wb")))
	{
		perror("fopen()");
		return;
	}
	fwrite(buf, 1, size, fout);
	fclose(fout);
}

void extractall(struct aggfile *agg, char *outputdir)
{
	char output_name[4096];
	unsigned int i;

	if (!direxists(outputdir))
		return;
	for (i = 0; i < agg->numentry; i++)
	{
		strcpy(output_name, outputdir);
  		strcat(output_name, agg->allentry[i].filename);
		dump_to_file(output_name, agg->allentry[i].buf, agg->allentry[i].size);
	}
}

void InfoAGG(struct aggfile *agg)
{
	unsigned int i;

	printf("Filename = %s\n", agg->filename);
	printf("NumEntry = %X\n", agg->numentry);
	for (i = 0; i < agg->numentry; i++)
	{
		printf("Hash = %X\n", agg->allentry[i].hash);
		printf("Name = %s\n", agg->allentry[i].filename);
		printf("Size = %X\n", agg->allentry[i].size);
	}
}

struct aggfile *OpenAGG(char *filename)
{
	struct aggfile *newagg = NULL;

	if (!(newagg = malloc(sizeof (struct aggfile))))
	{
		perror("malloc()");
		return NULL;
	}
	newagg->filename = strdup(filename);
	if (!(newagg->fin = fopen(filename, "rb")))
	{
		perror("fopen()");
		CloseAGG(newagg);
		return NULL;
	}
        fseek(newagg->fin,0, SEEK_END);
        newagg->bufsize = ftell(newagg->fin);
        fseek(newagg->fin, 0, SEEK_SET);
	if (!(newagg->buf = malloc(sizeof (char) * newagg->bufsize)))
	{
		perror("fopen()");
		CloseAGG(newagg);
		return NULL;
	}
	if (fread(newagg->buf, 1, newagg->bufsize, newagg->fin) != newagg->bufsize)
	{
		perror("fread()");
		CloseAGG(newagg);
		return NULL;
	}
	return newagg;
}
