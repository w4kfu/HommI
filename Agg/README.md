# AGG File Format Spec

	|   Header   |
	| Files Data |
	| Files list |

## Header

	+0x00 : Number Of Files
	+0x02 : Files Information

## Files Information

	+0x00 : Hash (Hash function can be found in agg.c)
	+0x02 : File Offset (from start)
	+0x06 : FileSize
	+0x0A : FileSize (again ?)

## Files list

After all files data, there is a list of all filenames, each filename is an array of 15 bytes.

# Types of files contained

## 82m ; 82M

Sound, music files can be handled by this [program][1].

## atk

## bin

## BIN

## BMP ; bkg ; bmp

Image files, 8bit per pixel, it's indexed image color, palette can be found in *.pal, thoses files can be handles by this [program][3].

## fnt

Maybe font file format

### bigfont.fnt

	00000000  10 00 0c 00 66 6f 6e 74  2e 69 63 6e 00 00 00 00  |....font.icn....|
	00000010  00                                                |.|
	00000011

### smalfont.fnt

	00000000  0c 00 09 00 73 6d 61 6c  66 6f 6e 74 2e 69 63 6e  |....smalfont.icn|
	00000010  00                                                |.|
	00000011

### File structure

	+0x00 : Width ?
	+0x02 : Height ?
	+0x04 : Filename[13]

## icn

## ICN

## mse

## obj

## pal

Palette files can be handled by this [program][2].

## std

## til

## TIL

## tod

## wip

## wlk

## xtl


[1]:https://github.com/w4kfu/HommI/tree/master/Sound
[2]:https://github.com/w4kfu/HommI/tree/master/Pal
[3]:https://github.com/w4kfu/HommI/tree/master/Bmp
