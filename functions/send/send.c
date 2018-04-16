/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuery <sjuery@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 18:28:43 by sjuery            #+#    #+#             */
/*   Updated: 2018/04/14 14:04:57 by sjuery           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void send(char *arg, char *content, char *user)
{
	char cmd[9999];

	if(!strcmp(arg, "mail") && content && user)
	{
		sprintf(cmd, "echo %s | mail -s Kift %s", content, user);
		system(cmd);
		system("say mail sent");
	}
	else if(!strcmp(arg, "sms"))
		system("say no sms credit please top up!");
	else
		system("say did you forget some content?");
}

int main(int argc, char const *argv[]) {
	send(argv[1], argv[2], argv[3]);
	return 0;
}
