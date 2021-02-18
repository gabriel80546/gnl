/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:06:33 by gpassos-          #+#    #+#             */
/*   Updated: 2021/02/18 12:14:22 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int	get_next_line(int fd, char **line)
{
	char *buffer;
	// int size;
	int i;
	int last_read;
	static int line_number = 0;

	// size = BUFFER_SIZE;
	*(line + line_number) = (char *)malloc(sizeof(char) * 350);
	buffer = (char *)malloc(sizeof(char) * 1);
	last_read = read(fd, buffer, 1);
	i = 0;
	*(*(line + line_number) + i) = *buffer;
	i++;
	while (1)
	{
		// printf("*buffer = '%c'(%d)\n", *buffer, (int)*buffer);
		if(last_read == 0)
		{
			*(*(line + line_number) + i - 1) = '\0';
			line_number++;
			return (0);
		}
		else if(*buffer == '\n')
		{
			*(*(line + line_number) + i - 1) = '\0';
			line_number++;
			return (1);
		}
		else
		{
			// printf("merda entrou aqui com *buffer = %d\n", (int)*buffer);
			last_read = read(fd, buffer, 1);
			*(*(line + line_number) + i) = *buffer;
			i++;
		}
	}
	return (-1);
}
