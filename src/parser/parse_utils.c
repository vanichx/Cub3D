/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:51:08 by ipetruni          #+#    #+#             */
/*   Updated: 2024/01/17 11:47:59 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');
}

char	*trim_whitespace(const char *str)
{
	const char	*end;
	char		*trimmed;
	while(ft_isspace((unsigned char)*str))
		str++;
	if(*str == 0)
		return (ft_strdup(str));
	end = str + ft_strlen(str) - 1;
	while(end > str && ft_isspace((unsigned char)*end)) 
		end--;
	trimmed = ft_substr(str, 0, end - str + 1);
	return (trimmed);
}
