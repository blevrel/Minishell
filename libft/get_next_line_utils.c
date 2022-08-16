/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 17:30:15 by pirabaud          #+#    #+#             */
/*   Updated: 2022/05/10 11:36:51 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_copy(char *dest, char *src)
{
	int	i;

	i = 0;
	if (src == NULL)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		++i;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin_free(char *str, char *buff)
{
	int		i;
	int		j;
	char	*dest;

	j = 0;
	i = 0;
	if (buff[i] == 0)
		return (str);
	while (buff[i])
		++i;
	dest = malloc((i + ft_strlen(str) + 1) * sizeof(char));
	i = 0;
	if (str != NULL)
	{
		dest = ft_copy(dest, str);
		while (dest[i])
			++i;
	}
	while (buff[j])
		dest[i++] = buff[j++];
	dest[i] = '\0';
	free(str);
	return (dest);
}
