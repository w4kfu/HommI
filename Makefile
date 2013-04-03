CC              = gcc
NASM		= nasm
RM              = rm -f
CFLAGS          = -W -Wall -Wextra -ansi -pedantic -D_BSD_SOURCE -std=c99 -ggdb
LFLAGS		= -lpng

PATCH_DIR       = Patch
PATCH_SRC       = 	$(PATCH_DIR)/patch.c	\
                        $(PATCH_DIR)/main.c
PATCH_NAME	= patch
PATCH_OBJ	= $(PATCH_SRC:.c=.o)

SOUND_DIR	= Sound
SOUND_SRC	=	$(SOUND_DIR)/sound.c	\
			$(SOUND_DIR)/main.c
SOUND_NAME	= sound
SOUND_OBJ	= $(SOUND_SRC:.c=.o)

AGG_DIR		= Agg
AGG_SRC		=	$(AGG_DIR)/agg.c	\
			$(AGG_DIR)/main.c
AGG_NAME	= agg
AGG_OBJ		= $(AGG_SRC:.c=.o)

PAL_DIR		= Pal
PAL_SRC		=	$(PAL_DIR)/main.c	\
			$(PAL_DIR)/pal.c
PAL_NAME	= pal
PAL_OBJ		= $(PAL_SRC:.c=.o)

BMP_DIR		= Bmp
BMP_SRC		=	$(BMP_DIR)/main.c	\
			$(BMP_DIR)/bmp.c	\
			$(PAL_DIR)/pal.c
BMP_NAME	= bmp
BMP_OBJ		= $(BMP_SRC:.c=.o)

ICN_DIR		= Icn
ICN_SRC		=	$(ICN_DIR)/main.c	\
			$(ICN_DIR)/icn.c	\
			$(PAL_DIR)/pal.c

ICN_NAME	= icn
ICN_OBJ		= $(ICN_SRC:.c=.o)

BIN_DIR		= bin

all: $(PATCH_NAME) $(SOUND_NAME) $(AGG_NAME) $(PAL_NAME) $(BMP_NAME) $(ICN_NAME)

$(PATCH_NAME): $(BIN_DIR) $(PATCH_OBJ)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$(PATCH_NAME) $(PATCH_OBJ)

$(SOUND_NAME): $(BIN_DIR) $(SOUND_OBJ)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$(SOUND_NAME) $(SOUND_OBJ)

$(AGG_NAME): $(BIN_DIR) $(AGG_OBJ)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$(AGG_NAME) $(AGG_OBJ)

$(PAL_NAME): $(BIN_DIR) $(PAL_OBJ)
	$(CC) $(CFLAGS) $(LFLAGS) -o $(BIN_DIR)/$(PAL_NAME) $(PAL_OBJ)

$(BMP_NAME): $(BIN_DIR) $(BMP_OBJ)
	$(CC) $(CFLAGS) $(LFLAGS) -o $(BIN_DIR)/$(BMP_NAME) $(BMP_OBJ)

$(ICN_NAME): $(BIN_DIR) $(ICN_OBJ)
	$(CC) $(CFLAGS) $(LFLAGS) -o $(BIN_DIR)/$(ICN_NAME) $(ICN_OBJ)

$(BIN_DIR):
	mkdir $(BIN_DIR)

clean:
	$(RM) $(SOUND_OBJ)
	$(RM) $(PATCH_OBJ)
	$(RM) $(AGG_OBJ)
	$(RM) $(PAL_OBJ)
	$(RM) $(BMP_OBJ)
	$(RM) $(ICN_OBJ)

distclean:  clean
	$(RM) -r $(BIN_DIR)


.PHONY:  clean all distclean
