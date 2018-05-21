/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kift.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalpart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 05:02:33 by gmalpart          #+#    #+#             */
/*   Updated: 2018/05/12 07:05:48 by gmalpart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KIFT_H
# define KIFT_H
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <pocketsphinx.h>
# include <sphinxbase/ad.h>
# include <sphinxbase/err.h>
# include <sys/time.h>

typedef struct		s_kift
{
	char			listen;
	char			*holder;
//	int				pos;
}					t_kift;

extern t_kift				*handler;

/*
** parsing.c
*/

void				parse_commands(char *str);
int					compare_values(char const *str, char *key);
int					get_post(char const *str, char *key);
void				decomposing_string(char const *str);

/*
** FUNCTIONS - DIR
** casting everyone but testing only the timer for the demo
*/

// demo
int timer(void);

int	alarm(void);
int brightness(char *brightness_value);
int events(void);
int exitsphinx(void);
void help(void);
void history(void);
void location(void);
void music(char *arg, char *song, int duration);
void search(char *arg);
void send(char *subject, char *content, char *recipient);
int traffic(void);
void weather(char *location); // ask stan what happen


#endif
