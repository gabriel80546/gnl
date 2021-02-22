/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:06:33 by gpassos-          #+#    #+#             */
/*   Updated: 2021/02/22 08:26:58 by gabriel          ###   ########.fr       */
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
	{
		if(debug == 1) { printf("60: BUFFER_SIZE = %i, fd = %i, line = %p\n", BUFFER_SIZE, fd, line); }
		if(debug == 1) { printf("61: retorno -1\n"); }
		return (-1);
	}

	*(line + line_number) = (char *)malloc(sizeof(char) * 10000);

	if(debug == 1) { printf("67: bora porra, pega a linha %i\n", line_number); }
	if (line_number == 0)
		ft_memset(buffer, vazio, BUFFER_SIZE + 1);
	if(debug == 1) { printf("70: last_offset = %i\n", last_offset); }

	i = 0;
	while (i < BUFFER_SIZE)
	{
		if (buffer[i] != vazio)
		{
			if(debug == 1) { printf("77: buffer[%i] tem lixo = %i  \t'%c'\n", i, buffer[i], buffer[i]); }
			tinha = 1;
		}
		else
		{
			if(debug == 1) { printf("82: buffer[%i] = %i\t'%c'\n", i, buffer[i], buffer[i]); }
		}
		i++;
	}

	i = 0;
	j = 0;
	while (1)
	{
		if(debug == 1) { printf("91: i já está = %i\n", i); }
		if(debug == 1) { printf("92: tinha algo no buffer? %s\n", (tinha) ? "sim" : "nao"); }
		if (tinha == 0)
		{
			if(debug == 1) { printf("95: entao vou usar o read\n"); }
			read_saida = read(fd, buffer, BUFFER_SIZE);
			buffer[BUFFER_SIZE] = '\0';
		}
		else
		{
			if(debug == 1) { printf("101: entao não vou usar o read\n"); }
			read_saida = BUFFER_SIZE + 1;
		}
		tinha = 0;

		if(debug == 1) { printf("106: read nem leu nada? %s\n", (read_saida == 0) ? "sim" : "nao"); }
		if (read_saida == 0)
		{
			if(debug == 1) { printf("109: então ja acabou\n"); }
			j = 0;
			while (j < BUFFER_SIZE)
			{
				if(debug == 1) { printf("113: buffer[%i] = '%c' =\t%d\n", j, buffer[j], buffer[j]); }
				j++;
			}
			*(*(line + line_number) + i + j) = '\0';
			if(debug == 1) { printf("117: *(line + line_number) = '%s'(%ld)\n", *(line + line_number), safe_strlen(*(line + line_number))); }
			if(debug == 1) { printf("118: i = %i; j = %i; i + j = %i\n", i, j, i + j); }
			line_number++;
			if(debug == 1) { printf("120: retorno 0\n"); }
			return (0);
		}

		if(debug == 1) { printf("124: read leu tudo? %s\n", (read_saida == BUFFER_SIZE) ? "sim" : "nao"); }
		if (read_saida == BUFFER_SIZE)
		{
			if(debug == 1) { printf("127: então EOF está longe\n"); }

			if(debug == 1) { printf("129: tem '\\n' nesse buffer? %s\n", (ft_strchr(buffer, '\n') != NULL) ? "sim" : "nao"); }
			if (ft_strchr(buffer, '\n') != NULL)
			{
				if(debug == 1) { printf("132: tem quebra de linha nessa porra\n"); }
				if(debug == 1) { printf("133: buffer = '%s'(%ld)\n", buffer, safe_strlen(buffer)); }
				if(debug == 1) { printf("134: vou ter que escrever só parte\n"); }
				j = 0;
				while (j < BUFFER_SIZE)
				{
					if (buffer[j] == '\n')
						break ;
					*(*(line + line_number) + j + i) = buffer[j];
					buffer[j] = 0;
					j++;
				}
				last_offset = j + 1;
				if(debug == 1) { printf("147: last offset é %i\n", j); }
				if(debug == 1) { printf("148: last offset é %i\n", last_offset); }
				if(debug == 1) { printf("149: buffer[last_offset] = %i\n", buffer[last_offset]); }
				if(debug == 1) { printf("150: buffer[last_offset] = '%c'\n", buffer[last_offset]); }
				*(*(line + line_number) + j + i) = '\0';
				buffer[j] = 0;
				line_number++;
				if(debug == 1) { printf("154: retorno 1\n"); }
				return (1);
			}
			else
			{
				if(debug == 1) { printf("159: não tem quebra de linha nessa disgraça\n"); }
				if(debug == 1) { printf("160: buffer = '%s'(%ld)\n", buffer, safe_strlen(buffer)); }
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
			if(debug == 1) { printf("173: na verdade nem teve read. já tinha coisa nesse buffer\n"); }



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
			if(debug == 1) { printf("188: buftemporario = '%s'(%ld)\n", buftemporario, safe_strlen(buftemporario)); }

			if(debug == 1) { printf("190: tem '\\n' nesse buffer? %s\n", (ft_strchr(buftemporario, '\n') != NULL) ? "sim" : "nao"); }

			if (ft_strchr(buftemporario, '\n') != NULL)
			{
				if(debug == 1) { printf("194: tem um '\\n' nesse buffer\n"); }
				if(debug == 1) { printf("195: TODO: e agora ????????????\n"); }

				j = last_offset;
				while (1)
				{
					if(debug == 1) { printf("200: deu merda buscando '\\n' kkkkkk %i %d '%c'\n", j, buffer[j], buffer[j]); }
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
				if(debug == 1) { printf("211: retorno 1\n"); }
				return (1);
			}
			else
			{
				if(debug == 1) { printf("216: não tem um '\\n' nesse buffer\n"); }
				if(debug == 1) { printf("217: entao vou colocar esse finalzinho no inicio da linha\n"); }
				j = last_offset;
				while (j < BUFFER_SIZE)
				{
					*(*(line + line_number) + (j - last_offset)) = buffer[j];
					buffer[j] = 0;
					j++;
				}
				if(debug == 1) { printf("225: i = %i, j = %i, last_offset = %i\n", i, j, last_offset); }
				i += j - last_offset;
			}
		}
		else
		{
			if(debug == 1) { printf("231: então EOF está proximo\n"); }
			if(debug == 1) { printf("232: read só leu %i\n", read_saida); }
			if(debug == 1) { printf("233: buffer = '%s'(%ld)\n", buffer, safe_strlen(buffer)); }

			if(debug == 1) { printf("235: tem '\\n' nesse buffer? %s\n", (ft_strchr(buffer, '\n') != NULL) ? "sim" : "nao"); }
			if (ft_strchr(buffer, '\n') != NULL)
			{
				if(debug == 1) { printf("238: TODO: estamos proximo do EOF, e ainda tem '\\n' nesse caraio\n"); }
				j = 0;
				while (j < BUFFER_SIZE)
				{
					if (buffer[j] == '\n')
						break ;
					*(*(line + line_number) + j + i) = buffer[j];
					buffer[j] = 0;
					j++;
				}
				last_offset = j + 1;
				if(debug == 1) { printf("251: last offset é %i\n", j); }
				if(debug == 1) { printf("252: last offset é %i\n", last_offset); }
				if(debug == 1) { printf("253: buffer[last_offset] = %i\n", buffer[last_offset]); }
				if(debug == 1) { printf("254: buffer[last_offset] = '%c'\n", buffer[last_offset]); }
				*(*(line + line_number) + j + i) = '\0';
				buffer[j] = 0;
				line_number++;
				if(debug == 1) { printf("258: retorno 1\n"); }
				return (1);

			}
			else
			{
				if(debug == 1) { printf("264: ufa estamos proximo do EOF, e não tem '\\n' nessa merda\n"); }
				if(debug == 1) { printf("265: é só colocar tudo no *(line + line_number) e ja era\n"); }
				if(debug == 1) { printf("266: j = %i, i = %i, read_saida = %i\n", j, i, read_saida); }
				j = 0;
				while (j < read_saida)
				{
					*(*(line + line_number) + j + i) = buffer[j];
					buffer[j] = 0;
					j++;
				}
				*(*(line + line_number) + j + i) = '\0';
				line_number++;
				if(debug == 1) { printf("276: retorno 0\n"); }
				return (0);
			}
		}
	}
	if(debug == 1) { printf("284: retorno -1\n"); }
	return (-1);
}
