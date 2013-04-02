#include "patch.h"
#include <stdlib.h>

int main(int argc, char *argv[])
{
        char *s = NULL;
        FILE *infile;
        FILE *patchfile;
        FILE *outfile;

        if (argc != 4)
        {
                fprintf(stderr, "%s <HEROES.EXE> <PATCH.BIN> <OUTPUT.EXE>\n", argv[0]);
                return EXIT_FAILURE;
        }
        if ((s = argv[1], (infile  = fopen(s, "rb")) == NULL)
         || (s = argv[2], (patchfile = fopen(s, "rb")) == NULL)
         || (s = argv[3], (outfile = fopen(s, "wb")) == NULL))
        {
                perror("fopen()");
                return EXIT_FAILURE;
        }
        if (checksig(infile))
        {
                copyfile(infile, outfile);
                patch(patchfile, outfile);
        }
        fclose(infile);
        fclose(patchfile);
        fclose(outfile);
        return EXIT_SUCCESS;
}
