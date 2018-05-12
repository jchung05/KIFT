/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalpart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 06:46:23 by gmalpart          #+#    #+#             */
/*   Updated: 2018/05/12 06:52:57 by gmalpart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kift.h"

void				parse_commands(char *str)
{
	if (strstr(str, "SET A TIMER"))
		printf("Setting a timer\n");
	else
		printf("Didnt recognize your command\n");
}

int		compare_values(char const *str, char *key)
{
	int	i;
	int	e;

	i = 0;
	e = 0; 
	while (str[i] && key[e] && str[i] == key[e])
	{
		i++;
		e++;
		if (key[e] == '\0')
			return(i);
	}
	return (-1);
}

int					get_post(char const *str, char *key)
{
	int		i;
	int		e;

	i = 0;
	e = 0;
	while(str[i])
	{
		if (str[i] == key[e] && compare_values(str, key) != -1)
				return (compare_values(str, key) + i);
		else
			i++;
	}
	return (0);
}

void				decomposing_string(char const *str)
{
	int		i;
	int		postkey;

	i = 0;
	if (strstr(str, "LARRY"))
	{
		handler->listen = 1;
//		printf("LISTENING = |%d|", (int)handler->listen);
		postkey = get_post(str, "LARRY");
		parse_commands((char*)str + postkey);
		handler->listen = 0;
	}
}
