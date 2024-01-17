/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:51:08 by ipetruni          #+#    #+#             */
/*   Updated: 2024/01/17 14:42:17 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

char	*trim_whitespace(const char *str)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = malloc(strlen(str) + 1);
	while (ft_isspace((unsigned char)str[i]))
		i++;
	while (str[i] != '\0')
	{
		if (ft_isspace((unsigned char)str[i]))
		{
			while (ft_isspace((unsigned char)str[i]))
				i++;
			if (str[i] != '\0')
				result[j++] = ' ';
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}
