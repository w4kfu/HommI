#include "sound.h"
#include <stdio.h>
#include <stdlib.h>

int getFileSize(FILE *inFile)
{
        int fileSize = 0;

        fseek(inFile ,0, SEEK_END);
        fileSize = ftell(inFile);
        fseek(inFile, 0, SEEK_SET);
        return fileSize;
}

int main(int argc, char *argv[])
{
        FILE *fin = NULL;
        unsigned int filesize = 0;
        unsigned char *buf = NULL;

        if (argc != 3)
        {
                fprintf(stderr, "%s <*.82M> <outfile>\n", argv[0]);
                return EXIT_FAILURE;
        }
        if (!(fin = fopen(argv[1], "rb")))
        {
                perror("fopen()");
                return EXIT_FAILURE;
        }
        filesize = getFileSize(fin);
        if (!(buf = malloc(sizeof (char) * filesize)))
        {
                perror("malloc()");
                fclose(fin);
                return EXIT_FAILURE;
        }
        fread(buf, filesize, 1, fin);
        save_wav(argv[2], buf, filesize);
        fclose(fin);
        return 0;
}

