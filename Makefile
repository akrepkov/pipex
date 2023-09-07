UNAME := $(shell uname)

CFLAGS = -Wall -Werror -Wextra
CC = gcc
NAME = pipex
SRC = pipex.c
HEADER = pipex.h

OBJ = pipex.o

LFT_NAME = libft.a
LFT_DIR = libft
LFT = $(LFT_DIR)/$(LFT_NAME)
CFLAGS += -I $(LFT_DIR)
LDFLAGS = -L $(LFT_DIR)
LDLIBS = -lft

all: $(NAME)

$(NAME): $(LFT) $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)
$(LFT):
	make all -sC $(LFT_DIR)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -sC $(LFT_DIR)
	rm -rf $(LFT)
	rm -rf $(OBJ)

fclean: clean
	make fclean -sC $(LFT_DIR)
	rm -rf $(NAME)

re: fclean all

.PHONY: fclean clean re all debug

ifeq ($(UNAME), Linux)
debug:	CFLAGS += -pedantic -fsanitize=address -fsanitize=leak -g3
debug: $(NAME)
endif
ifeq ($(UNAME), Darwin)
debug:	CFLAGS += -pedantic -fsanitize=address -g3
debug: $(NAME)
endif
