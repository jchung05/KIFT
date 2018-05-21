# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmalpart <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/26 04:46:42 by gmalpart          #+#    #+#              #
#    Updated: 2018/05/12 08:09:52 by gmalpart         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = kift
NATEST = test
HEADERS = includes/
GCC = gcc
FLAGS = -Wall -Wextra -Werror
LOGFILE = testinglog

#DEFCOMPILER =	-DMODELDIR=\"`pkg-config --variable=modeldir pocketsphinx`\" \
#				-DPENDEJADA=\"`pwd`\"

DEFCOMPILER =	-DMODELDIR=\"`pkg-config --variable=modeldir pocketsphinx`\" \
				-DDICTIONARY=\"`pwd`\"

EXTRAHEADERS = `pkg-config --cflags --libs pocketsphinx sphinxbase`


# all the necesary files

CFILES = pendejada.c \
		 parsing.c

SRCFILES = $(addprefix src/, $(CFILES))

all: $(NAME)

$(NAME):
	gcc -o $(NATEST) -I $(HEADERS) $(SRCFILES) $(DEFCOMPILER) $(EXTRAHEADERS)

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
