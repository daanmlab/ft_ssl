NAME = ft_ssl

CC = cc
CFLAGS = -Wall -Wextra -Werror -I./include

SRC_DIR = src
MD5_DIR = $(SRC_DIR)/md5
SHA256_DIR = $(SRC_DIR)/sha256
UTILS_DIR = $(SRC_DIR)/utils

SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/hash_common.c \
       $(SRC_DIR)/hash_process.c \
       $(MD5_DIR)/md5.c \
       $(MD5_DIR)/md5_process.c \
       $(SHA256_DIR)/sha256.c \
       $(SHA256_DIR)/sha256_process.c \
       $(UTILS_DIR)/string_utils.c \
       $(UTILS_DIR)/output_utils.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re