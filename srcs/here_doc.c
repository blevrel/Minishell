/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 16:34:01 by pirabaud          #+#    #+#             */
/*   Updated: 2022/11/13 11:04:04 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	here_doc_err_msg(t_data *data, char *limiter)
{
	ft_printf("minishell: warning: here-document delimited \
by end-of-file (wanted '%s')\n", limiter);
	clean_data(data, 1);
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
		here_doc_err_msg(data, limiter);
	new_line = ft_calloc((size_heredoc(line, data, limiter) + 1), sizeof(char));
	while (line[i] && ft_strcmp(line, limiter) != 0)
	{
		if (line[i] == 36 && line[i + 1] != 36 && check_char(&line[i + 1]) >= 0)
		{
			fill_env(new_line, &line[i], data, &j);
			i = move_indextoenv(line, i);
		}
		else
			ft_fill_char_and_increment(new_line, line, &i, &j);
	}
	if (ft_strcmp(line, limiter) == 0)
		new_line = ft_strcpy(new_line, line);
	free(line);
	return (new_line);
}

void	create_file(char **limiter, t_data *data)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	while (limiter[i] != NULL)
	{
		fd = open ("here_doc", O_WRONLY | O_TRUNC | O_CREAT, 0644);
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
		close (fd);
	}
}

void	here_doc(t_cmd *cmd, t_data *data)
{
	g_signal_trigger = IN_HERE_DOC;
	signal_handler();
	create_file(cmd->limiter, data);
	return ;
}
