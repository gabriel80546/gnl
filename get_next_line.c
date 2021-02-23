/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:06:33 by gpassos-          #+#    #+#             */
/*   Updated: 2021/02/22 10:16:45 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "libft/libft.h"

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

// static size_t	safe_strlen(const char *s)
// {
// 	return (s == NULL) ? 0 : ft_strlen(s);
// }
void	*ft_memset(void *s, int c, size_t n)
{
	size_t	contador;

	contador = 0;
	while (contador < n)
	{
		*((unsigned char *)s + contador) = (unsigned char)c;
		contador++;
	}
	return (s);
}

size_t	ft_strlen(const char *s)
{
	int	contador;

	contador = 0;
	while (*(s + contador) != '\0')
		contador++;
	return (contador);
}

char	*ft_strchr(const char *s, int c)
{
	char	*saida;

	saida = (char *)s;
	while (*(saida) != (char)c && *(saida) != '\0')
	{
		saida++;
	}
	if (*(saida) == (char)c)
		return (saida);
	else
		return (NULL);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	contador;

	if (dest == NULL && src == NULL)
		return (NULL);
	contador = 0;
	while (contador < n)
	{
		*((char *)dest + contador) = *((char *)src + contador);
		contador++;
	}
	return (dest);
}


int				get_next_line(int fd, char **line)
{
	static char	buffer[BUFFER_SIZE + 1] = {0};
	static int	line_number = 0;
	static int	last_offset = 0;
	char		temp_buffer[BUFFER_SIZE + 1];
	int			i;
	int			j;
	int			whitespace;
	int			first_read;
	int			read_saida;

	whitespace = 0;
	first_read = 1;

	if(BUFFER_SIZE <= 0 || fd <= 0 || line == NULL)
	{
		*(line + line_number) = (char *)malloc(sizeof(char) * 2);
		*(*(line + line_number) + 0) = '\0';
		*(*(line + line_number) + 1) = '\0';
		return (-1);
	}
	*(line + line_number) = (char *)malloc(sizeof(char) * 10000);
	if (line_number == 0)
		ft_memset(buffer, whitespace, BUFFER_SIZE + 1);

	i = 0;
	while (i < BUFFER_SIZE)
	{
		if (buffer[i] != whitespace)
			first_read = 0;
		i++;
	}
	i = 0;
	j = 0;
	while (1)
	{
		if (first_read == 1)
		{
			read_saida = read(fd, buffer, BUFFER_SIZE);
			buffer[BUFFER_SIZE] = '\0';
		}
		else
			read_saida = BUFFER_SIZE + 1;
		first_read = 1;
		if (read_saida == 0)
		{
			*(*(line + line_number) + BUFFER_SIZE + i) = '\0';
			line_number++;
			return (0);
		}
		if (read_saida == BUFFER_SIZE)
		{
			if (ft_strchr(buffer, '\n') != NULL)
			{
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
				*(*(line + line_number) + j + i) = '\0';
				buffer[j] = 0;
				line_number++;
				return (1);
			}
			else
			{
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
			ft_memcpy(temp_buffer, buffer, BUFFER_SIZE + 1);
			j = 0;
			while (j < BUFFER_SIZE)
			{
				if (buffer[j] == 0)
					temp_buffer[j] = ' ';
				else
					temp_buffer[j] = buffer[j];
				j++;
			}
			temp_buffer[j] = '\0';
			if (ft_strchr(temp_buffer, '\n') != NULL)
			{
				j = last_offset;
				while (1)
				{
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
				return (1);
			}
			else
			{
				j = last_offset;
				while (j < BUFFER_SIZE)
				{
					*(*(line + line_number) + (j - last_offset)) = buffer[j];
					buffer[j] = 0;
					j++;
				}
				i += j - last_offset;
			}
		}
		else
		{
			if (ft_strchr(buffer, '\n') != NULL)
			{
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
				*(*(line + line_number) + j + i) = '\0';
				buffer[j] = 0;
				line_number++;
				return (1);
			}
			else
			{
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
		}
	}
	return (-1);
}
