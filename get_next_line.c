/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:06:33 by gpassos-          #+#    #+#             */
/*   Updated: 2021/02/24 11:56:27 by gabriel          ###   ########.fr       */
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

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	contador;
	char	*saida;

	saida = (char *)s;
	contador = 0;
	while (contador < n)
	{
		if (*(saida) == (char)c)
			return (saida);
		saida++;
		contador++;
	}
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

int		get_next_line(int fd, char **line)
{
	static char	*buffer;
	static int	line_number = 0;
	static int	last_offset = 0;
	char		*temp_line;
	int			read_saida;
	int			i;
	// int			j;

	int			debug;
	debug = 0;
	debug = 1;


	if(debug == 1) { printf("143: --------------------\n"); }
	if(debug == 1) { printf("144: fd = %d\n", fd); }
	if(debug == 1) { printf("145: line = %p\n", line); }
	if(debug == 1) { printf("146: buffer = %p\n", buffer); }
	if(debug == 1) { printf("147: line_number = %d\n", line_number); }
	if(debug == 1) { printf("148: line_offset = %d\n", last_offset); }
	if(debug == 1) { printf("149: --------------------\n"); }

	if(BUFFER_SIZE <= 0 || fd < 0 || line == NULL || fd > RLIMIT_NOFILE)
		return (-1);

	if (line_number == 0)
	{
		if(debug == 1) { printf("156: primeira linha entao vou inicializar o buffer\n"); }
		buffer = (char *)ft_calloc(sizeof(char), BUFFER_SIZE + 1);
		if (buffer == NULL)
			return (-1);
	}

	if(debug == 1) { printf("162: inicializando temp_line\n"); }
	temp_line = (char *)ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (temp_line == NULL)
		return (-1);


	i = 0;
	while (1)
	{
		if(debug == 1) { printf("171: temp_line = '"); }
		if(debug == 1) { write(1, temp_line, BUFFER_SIZE); }
		if(debug == 1) { printf("'\n"); }
		if(debug == 1) { printf("174: lendo arquivo\n"); }
		read_saida = read(fd, buffer, BUFFER_SIZE);
		buffer[BUFFER_SIZE] = '\0';
		if(debug == 1) { printf("177: foi lido %d\n", read_saida); }

		if (read_saida == 0)
		{
			if(debug == 1) { printf("181: nada foi lido EOF atingido\n"); }
			*line = temp_line;
			line_number++;
			return (0);
		}
		else if (read_saida <= BUFFER_SIZE)
		{
			if(debug == 1) { printf("188: tem coisa para passar pro temp_line\n"); }
			if(debug == 1) { printf("189: tem '\\n' nesse buffer? %s\n", (ft_memchr(buffer, '\n', BUFFER_SIZE) != NULL) ? "sim" : "nao"); }
			if (ft_memchr(buffer, '\n', BUFFER_SIZE) != NULL)
			{
				if(debug == 1) { printf("192: tem '\\n' nesse buffer\n"); }
				if(debug == 1) { printf("193: \"caso tenha 1 ou mais '\\n' dentro do buffer nao faça mais chamadas para read\"\n"); }
				if(debug == 1) { printf("194: buffer = '%s'(%ld)\n", buffer, ft_strlen(buffer)); }
				if(debug == 1) { printf("195: esse '\\n' está na posicao %ld\n", (char *)ft_memchr(buffer, '\n', BUFFER_SIZE) - buffer); }
				if(debug == 1) { printf("196: então vou copiar até ai no temp_line\n"); }

				ft_memcpy(temp_line, buffer, ((char *)ft_memchr(buffer, '\n', BUFFER_SIZE) - buffer));
				last_offset += ((char *)ft_memchr(buffer, '\n', BUFFER_SIZE) - buffer);
				if(debug == 1) { printf("200: last_offset = %d\n", last_offset); }
				line_number++;
				*line = (char *)ft_calloc(sizeof(char), last_offset);
				if (*line == NULL)
					return (-1);
				ft_memcpy(*line, temp_line, last_offset);
				
				free(temp_line);
				return (1);
			}
			else
			{
				if(debug == 1) { printf("212: não tem '\\n' nesse buffer\n"); }
				if(debug == 1) { printf("213: todo conteudo do buffer é copiado no temp_line. e continua\n"); }
				if(debug == 1) { printf("214: buffer = '%s'(%ld)\n", buffer, ft_strlen(buffer)); }
			}
		}
		else
			break ;
		if (i >= 2)
			break ;
		i++;
	}
	return (-1);
}
