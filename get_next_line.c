/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:06:33 by gpassos-          #+#    #+#             */
/*   Updated: 2021/02/18 10:10:32 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int	get_next_line(int fd, char **line)
{
	char *buffer;
	char **nada;
	int size;
	int i;

	size = BUFFER_SIZE;
	nada = line;
	line = nada;
	buffer = (char *)malloc(sizeof(char) * size);
	printf("fd = %d\n", fd);
	read(fd, buffer, 1);
	printf("%c", *(buffer + 0));
	while (*(buffer + 0) != '\n' && *(buffer + 0) != '\0')
	{
		read(fd, buffer, 1);
		printf("%c", *(buffer + 0));
	}
	printf("%d\n", size);
	return (0);
}
