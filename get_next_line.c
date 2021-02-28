/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:06:33 by gpassos-          #+#    #+#             */
/*   Updated: 2021/02/28 12:20:00 by gabriel          ###   ########.fr       */
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

void		*ft_memcpy(void *dest, const void *src, size_t n)
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
		return ((char *)1);
	s_len = ft_strlen(s);
	alocar = ((start >= s_len) ? 1 : ft_min(s_len + 1, len + 1));
	saida = (char *)malloc(sizeof(char) * alocar);
	if (saida == NULL)
		return ((char *)2);
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

char		*ft_strdup(const char *s)
{
	char	*saida;
	int		i;

	i = 0;
	saida = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (saida == NULL)
		return (NULL);
	while (*((char *)s + i) != '\0')
	{
		*(saida + i) = *((char *)s + i);
		i++;
	}
	*(saida + i) = '\0';
	return (saida);
}

int			get_next_util(char **buffers[3], char *extra1, int flag, int len)
{

	if (ft_strchr(extra1, '\n') == NULL)
	{
		*buffers[1] = ft_strjoin(*buffers[2], extra1);
		free(*buffers[2]);
		*buffers[2] = *buffers[1];
		return (1);
	}
	else
	{
		*buffers[1] = ft_strjoin(*buffers[2], *buffers[0]);
		free(*buffers[2]);
		*buffers[2] = *buffers[1];
		if (flag == 0)
			*buffers[1] = ft_substr(*buffers[2], 0, ft_strchr(*buffers[2], '\n') - *buffers[2]);
		else
			*buffers[1] = ft_substr(*buffers[2], len, ft_strchr(extra1, '\n') - extra1);
		free(*buffers[2]);
		*buffers[2] = *buffers[1];
		return (2);
	}
}


int			get_next_line(int fd, char **line)
{
	static char	*buffer;
	static int	line_number = 0;
	static int	last_offset = 0;
	char		*temp_temp_line;
	char		*temp_line;
	int			read_saida;
	int			temp;
	char		**buffers[3];

	if (fd < 0 || BUFFER_SIZE <= 0 || line == NULL)
		return (-1);
	if (line_number == 0)
	{
		buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if ((BUFFER_SIZE + 1) > 10)
			ft_memset(buffer, 0, 10);
		else
			ft_memset(buffer, 0, (BUFFER_SIZE + 1));
	}
	temp_line = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if ((BUFFER_SIZE + 1) > 10)
		ft_memset(temp_line, 0, 10);
	else
		ft_memset(temp_line, 0, (BUFFER_SIZE + 1));
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
			buffers[0] = &buffer;
			buffers[1] = &temp_temp_line;
			buffers[2] = &temp_line;
			temp = get_next_util(buffers, (buffer + last_offset), 1, last_offset);
			if (temp == 2)
			{
				*line = temp_line;
				last_offset += ft_strlen(temp_line) + 1;
				return (1);
			}
			else if (temp == 1)
				last_offset = 0;
		}
		else if (read_saida == 0)
		{
			*line = (char *)malloc(sizeof(char) * (ft_strlen(temp_line) + 1));
			ft_memset(*line, 0, (ft_strlen(temp_line) + 1));
			ft_memcpy(*line, temp_line, ft_strlen(temp_line));
			free(temp_line);
			free(buffer);
			line_number = 0;
			return (0);
		}
		else if (read_saida <= BUFFER_SIZE)
		{
			buffers[0] = &buffer;
			buffers[1] = &temp_temp_line;
			buffers[2] = &temp_line;
			temp = get_next_util(buffers, buffer, 0, 0);
			if (temp == 2)
			{
				*line = temp_line;
				last_offset += ft_strchr(buffer, '\n') - buffer + 1;
				line_number++;
				return (1);
			}
		}
	}
	return (-1);
}
