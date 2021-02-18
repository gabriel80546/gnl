/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:25:10 by gabriel           #+#    #+#             */
/*   Updated: 2021/02/18 10:11:00 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line.h"
#include <fcntl.h>

int	main(void)
{
	int fd;
	char **linhas;

	linhas = (char **)malloc(sizeof(char *) * 50);
	fd = open("oloco.txt", O_RDONLY);
	get_next_line(fd, linhas);
	return (0);
}
