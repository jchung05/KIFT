/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 23:07:04 by ttran             #+#    #+#             */
/*   Updated: 2018/05/07 23:07:06 by ttran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

int exitsphinx(void)
{
	system("ps aux | grep kift | awk '{print $2}' | xargs kill -9");
	return (0);
}

/*
int main(void)
{
	exitsphinx();
	return (0);
}
*/