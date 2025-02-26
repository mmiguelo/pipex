/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 22:23:36 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/02/14 15:11:38 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	create_here_doc(t_pipex *pipes)
{
	char		*line;
	const char	*limiter;

	close(pipes->fd[0]);
	limiter = pipes->av[2];
	while (1)
	{
		ft_putstr_fd("here_doc> ", 1);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
			&& line[ft_strlen(limiter)] == '\n')
		{
			close(STDIN_FILENO);
			free(line);
			line = get_next_line(STDIN_FILENO);
			break ;
		}
		ft_putstr_fd(line, pipes->fd[1]);
		free(line);
		line = NULL;
	}
	close(pipes->fd[1]);
}

char	*search_path(char *cmd, char **env)
{
	char	**full_path;
	char	*partial_path;
	char	*temp;
	int		i;

	i = 0;
	while (ft_strnstr(env[i], "PATH=", 5) == 0)
		i++;
	full_path = ft_split(env[i] + 5, ':' );
	if (!full_path)
		return (ft_putstr_fd("error in splitting search_path\n", 2), NULL);
	i = 0;
	while (full_path[i])
	{
		temp = ft_strjoin(full_path[i], "/");
		partial_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(partial_path, F_OK | X_OK) == 0)
			return (ft_free(full_path), partial_path);
		free(partial_path);
		i++;
	}
	ft_free(full_path);
	return (NULL);
}
