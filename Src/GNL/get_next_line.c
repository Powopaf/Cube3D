/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:31:21 by sbrochar          #+#    #+#             */
/*   Updated: 2026/04/01 18:48:58 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../gnl.h"
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

char	*ft_strchr(const char *str, int c)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == (unsigned char)c)
		{
			return ((char *)(str + i));
		}
		i++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)str + i);
	return (NULL);
}

void	all_free(char **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

char	*extract_line(char **storage)
{
	char	*str;
	char	*swap;
	int		i;

	i = 0;
	if (!*storage)
		return (NULL);
	while ((*storage)[i] && (*storage)[i] != '\n')
		i++;
	if ((*storage)[i] == '\n')
	{
		str = ft_substr((*storage), 0, i + 1);
		swap = ft_strdup((*storage) + i + 1);
		all_free(storage);
		*storage = swap;
		if ((!*storage) || (**storage == '\0'))
			all_free(&(*storage));
		return (str);
	}
	str = ft_strdup(*storage);
	all_free(storage);
	return (str);
}

char	*read_stock(int fd, char *storage)
{
	char	*buffer;
	int		bytes_read;
	char	*swap;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && (storage == NULL || !ft_strchr(storage, '\n')))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (all_free(&buffer), all_free(&storage), NULL);
		buffer[bytes_read] = '\0';
		if (!storage)
			storage = ft_strdup(buffer);
		else
		{
			swap = storage;
			storage = ft_strjoin(storage, buffer);
			all_free(&swap);
		}
	}
	all_free(&buffer);
	return (storage);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*str;

	if (fd == -42)
	{
		if (storage)
		{
			free(storage);
			storage = NULL;
			return (NULL);
		}
	}
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (all_free(&storage), NULL);
	storage = read_stock(fd, storage);
	if (!storage)
		return (all_free(&storage), NULL);
	if (storage[0] == '\0')
		return (all_free(&storage), NULL);
	str = extract_line(&storage);
	return (str);
}
