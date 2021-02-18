/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:25:10 by gabriel           #+#    #+#             */
/*   Updated: 2021/02/18 11:43:45 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int	main(void)
{
	int fd;
	char **linhas;
	int i;

	linhas = (char **)malloc(sizeof(char *) * 50);
	fd = open("oloco.txt", O_RDONLY);
	i = 0;
	while (get_next_line(fd, linhas) != 0)
	{
		printf("*(linhas + %i) = '%s'(%ld)\n", i, *(linhas + i), strlen(*(linhas + i)));
		i++;
	}
	printf("*(linhas + %i) = '%s'(%ld)\n", i, *(linhas + i), strlen(*(linhas + i)));
	return (0);
}
