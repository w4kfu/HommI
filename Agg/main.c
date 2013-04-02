#include <stdio.h>
#include <stdlib.h>
#include "agg.h"

int main(int argc, char *argv[])
{
	struct aggfile *agg = NULL;

	if (argc != 2)
	{
		fprintf(stderr, "%s <*.AGG>\n", argv[0]);
		return EXIT_FAILURE;
	}
	if (!(agg = OpenAGG(argv[1])))
		return EXIT_FAILURE;
	fillentry(agg);
	InfoAGG(agg);
	extractall(agg, "./extract/");
	CloseAGG(agg);
	return 0;
}
