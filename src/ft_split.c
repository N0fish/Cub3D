/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roarslan <roarslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:21:40 by roarslan          #+#    #+#             */
/*   Updated: 2024/10/17 15:24:58 by roarslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	free_mem(char **tofree)
{
	int	i;

	i = 0;
	while (tofree[i])
		free (tofree[i++]);
	free (tofree);
}

int	ft_countwords(char const *str, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && str[i] == c)
			i++;
		if (str[i] != '\0')
		{
			words++;
			while (str[i] != '\0' && str[i] != c)
				i++;
		}
	}
	return (words);
}

char	*ft_strduplicate(char const *str, char c)
{
	char	*dest;
	int		i;
	int		len;

	len = 0;
	while (str[len] != '\0' && str[len] != c)
		len++;
	dest = (char *)malloc(sizeof(char) * len + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (i < len && str[i])
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	todup(char **dest, char const *s, char c)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (s[i] != '\0')
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			dest[k] = ft_strduplicate(&s[i], c);
			k++;
		}
		while (s[i] && s[i] != c)
			i++;
	}
	dest[k] = 0;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**dest;

	if (!s)
		return (NULL);
	dest = (char **)malloc(sizeof(char *) * (ft_countwords(s, c) + 1));
	if (!dest)
		return (NULL);
	if (!todup(dest, s, c))
		return (free_mem(dest), NULL);
	return (dest);
}
