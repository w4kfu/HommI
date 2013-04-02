#ifndef __PATCH_H__
#define __PATCH_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void patch(FILE *patchfile, FILE *outfile);
void copyfile(FILE *infile, FILE *outfile);
int checksig(FILE *infile);

#endif // __PATCH_H__

