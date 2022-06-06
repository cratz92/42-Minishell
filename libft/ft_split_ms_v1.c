/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponti-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 10:45:54 by gponti-s          #+#    #+#             */
/*   Updated: 2021/02/18 10:45:58 by gponti-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_nb_strs(char const *s, char *str)
{
	int	nb_strs;
	int	i;
	int	j;

	nb_strs = 0;
	if (!s[0] || !str[0])
		return (0);
	i = 0;
	while (s[i])
	{
		j = 0;
		if (s[i] == str[j])
		{
			while (s[i + j] == str[j])
			{
				j++;
				if (!str[j])
				{
					nb_strs++;
					i += (ft_strlen(str) - 1);
				}
			}
		}
		i++;
	}
	return (nb_strs);
}

static int	ft_next_word_count(char const *str, char sep, int i)
{
	int	count;

	count = 0;
	while (str[i] == sep && str[i] != '\0')
	{
		i++;
	}
	while (str[i] != '\0' && str[i] != sep)
	{
		count++;
		i++;
	}
	return (count);
}

static char	**ft_free(char **str_tab, int i)
{
	int	j;

	j = 0;
	while (j < i && str_tab[j] != 0)
	{
		free(str_tab[j]);
		j++;
	}
	free(str_tab);
	return (0);
}

char	**ft_split_ms(char const *str, char *del)
{
	int		s;
	int		i;
	int		j;
	char	**tab_str;

	s = 0;
	i = -1;
	tab_str = ft_malloc(str, charset);
	if (!tab_str)
		return (0);
	while (++i < ft_wordcount(str, charset))
	{
		j = 0;
		tab_str[i] = malloc(ft_next_word_count(str, charset, s) + 1);
		if (!(tab_str[i]))
			return (ft_free(tab_str, i));
		while (str[s] != '\0' && str[s] == charset)
			s++;
		while (str[s] != '\0' && str[s] != charset)
			tab_str[i][j++] = str[s++];
		tab_str[i][j] = '\0';
	}
	tab_str[i] = 0;
	return (tab_str);
}