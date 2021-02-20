/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:06:33 by gpassos-          #+#    #+#             */
/*   Updated: 2021/02/20 10:57:31 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <string.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif

int	get_next_line(int fd, char **line)
{
	char buffer[BUFFER_SIZE];
	// int size;
	int i;
	int j;
	int last_read;
	static int line_number = 0;

	if(BUFFER_SIZE <= 0 && fd <= 0 && line == NULL)
		return (-1);

	printf("BUFFER_SIZE = %d\n", BUFFER_SIZE);
	*(line + line_number) = (char *)malloc(sizeof(char) * 10000 + 1);
	*(*(line + line_number) + BUFFER_SIZE) = '\0';
	i = 0;
	last_read = read(fd, buffer, BUFFER_SIZE);
	printf("primeiro read = %d\n", last_read);
	printf("mas essa leitura(%d) foi menor que o buffer(%d)? %s\n", last_read, BUFFER_SIZE, (last_read < BUFFER_SIZE) ? "sim" : "nao");
	if(last_read < BUFFER_SIZE)
	{
		printf("então encontrou o EOF na leitura\n");
		j = 0;
		while (j < last_read)
		{
			*(*(line + line_number) + j + (i * BUFFER_SIZE)) = buffer[j + (i * BUFFER_SIZE)];
			j++;
		}
		line_number++;
		return (0);
	}
	// else
	// {
	// 	printf("então não encontrou o EOF na leitura\n");
	// 	last_read = read(fd, buffer, BUFFER_SIZE);
	// 	printf("o read colocou '%s'(%ld) no buffer\n", buffer, strlen(buffer));
	// 	j = 0;
	// 	while (j < BUFFER_SIZE)
	// 	{
	// 		*(*(line + line_number) + j + (i * BUFFER_SIZE)) = buffer[j + (i * BUFFER_SIZE)];
	// 		j++;
	// 	}
	// }
	printf("então não encontrou o EOF na leitura\n");
	printf("ENTRA NO WHILE ENTRA NO WHILE ENTRA NO WHILE ENTRA NO WHILE ENTRA NO WHILE\n");
	while (1)
	{
		if(last_read < BUFFER_SIZE)
		{
			printf("encontramos um EOF nessa string '%s'(%ld)\n", buffer, strlen(buffer));
			printf("agora finaliza i+j = %d\n", i + j);
			j = 0;
			while (j < last_read)
			{
				*(*(line + line_number) + j + i) = buffer[j + i];
				j++;
			}
			*(*(line + line_number) + j + i) = '\0';
			printf("*(linha + %d) = '%s'(%ld)\n", line_number, *(line + line_number), strlen(*(line + line_number)));
			line_number++;
			return (0);
		}
		else if(strchr(buffer, '\n') != NULL)
		{
			printf("tem um '\\n' nessa string '%s'(%ld)\n", buffer, strlen(buffer));
			printf("agora finaliza i+j = %d\n", i + j);
			j = 0;
			while (j < BUFFER_SIZE)
			{
				*(*(line + line_number) + j + i) = buffer[j + i];
				j++;
			}
			*(*(line + line_number) + j + i) = '\0';
			printf("*(linha + %d) = '%s'(%ld)\n", line_number, *(line + line_number), strlen(*(line + line_number)));
			line_number++;
			return (1);
		}
		else
		{
			printf("nao tem um '\\n' nem o EOF nessa string '%s'(%ld)\n", buffer, strlen(buffer));
			printf("estamos no meio i+j = %d\n", i + j);
			j = 0;
			while (j < BUFFER_SIZE)
			{
				*(*(line + line_number) + j + i) = buffer[j + i];
				j++;
			}
			i += j;
			printf("*(linha + %d) = '%s'(%ld)\n", line_number, *(line + line_number), strlen(*(line + line_number)));
			last_read = read(fd, buffer, BUFFER_SIZE);
		}
	}
	return (-1);
}
