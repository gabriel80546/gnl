/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:06:33 by gpassos-          #+#    #+#             */
/*   Updated: 2021/02/24 16:40:06 by gabriel          ###   ########.fr       */
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

void	*ft_calloc(size_t nmemb, size_t size)
{
	void *saida;

	saida = malloc(nmemb * size);
	if (saida == NULL)
		return (NULL);
	ft_memset(saida, 0, nmemb * size);
	return (saida);
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


	if(debug == 1) { printf("155: --------------------\n"); }
	if(debug == 1) { printf("156: fd = %d\n", fd); }
	if(debug == 1) { printf("157: line = %p\n", line); }
	if(debug == 1) { printf("158: buffer = %p\n", buffer); }
	if(debug == 1) { printf("159: line_number = %d\n", line_number); }
	if(debug == 1) { printf("160: last_offset = %d\n", last_offset); }
	if(debug == 1) { printf("161: --------------------\n"); }


	if(line_number == 0)
		buffer = (char *)ft_calloc(sizeof(char), BUFFER_SIZE + 1);

	temp_line = (char *)ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	size_temp_line = 0;
	temp_line[BUFFER_SIZE] = '\0';


	while (1)
	{
		read_saida = read(fd, buffer, BUFFER_SIZE);
		buffer[BUFFER_SIZE] = '\0';

		if(debug == 1) { printf("177: foi lido %d\n", read_saida); }
		if(debug == 1) { printf("178: buffer = '"); print_nstring(buffer, read_saida); printf("'\n"); }

		if (read_saida == 0)
			return (-1);
		else if (read_saida <= BUFFER_SIZE)
		{
			if(debug == 1) { printf("184: houve uma leitura normal\n"); }
			if(debug == 1) { printf("185: buffer = '"); print_nstring(buffer, read_saida); printf("'\n"); }
			if(debug == 1) { printf("186: temp_line = '"); print_nstring(temp_line, read_saida); printf("'\n"); }
			if(debug == 1) { printf("187: size_temp_line = %d\n", size_temp_line); }

			if(debug == 1) { printf("189: tem '\\n' no buffer? %s\n", (ft_strchr(buffer, '\n') != NULL) ? "sim" : "nao"); }
			if (ft_strchr(buffer, '\n') == NULL)
			{
				if(debug == 1) { printf("192: nao tem '\\n' no buffer\n"); }
				if(debug == 1) { printf("193: apenas copie esse buffer em temp_line e leia denovo\n"); }

				temp_temp_line = (char *)ft_calloc(sizeof(char), size_temp_line + 1);
				temp_temp_line[size_temp_line] = '\0';
				ft_memcpy(temp_temp_line, temp_line, size_temp_line);
				free(temp_line);
				size_temp_line += read_saida;
				temp_line = (char *)ft_calloc(sizeof(char), size_temp_line + 1);
				temp_line[size_temp_line] = '\0';
				if(debug == 1) { printf("202: temp_line = '"); print_nstring(temp_line, size_temp_line); printf("'\n"); }
				if(debug == 1) { printf("203: temp_temp_line = '"); print_nstring(temp_temp_line, size_temp_line - read_saida); printf("'\n"); }
				if(debug == 1) { printf("204: size_temp_line = %d\n", size_temp_line); }
				ft_memcpy(temp_line, temp_temp_line, size_temp_line - read_saida);
				ft_memcpy(temp_line + size_temp_line - read_saida, buffer, read_saida);
				free(temp_temp_line);
				if(debug == 1) { printf("208: temp_line = '"); print_nstring(temp_line, size_temp_line); printf("'\n"); }
				if(debug == 1) { printf("209: size_temp_line = %d\n", size_temp_line); }
			}
			else
			{
				if(debug == 1) { printf("213: tem '\\n' no buffer\n"); }
				// free(temp_line);

				temp_temp_line = (char *)ft_calloc(sizeof(char), size_temp_line + 1);
				temp_temp_line[size_temp_line] = '\0';
				ft_memcpy(temp_temp_line, temp_line, size_temp_line);
				free(temp_line);
				size_temp_line += read_saida;
				temp_line = (char *)ft_calloc(sizeof(char), size_temp_line + 1);
				temp_line[size_temp_line] = '\0';
				if(debug == 1) { printf("224: temp_line = '"); print_nstring(temp_line, size_temp_line); printf("'\n"); }
				if(debug == 1) { printf("225: temp_temp_line = '"); print_nstring(temp_temp_line, size_temp_line - read_saida); printf("'\n"); }
				if(debug == 1) { printf("226: size_temp_line = %d\n", size_temp_line); }
				ft_memcpy(temp_line, temp_temp_line, size_temp_line - read_saida);
				ft_memcpy(temp_line + size_temp_line - read_saida, buffer, read_saida);
				free(temp_temp_line);
				if(debug == 1) { printf("230: temp_line = '"); print_nstring(temp_line, size_temp_line); printf("'\n"); }
				if(debug == 1) { printf("231: size_temp_line = %d\n", size_temp_line); }

				if(debug == 1) { printf("230: temp_line = '"); print_nstring(temp_line, size_temp_line); printf("'(%ld)\n", ft_strlen(temp_line)); }
				if(debug == 1) { printf("230: size_temp_line = %d\n", size_temp_line); }
				*line = (char *)ft_calloc(sizeof(char), size_temp_line + 1);
				ft_memcpy(*line, temp_line, size_temp_line);
				free(temp_line);
				line_number++;
				return (1);
			}
		}
	}
	return (-1);
}
