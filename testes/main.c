/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:25:10 by gabriel           #+#    #+#             */
/*   Updated: 2021/02/21 07:58:58 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif

int	main(void)
{
	int fd;
	char **linhas;
	int i;

	linhas = (char **)malloc(sizeof(char *) * 50);
	fd = open("oloco.txt", O_RDONLY);
	// while (get_next_line(fd, linhas) != 0)
	// {
	// 	printf("linha[%i] = '%s'(%ld)\n", i, linhas[i], strlen(linhas[i]));
	// 	i++;
	// }
	i = 0;
	get_next_line(fd, linhas);
	printf("linha[%i] = '%s'(%ld)\n", i, linhas[i], strlen(linhas[i]));
	i++;
	get_next_line(fd, linhas);
	printf("linha[%i] = '%s'(%ld)\n", i, linhas[i], strlen(linhas[i]));
	return (0);
}
