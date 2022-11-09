/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 16:34:01 by pirabaud          #+#    #+#             */
/*   Updated: 2022/11/09 17:32:05 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	here_doc_err_msg(char *limiter)
{
	ft_printf("minishell: warning: here-document delimited \
by end-of-file (wanted '%s')\n", limiter);
	exit(0);
}

char	*tokenize_here_doc_line(t_data *data, char *limiter)
{
	int		i;
	int		j;
	char	*line;
	char	*new_line;

	i = 0;
	j = 0;
	line = readline("");
	if (line == NULL)
		here_doc_err_msg(limiter);
	new_line = malloc((size_here_doc_line(line, data) + 1) * sizeof(char));
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] != '$'
			&& check_char(&line[i + 1]) >= 0)
		{
			fill_env(new_line, &line[i], data, &j);
			i = move_indextoenv(line, i);
		}
		else
			ft_fill_char_and_increment(new_line, line, &i, &j);
	}
	new_line[j] = '\0';
	free(line);
	return (new_line);
}

void	create_file(char **limiter, t_data *data)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open ("here_doc", O_WRONLY | O_CREAT, 0644);
	while (limiter[i] != NULL)
	{
		line = tokenize_here_doc_line(data, limiter[i]);
		while (ft_strcmp(line, limiter[i]) != 0)
		{
			ft_putstr_fd(line, fd);
			ft_putchar_fd('\n', fd);
			free(line);
			line = tokenize_here_doc_line(data, limiter[i]);
		}
		free(line);
		++i;
	}
	close (fd);
}

void	here_doc(t_cmd *cmd, t_data *data)
{

	g_signal_trigger = IN_HERE_DOC;
	signal_handler();
	create_file(cmd->limiter, data);
	return ;
}
