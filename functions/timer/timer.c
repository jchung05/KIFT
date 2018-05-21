/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 23:44:55 by ttran             #+#    #+#             */
/*   Updated: 2018/04/17 20:49:48 by ttran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kift.h"

/*
int	is_number(char *nbr)
{
	while (*nbr)
	{
		if (!(*nbr >= '0' && *nbr <= '9'))
			return (0);
		nbr++;
	}
	return (1);
}
*/

/*
** Person says "set timer"
** This function is called
** Function asks for user input! 
** GERARDO/COMMENT = have to specify the path of the script
*/

int timer(void)
{
//	system("sh timer.script");
	system("sh functions/timer/timer.script");
	return (0);
}
