Initialization of frequency in "wail32.dll", eax type is (maybe) HSAMPLE

	.text:20009DAB                 mov     dword ptr [eax+3Ch], 2B11h

Frequency = 11025 (0x2b11)

There is a switch case for suffix filename :

	.text:00477F94 off_477F94      dd offset loc_477E10, offset loc_477E17, offset loc_477E1E
	.text:00477F94                                         ; DATA XREF: sub_477CC0+149r
	.text:00477F94                 dd offset loc_477E25, offset loc_477E2C, offset loc_477E30 ; jump table for switch statement
	.text:00477F94                 dd offset loc_477E30, offset loc_477E38
	.text:00477FB4 byte_477FB4     db      0,     1,     7,     2 ; DATA XREF: sub_477CC0+143r
	.text:00477FB4                 db      7,     3,     7,     4 ; indirect table for switch statement
	.text:00477FB4                 db      7,     7,     7,     7
	.text:00477FB4                 db      7,     7,     7,     7
	.text:00477FB4                 db      7,     7,     7,     7
	.text:00477FB4                 db      7,     7,     7,     7
	.text:00477FB4                 db      7,     7,     7,     7
	.text:00477FB4                 db      5,     7,     7,     7
	.text:00477FB4                 db      7,     7,     7,     7
	.text:00477FB4                 db      7,     7,     7,     7
	.text:00477FB4                 db      7,     7,     7,     7
	.text:00477FB4                 db      7,     7,     7,     7
	.text:00477FB4                 db      7,     7,     7,     7
	.text:00477FB4                 db      7,     7,     7,     7
	.text:00477FB4                 db      7,     7,     7,     7
	.text:00477FB4                 db      6
	.text:00477FF1                 align 10h

Result for each cases : (these values has been tested only on file "*.82M")

* "m81" :	BytesPerSec = 11025; PCM = 1 ; BytePerBloc = 1; BitsPerSample = 8
* "M81" :	BytesPerSec = 11025; PCM = 1 ; BytePerBloc = 1; BitsPerSample = 8
* "m82" :	BytesPerSec = 22050; PCM = 1 ; BytePerBloc = 2; BitsPerSample = 16
* "M82" :	BytesPerSec = 22050; PCM = 1 ; BytePerBloc = 2; BitsPerSample = 16
* "m84" :	BytesPerSec = 44100; PCM = 1 ; BytePerBloc = 4; BitsPerSample = 24
* "M84" :	BytesPerSec = 44100; PCM = 1 ; BytePerBloc = 4; BitsPerSample = 24
* "m61" :	BytesPerSec = 11025; Form of compression ; ...
* "M61" :	BytesPerSec = 11025; Form of compression ; ...
* "m62" :	BytesPerSec = 22050; Form of compression ; ...
* "M62" :	BytesPerSec = 22050; Form of compression ; ...
* "m64" :	BytesPerSec = 44100; Form of compression ; ...
* "M64" :	BytesPerSec = 44100; Form of compression ; ...

