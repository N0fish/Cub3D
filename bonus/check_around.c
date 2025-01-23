/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_around.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:17:33 by roarslan          #+#    #+#             */
/*   Updated: 2024/11/13 21:23:45 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

int	check_around(char **tab, int y, int x, char *allowed_chars)
{
	if (y > 0)
	{
		if ((tab[y][x] == '0' || tab[y][x] == 'X')
			&& x + 1 >= (int)ft_strlen(tab[y - 1]))
			return (0);
		if (!ft_strchr(allowed_chars, tab[y - 1][x]) && tab[y - 1][x] != 'X')
			return (0);
	}
	if (tab[y + 1])
	{
		if ((tab[y][x] == '0' || tab[y][x] == 'X')
			&& x + 1 >= (int)ft_strlen(tab[y + 1]))
			return (0);
		if (!ft_strchr(allowed_chars, tab[y + 1][x]) && tab[y + 1][x] != 'X')
			return (0);
	}
	if (x > 0)
		if (!ft_strchr(allowed_chars, tab[y][x - 1]) && tab[y][x - 1] != 'X')
			return (0);
	if (tab[y][x + 1])
		if (!ft_strchr(allowed_chars, tab[y][x + 1]) && tab[y][x + 1] != 'X')
			return (0);
	return (1);
}

int	check_above(char **tab, int y, int x, char *charset)
{
	if (x > 0 && x - 1 < (int)ft_strlen(tab[y - 1])
		&& tab[y - 1][x - 1] && !is_charset(tab[y - 1][x - 1], charset))
		return (0);
	if (x < (int)ft_strlen(tab[y - 1]) && tab[y - 1][x]
		&& !is_charset(tab[y - 1][x], charset))
		return (0);
	if (x + 1 < (int)ft_strlen(tab[y - 1]) && tab[y - 1][x + 1]
		&& !is_charset(tab[y - 1][x + 1], charset))
		return (0);
	return (1);
}

int	check_below(char **tab, int y, int x, char *charset)
{
	if (x > 0 && x - 1 < (int)ft_strlen(tab[y + 1])
		&& tab[y + 1][x - 1] && !is_charset(tab[y + 1][x - 1], charset))
		return (0);
	if (x < (int)ft_strlen(tab[y + 1]) && tab[y + 1][x]
		&& !is_charset(tab[y + 1][x], charset))
		return (0);
	if (x + 1 < (int)ft_strlen(tab[y + 1]) && tab[y + 1][x + 1]
		&& !is_charset(tab[y + 1][x + 1], charset))
		return (0);
	return (1);
}

int	is_charset(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}
