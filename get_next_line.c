/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:06:33 by gpassos-          #+#    #+#             */
/*   Updated: 2021/02/17 14:52:27 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int	get_next_line(int fd, char **line)
{
	char *buffer;

	buffer = (char *)malloc(sizeof(char) * 2);
	printf("fd = %d\n", fd);
	read(fd, buffer, 1);
	printf("%c", *(buffer + 0));
	while (*(buffer + 0) != '\n' && *(buffer + 0) != '\0')
	{
		read(fd, buffer, 1);
		// printf("*(buffer + 0) = '%c'\n", *(buffer + 0));
		printf("%c", *(buffer + 0));
	}
	return (0);
}
