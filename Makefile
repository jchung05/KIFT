# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmalpart <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/26 04:46:42 by gmalpart          #+#    #+#              #
#    Updated: 2018/05/11 07:39:32 by gmalpart         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = kift
NATEST = test
HEADERS = includes/
GCC = gcc
FLAGS = -Wall -Wextra -Werror
LOGFILE = testinglog

DEFCOMPILER =	-DMODELDIR=\"`pkg-config --variable=modeldir pocketsphinx`\" \
				-DPENDEJADA=\"`pwd`\"

EXTRAHEADERS = `pkg-config --cflags --libs pocketsphinx sphinxbase`


# all the necesary files
CFILES = pendejada.c

all: $(NAME)

$(NAME):
	gcc -g -o $(NATEST) -I $(HEADERS) $(CFILES) $(DEFCOMPILER) $(EXTRAHEADERS)

re:
	rm $(NATEST)

# not really creating .o files so cleaning the log
clean:
	rm $(LOGFILE)

fclean: clean
	rm $(NATEST)

.PHONY: all, clean, fclean, re

#gcc -o test pendejada.c \
#    -DMODELDIR=\"`pkg-config --variable=modeldir pocketsphinx`\" \
#    -DPENDEJADA=\"`pwd`\" \
#    `pkg-config --cflags --libs pocketsphinx sphinxbase`
