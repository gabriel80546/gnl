/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:25:10 by gabriel           #+#    #+#             */
/*   Updated: 2021/02/22 07:37:11 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif

int	main(void)
{
	int fd;
	char **linhas;
	int i/*, j*/;

	linhas = (char **)malloc(sizeof(char *) * 50);
	fd = open("oloco.txt", O_RDONLY);
	// while (get_next_line(fd, linhas) != 0)
	// {
	// 	printf("linha[%i] = '%s'(%ld)\n", i, linhas[i], strlen(linhas[i]));
	// 	i++;
	// }
	i = 0;
	if(get_next_line(fd, linhas) == 0) { 
		printf("linha[%i] = '%s'(%ld)\n", i, linhas[i], strlen(linhas[i]));
		return (1); }
	printf("linha[%i] = '%s'(%ld)\n", i, linhas[i], strlen(linhas[i]));
	i++;
	if(get_next_line(fd, linhas) == 0) { 
		printf("linha[%i] = '%s'(%ld)\n", i, linhas[i], strlen(linhas[i]));
		return (1); }
	printf("linha[%i] = '%s'(%ld)\n", i, linhas[i], strlen(linhas[i]));
	i++;
	if(get_next_line(fd, linhas) == 0) { 
		printf("linha[%i] = '%s'(%ld)\n", i, linhas[i], strlen(linhas[i]));
		return (1); }
	printf("linha[%i] = '%s'(%ld)\n", i, linhas[i], strlen(linhas[i]));
	i++;
	if(get_next_line(fd, linhas) == 0) { 
		printf("linha[%i] = '%s'(%ld)\n", i, linhas[i], strlen(linhas[i]));
		return (1); }
	printf("linha[%i] = '%s'(%ld)\n", i, linhas[i], strlen(linhas[i]));
	i++;
	if(get_next_line(fd, linhas) == 0) { 
		printf("linha[%i] = '%s'(%ld)\n", i, linhas[i], strlen(linhas[i]));
		return (1); }
	printf("linha[%i] = '%s'(%ld)\n", i, linhas[i], strlen(linhas[i]));

// printf("linha[%i] = '", i);
// 	j = 0;
// 	while (*(*(linhas + i) + j) != '\0')
// 	{
// 		printf("%c", linhas[i][j]);
// 		j++;
// 	}
// 	printf("'\n");

	i++;
	if(get_next_line(fd, linhas) == 0) { 
		printf("linha[%i] = '%s'(%ld)\n", i, linhas[i], strlen(linhas[i]));
		return (1); }
	// printf("linha[%i] = '%s'(%ld)\n", i, linhas[i], strlen(linhas[i]));

	// printf("linha[%i] = '", i);
	// j = 0;
	// while (*(*(linhas + i) + j) != '\0')
	// {
	// 	printf("%c", linhas[i][j]);
	// 	j++;
	// }
	// printf("'\n");
	// printf("linha[%i] = '%s'\n", i, linhas[i]);


	i++;
	if(get_next_line(fd, linhas) == 0) { 
		printf("linha[%i] = '%s'(%ld)\n", i, linhas[i], strlen(linhas[i]));
		return (1); }
	printf("linha[%i] = '%s'(%ld)\n", i, linhas[i], strlen(linhas[i]));
	i++;
	if(get_next_line(fd, linhas) == 0) { 
		printf("linha[%i] = '%s'(%ld)\n", i, linhas[i], strlen(linhas[i]));
		return (1); }
	printf("linha[%i] = '%s'(%ld)\n", i, linhas[i], strlen(linhas[i]));
	i++;
	if(get_next_line(fd, linhas) == 0) { 
		printf("linha[%i] = '%s'(%ld)\n", i, linhas[i], strlen(linhas[i]));
		return (1); }
	printf("linha[%i] = '%s'(%ld)\n", i, linhas[i], strlen(linhas[i]));
	i++;
	if(get_next_line(fd, linhas) == 0) { 
		printf("linha[%i] = '%s'(%ld)\n", i, linhas[i], strlen(linhas[i]));
		return (1); }
	printf("linha[%i] = '%s'(%ld)\n", i, linhas[i], strlen(linhas[i]));
	i++;
	if(get_next_line(fd, linhas) == 0) { 
		printf("linha[%i] = '%s'(%ld)\n", i, linhas[i], strlen(linhas[i]));
		return (1); }
	printf("linha[%i] = '%s'(%ld)\n", i, linhas[i], strlen(linhas[i]));
	i++;
	if(get_next_line(fd, linhas) == 0) { 
		printf("linha[%i] = '%s'(%ld)\n", i, linhas[i], strlen(linhas[i]));
		return (1); }
	free(linhas);
	return (0);
}
