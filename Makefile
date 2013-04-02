CC              = gcc
NASM		= nasm
RM              = rm -f
CFLAGS          = -W -Wall -Wextra -ansi -pedantic -D_BSD_SOURCE -std=c99 -ggdb

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

BIN_DIR		= bin

all: $(PATCH_NAME) $(SOUND_NAME) $(AGG_NAME)

$(PATCH_NAME): $(BIN_DIR) $(PATCH_OBJ)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$(PATCH_NAME) $(PATCH_OBJ)

$(SOUND_NAME): $(BIN_DIR) $(SOUND_OBJ)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$(SOUND_NAME) $(SOUND_OBJ)

$(AGG_NAME): $(BIN_DIR) $(AGG_OBJ)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$(AGG_NAME) $(AGG_OBJ)

$(BIN_DIR):
	mkdir $(BIN_DIR)

clean:
	$(RM) $(SOUND_OBJ)
	$(RM) $(PATCH_OBJ)
	$(RM) $(AGG_OBJ)

distclean:  clean
	$(RM) -r $(BIN_DIR)


.PHONY:  clean all distclean
