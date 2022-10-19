/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 09:04:41 by pirabaud          #+#    #+#             */
/*   Updated: 2022/10/19 14:46:46 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_cpy_save(char *save)
{
	char	*dst;
	int		i;

	i = 0;
	while (save[i] != '\n' && save[i])
		++i;
	if (save[i] == '\n')
		++i;
	++i;
	dst = ft_calloc(i, sizeof(char));
	i = 0;
	while (save[i] != '\n' && save[i])
	{
		dst[i] = save[i];
		++i;
	}
	if (save[i] == '\n')
		dst[i] = '\n';
	return (dst);
}

char	*free_save(char *save)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (save[i] != '\n' && save[i])
		++i;
	if (save[i] == '\n')
		++i;
	str = ft_calloc((ft_strlen(&save[i]) + 1), sizeof(char));
	while (save[i])
	{
		str[j] = save[i];
		j++;
		i++;
	}
	free(save);
	save = NULL;
	if (str[0] == '\0')
	{
		free (str);
		return (NULL);
	}
	return (str);
}

int	check_n(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (1);
	while (str[i] != 0)
	{
		if (str[i] == '\n')
			return (0);
		++i;
	}
	return (1);
}

char	*ft_read(int fd, char *save, int buffer_size)
{
	char	*buff;
	int		ret;

	ret = 1;
	buff = malloc((buffer_size + 1) * sizeof(char));
	while (ret)
	{
		ret = read(fd, buff, buffer_size);
		if (ret < 0)
		{
			free(buff);
			return (NULL);
		}
		buff[ret] = '\0';
		if (buff[0] != 0)
			save = join_gnl(save, buff);
		if (check_n(save) == 0)
		{
			free(buff);
			return (save);
		}
	}
	free (buff);
	return (save);
}

char	*get_next_line(int fd, int buffer_size)
{
	static char	*save[1024];
	char		*dest;

	dest = NULL;
	save[fd] = ft_read(fd, save[fd], buffer_size);
	if (save[fd] == NULL)
		return (NULL);
	if (save[fd][0] == 0)
	{
		free(save[fd]);
		return (NULL);
	}
	dest = ft_cpy_save(save[fd]);
	save[fd] = free_save(save[fd]);
	return (dest);
}
