/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbesa <arbesa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 21:44:37 by arbesa            #+#    #+#             */
/*   Updated: 2023/06/15 14:34:56 by arbesa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int	ft_lenword(char *str, char sep)
{
	int	i;

	i = 0;
	while (str[i] && sep != str[i])
		i++;
	return (i);
}

static int	ft_nbsep(char *str, char c)
{
	int	i;
	int	nb_word;

	i = 0;
	nb_word = 0;
	while (str[i])
	{
		while (str[i] != '\0' && str[i] == c)
			i++;
		if (str[i] != '\0')
			nb_word++;
		while (str[i] && c != str[i])
			i++;
	}
	return (nb_word);
}

static char	*ft_tab(char *tab, char set)
{
	int		i;
	int		size;
	char	*str;

	i = 0;
	size = ft_lenword(tab, set);
	str = (char *)malloc(size + 1);
	if (!str)
		return (NULL);
	while (i < size)
	{
		str[i] = tab[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_split(char const *s, char c, t_data *data)
{
	char	**newstr;
	int		i;
	int		j;
	int		nb_lines;

	if (s == NULL)
		return (NULL);
	nb_lines = ft_nbsep((char *)s, c);
	newstr = (char **)malloc(sizeof(char *) * (nb_lines + 1));
	if (!newstr)
		return (ft_exit(data, 1), NULL);
	i = 0;
	j = 0;
	while (s[i] && j < nb_lines)
	{
		while (s[i] != '\0' && c == s[i])
			i++;
		newstr[j] = ft_tab((char *)&s[i], c);
		if (!newstr[j])
			return (ft_free(newstr), ft_exit(data, 1), NULL);
		j++;
		while (s[i] && c != s[i])
			i++;
	}
	return (newstr[nb_lines] = NULL, newstr);
}
