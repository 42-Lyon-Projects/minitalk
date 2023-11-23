# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/17 17:54:42 by jbadaire          #+#    #+#              #
#    Updated: 2023/01/17 17:54:46 by jbadaire         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

CLIENT = client
SERVER = server

COMMONS_FILES = ./sources/sig_queue.c

CLIENT_FILES = ./sources/client.c $(COMMONS_FILES)
CLIENT_OBJS = $(addprefix $(OBJ_DIRECTORY), $(CLIENT_FILES:.c=.o))

SERVER_FILES = ./sources/server.c $(COMMONS_FILES)
SERVER_OBJS = $(addprefix $(OBJ_DIRECTORY), $(SERVER_FILES:.c=.o))

LIBFT = ./dependencies/libft/libft.a
MAKE_LIBFT = make -C ./dependencies/libft
LIBFT_FLAGS = -L./dependencies/libft -l:libft.a

CC = cc
FLAGS = -Wall -Wextra -Werror -g3

OBJ_DIRECTORY = ./build/.obj
DEPENDENCIES = ./includes/minitalk.h Makefile

all: server client

server: $(DEPENDENCIES) $(LIBFT)
	$(CC) $(FLAGS) $(SERVER_FILES) $(LIBFT_FLAGS) -o ./build/$(SERVER)

client: $(DEPENDENCIES) $(LIBFT)
	$(CC) $(FLAGS) $(CLIENT_FILES) $(LIBFT_FLAGS) -o ./build/$(CLIENT)

clean:
	rm -rf build

re : clean all

force :

$(LIBFT): force
	mkdir -p build
	$(MAKE_LIBFT)

.PHONY: all clean fclean re force