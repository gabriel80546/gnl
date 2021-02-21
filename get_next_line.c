/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:06:33 by gpassos-          #+#    #+#             */
/*   Updated: 2021/02/20 21:49:05 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "libft/libft.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif


// static size_t	safe_strlen(const char *s)
// {
// 	return (s == NULL) ? 0 : ft_strlen(s);
// }

int				get_next_line(int fd, char **line)
{
	char		buffer[BUFFER_SIZE] = {0};
	static int	line_number = 0;
	// int			i;
	char		**saida;
	int			read_saida;
	int			split_w;

	if (line_number == 0)
		ft_memset(buffer, 30, BUFFER_SIZE);

	read_saida = read(fd, buffer, BUFFER_SIZE);

	printf("read_saida = %i\n", read_saida);
	printf("BUFFER_SIZE = %i\n", BUFFER_SIZE);
	if(read_saida == BUFFER_SIZE)
	{
		saida = ft_split(buffer, '\n');
		split_w = 0;
		while (saida[split_w] != NULL)
			split_w++;
		printf("esse read encontrou %d palavras\n", split_w);
	}
	else
	{
		printf("merda\n");
	}
	line = NULL;
	line = line;
	return (1);
}

/*
int	get_next_line_old(int fd, char **line)
{
	char buffer[BUFFER_SIZE];
	// int size;
	int i;
	int j;
	int last_read;
	static int line_number = 0;

	if(BUFFER_SIZE <= 0 && fd <= 0 && line == NULL)
		return (-1);

	i = 0;
	if (line_number != 0)
	{
		printf("segunda chamada\n");
		j = 0;
		while (j < BUFFER_SIZE)
		{
			if (buffer[j] == '\n')
				i++;
			else if (buffer[j] != 0)
			{
				*(*(line + line_number) + i) = buffer[j];
				i++;
			}
			j++;
		}
	}
	else
	{
		memset(buffer, 0, BUFFER_SIZE);
		i = 0;
	}
	printf("aaaaaaaaaaaaaaaaa i = %i\n", i);

	*(line + line_number) = (char *)malloc(sizeof(char) * 10000 + 1);
	*(*(line + line_number) + BUFFER_SIZE) = '\0';
	// i = 0;
	last_read = read(fd, buffer, BUFFER_SIZE);
	printf("2 primeiro read = %d\n", last_read);
	printf("3 mas essa leitura(%d) foi menor que o buffer(%d)? %s\n", last_read, BUFFER_SIZE, (last_read < BUFFER_SIZE) ? "sim" : "nao");
	if(last_read < BUFFER_SIZE)
	{
		printf("4 então encontrou o EOF na leitura\n");
		j = 0;
		while (j < last_read)
		{
			*(*(line + line_number) + j + i) = buffer[j];
			j++;
		}
		line_number++;
		return (0);
	}
	j = 0;
	while (1)
	{
		if(last_read < BUFFER_SIZE)
		{
			printf("5 encontramos um EOF nessa string '%s'(%ld)\n", buffer, strlen(buffer));
			printf("6 agora finaliza i+j = %d\n", i + j);
			j = 0;
			while (j < last_read)
			{
				*(*(line + line_number) + j + i) = buffer[j];
				j++;
			}
			*(*(line + line_number) + j + i) = '\0';
			printf("7 *(linha + %d) = '%s'(%ld)\n", line_number, *(line + line_number), strlen(*(line + line_number)));
			line_number++;
			return (0);
		}
		else if(strchr(buffer, '\n') != NULL)
		{
			printf("8 tem um '\\n' nessa string '%s'(%ld)\n", buffer, strlen(buffer));
			printf("9 agora finaliza i+j = %d\n", i + j);
			// printf("00 *(linha + %d) = '%s'(%ld)\n", line_number, *(line + line_number), strlen(*(line + line_number)));
			// printf("i = %d\n", i);
			j = 0;
			while (buffer[j] != '\n')
			{
				*(*(line + line_number) + j + i) = buffer[j];
				buffer[j] = 0;
				j++;
			}
			*(*(line + line_number) + j + i) = '\0';
			printf("10 *(linha + %d) = '%s'(%ld)\n", line_number, *(line + line_number), strlen(*(line + line_number)));
			line_number++;
			return (1);
		}
		else
		{
			printf("11 nao tem um '\\n' nem o EOF nessa string '%s'(%ld)\n", buffer, strlen(buffer));
			printf("12 estamos no meio i+j = %d\n", i + j);
			j = 0;
			while (j < BUFFER_SIZE)
			{
				*(*(line + line_number) + j + i) = buffer[j];
				j++;
			}
			i += j;
			printf("13 *(linha + %d) = '%s'(%ld)\n", line_number, *(line + line_number), strlen(*(line + line_number)));
			last_read = read(fd, buffer, BUFFER_SIZE);
		}
	}
	return (-1);
}
*/
