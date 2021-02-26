/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:06:33 by gpassos-          #+#    #+#             */
/*   Updated: 2021/02/26 02:05:42 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
// #include "libft/libft.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif

size_t	ft_strlen(const char *s)
{
	int	contador;

	if (s == NULL)
		return (0);
	contador = 0;
	while (*(s + contador) != '\0')
		contador++;
	return (contador);
}

char	*ft_strjoin(char const *s1, char const *s2)
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


void	*ft_calloc(size_t nmemb, size_t size)
{
	void *saida;

	saida = malloc(nmemb * size);
	if (saida == NULL)
		return (NULL);
	ft_memset(saida, 0, nmemb * size);
	return (saida);
}

void	*ft_calloco(size_t nmemb, size_t size)
{
	return ft_calloc(nmemb, size);
}
void	*ft_calloca(size_t nmemb, size_t size)
{
	return ft_calloc(nmemb, size);
}

char	*join_and_free(void)
{
	return (NULL);
}

void	print_nstring(char *str, int n)
{
	int i;
	
	i = 0;
	while (i < n)
	{
		// printf("%c[%d]", str[i], str[i]);
		printf("%c", str[i]);
		i++;
	}
	return ;
}


char	*ft_strdup(const char *s)
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

int		get_next_line(int fd, char **line)
{
	static char	*buffer;
	static int	line_number = 0;
	static int	last_offset = 0;
	char		*temp_temp_line;
	char		*temp_line;
	int			size_temp_line;
	int			read_saida;
	// int			i;
	// int			j;

	int			debug;
	debug = 1;
	debug = 0;

	if(debug == 1) { printf("179: --------------------\n"); }
	if(debug == 1) { printf("180: fd = %d\n", fd); }
	if(debug == 1) { printf("181: line = %p\n", line); }
	if(debug == 1) { printf("182: buffer = %p\n", buffer); }
	if(debug == 1) { printf("183: line_number = %d\n", line_number); }
	if(debug == 1) { printf("184: last_offset = %d\n", last_offset); }
	if(debug == 1) { printf("185: --------------------\n"); }

	if(line_number == 0)
		buffer = (char *)ft_calloc(sizeof(char), BUFFER_SIZE + 1);

	temp_line = (char *)ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	size_temp_line = 0;

	while (1)
	{
		if (last_offset == 0)
		{
			read_saida = read(fd, buffer, BUFFER_SIZE);
			buffer[read_saida] = '\0';
		}
		if (read_saida == 0)
		{
			return (-1);
		}
		else if (read_saida <= BUFFER_SIZE)
		{
			if(debug == 1) { printf("209: leitura normal\n"); }
			if(debug == 1) { printf("210: buffer = '%s'\n", buffer); }
			if(debug == 1) { printf("211: temp_line = '%s'\n", temp_line); }
			if(debug == 1) { printf("212: tem '\\n' no buffer? %s\n", (ft_strchr(buffer, '\n') != NULL) ? "sim" : "nao"); }

			if (ft_strchr(buffer, '\n') != NULL)
			{
				if(debug == 1) { printf("216: tem '\\n' nesse buffer\n"); }
				temp_temp_line = ft_strjoin(temp_line, buffer);
				free(temp_line);
				temp_line = temp_temp_line;
				size_temp_line = ft_strlen(temp_line);
				// free(temp_temp_line);
				if(debug == 1) { printf("260: buffer = '%s'\n", buffer); }
				if(debug == 1) { printf("261: temp_line = '%s'\n", temp_line); }

				temp_temp_line = ft_substr(temp_line, 0, ft_strchr(temp_line, '\n') - temp_line);
				free(temp_line);
				temp_line = temp_temp_line;
				size_temp_line = ft_strlen(temp_line);
				*line = temp_line;
				if(debug == 1) { printf("268: buffer = '%s'\n", buffer); }
				if(debug == 1) { printf("269: temp_line = '%s'\n", temp_line); }


				last_offset += ft_strchr(buffer, '\n') - buffer;

				return (0);
			}
			else
			{
				if(debug == 1) { printf("221: nao tem '\\n' nesse buffer\n"); }
				temp_temp_line = ft_strjoin(temp_line, buffer);
				free(temp_line);
				temp_line = temp_temp_line;
				size_temp_line = ft_strlen(temp_line);
			}

		}
	}
	return (-1);
}
