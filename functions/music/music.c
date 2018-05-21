/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   music.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuery <sjuery@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 18:28:43 by sjuery            #+#    #+#             */
/*   Updated: 2018/04/16 17:43:50 by sjuery           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kift.h"

void music(char *arg, char *song, int duration)
{
	FILE *file;
	char cmd[256];

    if (!(file = fopen(song, "r")))
    {
        fclose(file);
        sprintf(cmd, "say sorry, but this song does not exist.");
    }
	else if(!strcmp(arg, "stop"))
		sprintf(cmd, "killall afplay");
	else if(!strcmp(arg, "play") && duration <= 0)
		sprintf(cmd, "afplay %s", song);
	else if(!strcmp(arg, "play") && duration >= 0)
		sprintf(cmd, "afplay -t %d %s", duration, song);
	system(cmd);
}
