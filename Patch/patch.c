#include "patch.h"

int checksig(FILE *infile)
{
	char buf[0x100];

	fseek(infile, 0x8FCA0, SEEK_SET);
	fread(buf, 0x20, 1, infile);
	if (strcmp(buf, "\\HEROES\\SOUND\\"))
	{
		fprintf(stderr, "[-] Sig fail\n");
		return 0;
	}
	fseek(infile, 0x8FB40, SEEK_SET);
	fread(buf, 0x20, 1, infile);
	if (strcmp(buf, "\\HEROES\\ANIM\\"))
	{
		fprintf(stderr, "[-] Sig fail\n");
		return 0;
	}
	fseek(infile, 0, SEEK_SET);
	return 1;
}

void copyfile(FILE *infile, FILE *outfile)
{
	int numr, numw;
	char buffer[100];

	while (feof(infile) == 0)
	{
		if ((numr = fread(buffer, 1, 100, infile)) != 100)
		{
			if (ferror(infile) != 0)
			{
				fprintf(stderr, "[-] Read file error.\n");
				exit(EXIT_FAILURE);
			}
		}
		if ((numw = fwrite(buffer, 1, numr, outfile)) != numr)
		{
			fprintf(stderr, "[-] Write file error.\n");
			exit(EXIT_FAILURE);
		}
	}

}

void patch(FILE *patchfile, FILE *outfile)
{
	unsigned char CallPatchFunc[] = {0xE8, 0xD7, 0xAF, 0x03, 0x00};
	unsigned char JmpRest[] = {0xEB, 0x25};

	fseek(outfile, 0x8A4A0, SEEK_SET);
	copyfile(patchfile, outfile);
	fseek(outfile, 0x4F4C4, SEEK_SET);
	if (fwrite(CallPatchFunc, 1, sizeof (CallPatchFunc), outfile) != sizeof (CallPatchFunc))
	{
		fprintf(stderr, "[-] Write file error.\n");
		exit(EXIT_FAILURE);
	}
	if (fwrite(JmpRest, 1, sizeof (JmpRest), outfile) != sizeof (JmpRest))
	{
		fprintf(stderr, "[-] Write file error.\n");
		exit(EXIT_FAILURE);
	}
}
