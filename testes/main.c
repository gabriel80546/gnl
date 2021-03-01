/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:25:10 by gabriel           #+#    #+#             */
/*   Updated: 2021/02/28 21:38:10 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif

// size_t	ft_strlen(const char *s)
// {
// 	int	contador;

// 	if (s == NULL)
// 		return (0);
// 	contador = 0;
// 	while (*(s + contador) != '\0')
// 		contador++;
// 	return (contador);
// }

size_t	ft_strlen(const char *s);

int	main(void)
{
	int fd;
	char *linha;
	int i;
	int retorno;

	i = 0;
	fd = open("antigo.txt", O_RDONLY);
	while ((retorno = get_next_line(fd, &linha) == 1) && (i < 1 || 1))
	{
		printf("linha[%d] = '%s'(%ld); retorno = %i\n", i, linha, strlen(linha), retorno);
		free(linha);
		i++;
		// break;
	}
	if (retorno != -1)
	{
		printf("linha[%d] = '%s'(%ld); retorno = %i\n", i, linha, strlen(linha), retorno);
		free(linha);
	}
	return (0);
}

// while (read(fd, buffer, BUFFER_SIZE) > 0)
// {
// 	printf("buffer = '%s'\n", buffer);
// }
// printf("buffer = '%s'\n", buffer);