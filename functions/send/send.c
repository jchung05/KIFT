/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuery <sjuery@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 18:28:43 by sjuery            #+#    #+#             */
/*   Updated: 2018/04/16 17:43:41 by sjuery           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void send(char *subject, char *content, char *recipient)
{
	char cmd[256];

	if(!content || !recipient || !subject)
	{
		if(!content)
			content = "empty";
		if(!recipient)
			recipient = "empty";
		if(!subject)
			subject = "empty";
		sprintf(cmd, "say your subject is %s, your content is %s, and your"
						" receipent is %s. Make sure none of them are empty",
						subject, content, recipient);
	}
	else
	{
		sprintf(cmd, "echo %s | mail -s %s %s", content, subject, recipient);
		system("say mail sent!");
	}
	system(cmd);
}
