/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   location.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuery <sjuery@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 18:28:43 by sjuery            #+#    #+#             */
/*   Updated: 2018/04/13 21:36:35 by sjuery           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void location()
{
	system("sh location.sh > location_history");
}

int main(int argc, char const *argv[]) {
	location();
	return 0;
}
