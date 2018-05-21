/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuery <sjuery@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 18:28:43 by sjuery            #+#    #+#             */
/*   Updated: 2018/04/16 16:55:23 by sjuery           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kift.h"

void search(char *arg)
{
	char cmd[256];

	sprintf(cmd, "say searching for %s", arg);
	system(cmd);
	sprintf(cmd, "sh search.sh %s", arg);
	system(cmd);
}


/*
int main(int argc, char const *argv[]) {
	search(argv[1]);
	return 0;
}

*/