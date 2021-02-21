/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:06:33 by gpassos-          #+#    #+#             */
/*   Updated: 2021/02/21 16:06:09 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft/libft.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif

// int printf (const char * fmt, ...)
// {
// 	if (fmt[0] == 7)
// 		return (1);
// 	else
// 		return (0);
// }



static size_t	safe_strlen(const char *s)
{
	return (s == NULL) ? 0 : ft_strlen(s);
}

int				get_next_line(int fd, char **line)
{
	static char	buffer[BUFFER_SIZE + 1] = {0};
	static int	line_number = 0;
	static int	last_offset = 0;
	char		buftemporario[BUFFER_SIZE + 1];
	int			i;
	int			j;
	int			vazio;
	int			tinha;
	// char		**saida;
	int			read_saida;
	// int			split_w;

	int debug = 0;
	debug = 1;
	debug = 0;

	vazio = 0;
	tinha = 0;

	if(BUFFER_SIZE <= 0 || fd <= 0 || line == NULL)
		return (-1);


	*(line + line_number) = (char *)malloc(sizeof(char) * 10000);


	if(debug == 1) { printf("bora porra, pega a linha %i\n", line_number); }
	if (line_number == 0)
		ft_memset(buffer, vazio, BUFFER_SIZE + 1);
	if(debug == 1) { printf("last_offset = %i\n", last_offset); }

	

	i = 0;
	while (i < BUFFER_SIZE)
	{
		if (buffer[i] != vazio)
		{
			if(debug == 1) { printf("buffer[%i] tem lixo = %i  \t'%c'\n", i, buffer[i], buffer[i]); }
			tinha = 1;
		}
		else
		{
			if(debug == 1) { printf("buffer[%i] = %i\t'%c'\n", i, buffer[i], buffer[i]); }
		}
		i++;
	}

	i = 0;
	j = 0;
	while (1)
	{
		if(debug == 1) { printf("i já está = %i\n", i); }
		if(debug == 1) { printf("tinha algo no buffer? %s\n", (tinha) ? "sim" : "nao"); }
		if (tinha == 0)
		{
			if(debug == 1) { printf("entao vou usar o read\n"); }
			read_saida = read(fd, buffer, BUFFER_SIZE);
			buffer[BUFFER_SIZE] = '\0';
		}
		else
		{
			if(debug == 1) { printf("entao não vou usar o read\n"); }
			read_saida = BUFFER_SIZE + 1;
		}
		tinha = 0;

		if(debug == 1) { printf("read nem leu nada? %s\n", (read_saida == 0) ? "sim" : "nao"); }
		if (read_saida == 0)
		{
			if(debug == 1) { printf("então ja acabou\n"); }
			line_number++;
			return (0);
		}

		if(debug == 1) { printf("read leu tudo? %s\n", (read_saida == BUFFER_SIZE) ? "sim" : "nao"); }
		if (read_saida == BUFFER_SIZE)
		{
			if(debug == 1) { printf("então EOF está longe\n"); }

			if(debug == 1) { printf("tem '\\n' nesse buffer? %s\n", (ft_strchr(buffer, '\n') != NULL) ? "sim" : "nao"); }
			if (ft_strchr(buffer, '\n') != NULL)
			{
				if(debug == 1) { printf("tem quebra de linha nessa porra\n"); }
				if(debug == 1) { printf("buffer = '%s'(%ld)\n", buffer, safe_strlen(buffer)); }
				if(debug == 1) { printf("vou ter que escrever só parte\n"); }
				j = 0;
				while (j < BUFFER_SIZE)
				{
					if (buffer[j] == '\n')
						break ;
					*(*(line + line_number) + j + i) = buffer[j];
					buffer[j] = 0;
					j++;
				}
				if (last_offset == 0 && 0)
					last_offset = 0;
				last_offset = j + 1;
				if(debug == 1) { printf("last offset é %i\n", j); }
				if(debug == 1) { printf("last offset é %i\n", last_offset); }
				if(debug == 1) { printf("buffer[last_offset] = %i\n", buffer[last_offset]); }
				if(debug == 1) { printf("buffer[last_offset] = '%c'\n", buffer[last_offset]); }
				*(*(line + line_number) + j + i) = '\0';
				buffer[j] = 0;
				line_number++;
				return (0);
			}
			else
			{
				if(debug == 1) { printf("não tem quebra de linha nessa disgraça\n"); }
				if(debug == 1) { printf("buffer = '%s'(%ld)\n", buffer, safe_strlen(buffer)); }
				j = 0;
				while (j < BUFFER_SIZE)
				{
					*(*(line + line_number) + j + i) = buffer[j];
					buffer[j] = 0;
					j++;
				}
				i += j;
			}
		}
		else if (read_saida == (BUFFER_SIZE + 1))
		{
			if(debug == 1) { printf("na verdade nem teve read. já tinha coisa nesse buffer\n"); }



			ft_memcpy(buftemporario, buffer, BUFFER_SIZE + 1);
			j = 0;
			while (j < BUFFER_SIZE)
			{
				if (buffer[j] == 0)
					buftemporario[j] = ' ';
				else
					buftemporario[j] = buffer[j];
				j++;
			}
			buftemporario[j] = '\0';
			if(debug == 1) { printf("buftemporario = '%s'(%ld)\n", buftemporario, safe_strlen(buftemporario)); }

			if(debug == 1) { printf("tem '\\n' nesse buffer? %s\n", (ft_strchr(buftemporario, '\n') != NULL) ? "sim" : "nao"); }

			if (ft_strchr(buftemporario, '\n') != NULL)
			{
				if(debug == 1) { printf("tem um '\\n' nesse buffer\n"); }
				if(debug == 1) { printf("TODO: e agora ????????????\n"); }


				j = last_offset;
				while (1)
				{
					if(debug == 1) { printf("deu merda buscando '\\n' kkkkkk %i\n", j); }
					if (buffer[j] == '\n')
						break ;
					*(*(line + line_number) + (j - last_offset)) = buffer[j];
					buffer[j] = 0;
					j++;
				}
				*(*(line + line_number) + (j - last_offset)) = '\0';
				buffer[j] = '\0';
				last_offset = j + 1;
				line_number++;
				return (0);
			}
			else
			{
				if(debug == 1) { printf("não tem um '\\n' nesse buffer\n"); }
				if(debug == 1) { printf("entao vou colocar esse finalzinho no inicio da linha\n"); }
				j = last_offset;
				while (j < BUFFER_SIZE)
				{
					*(*(line + line_number) + (j - last_offset)) = buffer[j];
					buffer[j] = 0;
					j++;
				}
				if(debug == 1) { printf("i = %i, j = %i, last_offset = %i\n", i, j, last_offset); }
				i += j - last_offset;
			}
		}
		else
		{
			if(debug == 1) { printf("então EOF está proximo\n"); }
			if(debug == 1) { printf("read só leu %i\n", read_saida); }
			if(debug == 1) { printf("buffer = '%s'(%ld)\n", buffer, safe_strlen(buffer)); }

			if(debug == 1) { printf("tem '\\n' nesse buffer? %s\n", (ft_strchr(buffer, '\n') != NULL) ? "sim" : "nao"); }
			if (ft_strchr(buffer, '\n') != NULL)
			{
				if(debug == 1) { printf("TODO: estamos proximo do EOF, e ainda tem '\\n' nesse caraio\n"); }
			}
			else
			{
				if(debug == 1) { printf("ufa estamos proximo do EOF, e não tem '\\n' nessa merda\n"); }
				if(debug == 1) { printf("é só colocar tudo no *(line + line_number) e ja era\n"); }
				if(debug == 1) { printf("j = %i, i = %i, read_saida = %i\n", j, i, read_saida); }
				j = 0;
				while (j < read_saida)
				{
					*(*(line + line_number) + j + i) = buffer[j];
					buffer[j] = 0;
					j++;
				}
				*(*(line + line_number) + j + i) = '\0';
				line_number++;
				return (0);
			}
			break ;
		}
		// i++;
		// break ;
	}
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

	if(BUFFER_SIZE <= 0 || fd <= 0 || line == NULL)
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
