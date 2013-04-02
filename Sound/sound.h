#ifndef __SOUND_H__
#define __SOUND_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct wav_header
{
    char FileTypeBlocID[4];
    unsigned int FileSize;
    char FileFormatID[4];
    char FormatBlocID[4];
    unsigned int BlocSize;
    unsigned short AudioFormat;
    unsigned short NumOfChan;
    unsigned int Frequency;
    unsigned int BytePerSec;
    unsigned short BytePerBloc;
    unsigned short BitsPerSample;
    char DataBlocID[4];
    unsigned int DataSize;
}__attribute__((packed));

struct wav_header *Make_wav_header(unsigned int length_data);
int save_wav(char *filename, unsigned char *buf, unsigned int length_buf);

#endif // __SOUND_H__
