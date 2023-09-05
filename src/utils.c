/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbesa <arbesa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 21:44:35 by arbesa            #+#    #+#             */
/*   Updated: 2023/06/15 14:35:12 by arbesa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strcat(char *dest, char *src, t_data *data)
{
	char	*str;
	int		i;
	int		j;

	if (!dest || !src)
		return (NULL);
	i = 0;
	str = (char *)malloc(ft_strlen(src) + ft_strlen(dest) + 1);
	if (!str)
		return (ft_exit(data, 1), NULL);
	while (dest[i] != '\0')
	{
		str[i] = dest[i];
		i++;
	}
	j = 0;
	while (src[j] != '\0')
	{
		str[i + j] = src[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

void	ft_free(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		if (tab[i])
			free(tab[i]);
		i++;
	}
	free(tab);
}
