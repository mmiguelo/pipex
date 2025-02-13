/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:42:25 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/02/13 12:34:14 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	create_process(t_pipex *pipes)
{
		
}

void	create_here_doc(t_pipex *pipes)
{
	const char	*limiter;
	char		*line;

	limiter = pipes->argv[2];
	while (1)
	{
		ft_printf("pipex_bonus here_doc> ");
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		write(pipes->fd[1], line, ft_strlen(line));
		write(pipes->fd[1], "\n", 1);
		free(line);
		line = NULL;
	}
	close(pipes->fd[0]);
	close(pipes->fd[1]);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipes;

	parse_bonus(envp, argv);
	if ((ft_strcmp("here_doc", argv[1]) == '0') && argc < 6)
		return (ft_putstr_fd(INPUT_ERROR, 2), 4);
	if (argc < 5)
		return (ft_putstr_fd(INPUT2_ERROR, 2), 5);
	ft_init_pipes(&pipes, argc, argv, envp);
	if (pipes.here_doc)
	{
		if (pipe(pipes.fd) == -1)
			return (ft_putstr_fd(PIPE_ERROR, 2), 6);
		pipes.pid = create_fork(&pipes);
		if (pipes.pid == 0)
			create_here_doc(&pipes);
		else
		{
			close(pipes.fd[1]);
			dup2(pipes.fd[0], STDIN_FILENO);
			close(pipes.fd[0]);
			create_process(&pipes);
		}
	}
	else
		create_process(&pipes);
}
