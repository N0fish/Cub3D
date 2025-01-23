/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roarslan <roarslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 20:50:48 by roarslan          #+#    #+#             */
/*   Updated: 2024/10/21 10:24:25 by roarslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

char	*read_file(int fd, char *buffer)
{
	ssize_t	read_size;
	char	*dest;

	if (!buffer)
		buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	else if (buffer)
	{
		dest = ft_strdup(buffer);
		free(buffer);
		buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!buffer)
			return (free(dest), NULL);
	}
	read_size = 1;
	while (read_size > 0 && !ft_strchr(dest, '\n'))
	{
		read_size = read(fd, buffer, BUFFER_SIZE);
		if (read_size == -1)
			return (free(dest), free(buffer), NULL);
		buffer[read_size] = '\0';
		dest = ft_strjoin(dest, buffer);
	}
	return (free(buffer), dest);
}

char	*fill_line(char *buffer)
{
	size_t	i;
	char	*dest;

	i = 0;
	if (!buffer)
		return (NULL);
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	dest = ft_calloc(i + 2, sizeof(char));
	if (!dest)
		return (free(dest), NULL);
	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
	{
		dest[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
	{
		dest[i] = '\n';
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*clean_buffer(char *buffer)
{
	char	*dest;
	size_t	i;
	size_t	j;

	if (!buffer)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
		return (free(buffer), NULL);
	dest = ft_calloc(ft_strlen(buffer) - i + 1, sizeof(char));
	if (!dest)
		return (free(buffer), NULL);
	j = 0;
	i++;
	while (buffer[i] != '\0')
		dest[j++] = buffer[i++];
	dest[j] = '\0';
	free(buffer);
	return (dest);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || (read(fd, 0, 0) < 0))
		return (NULL);
	buffer = read_file(fd, buffer);
	if (!buffer || buffer[0] == '\0')
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	line = fill_line(buffer);
	buffer = clean_buffer(buffer);
	return (line);
}
/*
int	main(void)
{
	char	*line;
	int	fd;
	int	i;

	fd = open("get_next_line.c", O_RDONLY);
	i = 0;
	while (i < 11)
	{
		line = get_next_line(fd);
		printf("%s", line);
		free(line);
		i++;
	}
	close(fd);
	return (0);
}
*/
