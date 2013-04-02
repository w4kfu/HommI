#include "sound.h"

struct wav_header *Make_wav_header(unsigned int length_data)
{
	struct wav_header *new_header = NULL;

	if (!(new_header = malloc(sizeof (struct wav_header))))
	{
		perror("malloc()");
		return NULL;
	}
	memcpy(new_header->FileTypeBlocID, "RIFF", 4);
	new_header->FileSize = length_data + sizeof (struct wav_header) - 8;
	memcpy(new_header->FileFormatID, "WAVE", 4);
	memcpy(new_header->FormatBlocID, "fmt ", 4);
	new_header->BlocSize = 0x10;
	new_header->AudioFormat = 0x01;
	new_header->NumOfChan = 0x01;
	new_header->Frequency = 11025;

	new_header->BitsPerSample = 16;
	new_header->BytePerBloc = new_header->NumOfChan * new_header->BitsPerSample / 8;
	new_header->BytePerSec = new_header->Frequency * new_header->BytePerBloc;

	memcpy(new_header->DataBlocID, "data", 4);
	new_header->DataSize = length_data;
	return new_header;
}

int save_wav(char *filename, unsigned char *buf, unsigned int length_buf)
{
	struct wav_header *wheader = NULL;
	FILE *fout = NULL;

	if (!(wheader = Make_wav_header(length_buf)))
		return 0;
	if (!(fout = fopen(filename, "wb")))
	{
		perror("fopen()");
		return 0;
	}
	fwrite(wheader, sizeof (struct wav_header), 1, fout);
	fwrite(buf, length_buf, 1, fout);
	fclose(fout);
	return 1;
}
