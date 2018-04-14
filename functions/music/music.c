/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   music.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuery <sjuery@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 18:28:43 by sjuery            #+#    #+#             */
/*   Updated: 2018/04/13 21:54:34 by sjuery           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void music(char *arg, char *song, int time, int volume)
{
	if(!strcmp(arg, "play"))
		system("afplay BestSong.mp3&");
	if(!strcmp(arg, "stop"))
		system("killall afplay");
}

int main(int argc, char const *argv[]) {
	music(argv[1], "BestSong.mp3", 2, 2);
	return 0;
}
