/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:06:33 by gpassos-          #+#    #+#             */
/*   Updated: 2021/02/27 16:03:02 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif

size_t		ft_strlen(const char *s)
{
	int	contador;

	if (s == NULL)
		return (0);
	contador = 0;
	while (*(s + contador) != '\0')
		contador++;
	return (contador);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*saida;
	int		contador;
	int		next;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	saida = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (saida == NULL)
		return (NULL);
	next = 0;
	contador = 0;
	while (*((char *)s1 + contador) != '\0')
	{
		*(saida + contador) = *((char *)s1 + contador);
		contador++;
	}
	while (*((char *)s2 + next) != '\0')
	{
		*(saida + contador) = *((char *)s2 + next);
		next++;
		contador++;
	}
	*(saida + contador) = '\0';
	return (saida);
}

char		*ft_strchr(const char *s, int c)
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

void		*ft_memset(void *s, int c, size_t n)
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

static int	ft_min(int a, int b)
{
	if (a > b)
		return (b);
	else
		return (a);
}

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*saida;
	size_t	contador;
	size_t	s_len;
	int		alocar;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	alocar = ((start >= s_len) ? 1 : ft_min(s_len + 1, len + 1));
	saida = (char *)malloc(sizeof(char) * alocar);
	if (saida == NULL)
		return (NULL);
	if (start > s_len)
	{
		*(saida + 0) = '\0';
		return (saida);
	}
	contador = start;
	while ((contador < (start + len)) && (contador < s_len))
	{
		*(saida + (contador - start)) = *((char *)s + contador);
		contador++;
	}
	*(saida + (contador - start)) = '\0';
	return (saida);
}

int			get_next_line(int fd, char **line)
{
	static char	*buffer;
	static int	line_number = 0;
	static int	last_offset = 0;
	char		*temp_temp_line;
	char		*temp_line;
	int			read_saida;

	if (fd < 0 || BUFFER_SIZE <= 0 || line == NULL)
		return (-1);
	if (line_number == 0)
	{
		buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		ft_memset(buffer, 0, ft_min((BUFFER_SIZE + 1), 10));
	}
	temp_line = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	ft_memset(temp_line, 0, ft_min((BUFFER_SIZE + 1), 10));
	while (1)
	{
		if (last_offset == 0)
		{
			read_saida = read(fd, buffer, BUFFER_SIZE);
			if (read_saida < 0 || read_saida > BUFFER_SIZE)
			{
				free(temp_line);
				free(buffer);
				line_number = 0;
				return (-1);
			}
			buffer[read_saida] = '\0';
		}
		if (last_offset != 0)
		{
			if (ft_strchr(buffer + last_offset, '\n') == NULL)
			{
				temp_temp_line = ft_strjoin(temp_line, buffer + last_offset);
				free(temp_line);
				temp_line = temp_temp_line;
				temp_temp_line = ft_substr(temp_line, 0, ft_strlen(temp_line));
				free(temp_line);
				temp_line = temp_temp_line;
				last_offset = 0;
			}
			else
			{
				temp_temp_line = ft_strjoin(temp_line, buffer);
				free(temp_line);
				temp_line = temp_temp_line;
				temp_temp_line = ft_substr(temp_line, last_offset, ft_strchr(buffer + last_offset, '\n') - buffer - last_offset);
				free(temp_line);
				temp_line = temp_temp_line;
				last_offset += ft_strlen(temp_line) + 1;
				*line = temp_line;
				return (1);
			}
		}
		else if (read_saida == 0)
		{
			*line = (char *)malloc(sizeof(char) * (ft_strlen(temp_line) + 1));
			*line[0] = '\0';
			ft_memcpy(*line, temp_line, ft_strlen(temp_line));
			free(temp_line);
			free(buffer);
			line_number = 0;
			return (0);
		}
		else if (read_saida <= BUFFER_SIZE)
		{
			if (ft_strchr(buffer, '\n') != NULL)
			{
				temp_temp_line = ft_strjoin(temp_line, buffer);
				free(temp_line);
				temp_line = temp_temp_line;
				temp_temp_line = ft_substr(temp_line, 0, ft_strchr(temp_line, '\n') - temp_line);
				free(temp_line);
				temp_line = temp_temp_line;
				*line = temp_line;
				last_offset += ft_strchr(buffer, '\n') - buffer + 1;
				line_number++;
				return (1);
			}
			else
			{
				temp_temp_line = ft_strjoin(temp_line, buffer);
				free(temp_line);
				temp_line = temp_temp_line;
			}
		}
	}
	return (-1);
}
