# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmalpart <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/26 04:46:42 by gmalpart          #+#    #+#              #
#    Updated: 2018/05/21 07:01:32 by gmalpart         ###   ########.fr        #
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

DIRFILES =	timer/timer.c \
			alarm/alarm.c \
			brightness/brightness.c \
			events/events.c \
			exit/exit.c \
			help/help.c \
			history/history.c \
			location/location.c \
			music/music.c \
			search/search.c \
			send/send.c \
			traffic/traffic.c \
			weather/weather.c

DIRCFILES = $(addprefix functions/, $(DIRFILES))

CFILES = pendejada.c \
		 parsing.c

SRCFILES = $(addprefix src/, $(CFILES))

all: $(NAME)

$(NAME):
	gcc -o $(NATEST) -I $(HEADERS) $(SRCFILES) $(DIRCFILES) $(DEFCOMPILER) $(EXTRAHEADERS)

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
