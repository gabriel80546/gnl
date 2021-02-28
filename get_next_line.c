/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:06:33 by gpassos-          #+#    #+#             */
/*   Updated: 2021/02/28 18:23:58 by gabriel          ###   ########.fr       */
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

int			get_next_util(char *bf[3], char *extra1)
{
	if (ft_strchr(extra1, '\n') == NULL)
	{
		bf[1] = ft_strjoin(bf[2], extra1);
		free(bf[2]);
		bf[2] = bf[1];
		return (1);
	}
	else
	{
		bf[1] = ft_strjoin(bf[2], bf[0]);
		free(bf[2]);
		bf[2] = bf[1];
		bf[1] = ft_substr(bf[2], 0, ft_strchr(bf[2], '\n') - bf[2]);
		free(bf[2]);
		bf[2] = bf[1];
		return (2);
	}
}

int			get_fim(char *bf2, char **line)
{
	*line = (char *)malloc(sizeof(char) * (ft_strlen(bf2) + 1));
	ft_memset(*line, 0, (ft_strlen(bf2) + 1));
	ft_memcpy(*line, bf2, ft_strlen(bf2));
	free(bf2);
	return (0);
}

int			get_next_line(int fd, char **line)
{
	static char	buffer[BUFFER_SIZE + 1];
	int			flag;
	int			read_saida;
	char		*bf[3];

	flag = 0;
	if (fd < 0 || BUFFER_SIZE <= 0 || line == NULL)
		return (-1);
	bf[2] = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	ft_memset(bf[2], 0, ft_min(10, (BUFFER_SIZE + 1)));
	while (1)
	{
		if (buffer[0] == '\0' || flag == 1)
		{
			read_saida = read(fd, buffer, BUFFER_SIZE);
			if (read_saida < 0 || read_saida > BUFFER_SIZE)
			{
				free(bf[2]);
				return (-1);
			}
			buffer[read_saida] = '\0';
		}
		else
			read_saida = BUFFER_SIZE - 1;
		if (read_saida > 0 && read_saida <= BUFFER_SIZE)
		{
			flag = 1;
			bf[0] = buffer;
			if (get_next_util(bf, buffer) == 2)
			{
				*line = bf[2];
				read_saida = (ft_strlen(buffer) - (ft_strchr(buffer, '\n') - buffer + 1));
				ft_memcpy(buffer, (ft_strchr(buffer, '\n') + 1), read_saida);
				buffer[read_saida] = '\0';
				return (1);
			}
		}
		else if (read_saida == 0)
			return (get_fim(bf[2], line));
	}
	return (-1);
}
