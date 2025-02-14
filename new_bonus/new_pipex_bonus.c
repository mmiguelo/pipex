/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_pipex_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 21:09:03 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/02/14 13:34:34 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	main_process(char **av, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		perror(PIPE_ERROR);
	pid = fork();
	if (pid == -1)
	{
		perror(FORK_ERROR);
		close(fd[0]);
		close(fd[1]);
	}
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		process(*av, envp, fd);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	waitpid(pid, NULL, 0);
}

int main(int ac, char **av, char **envp)
{
	t_pipex	pipes;
	int		fd_in;
	int		fd_out;

	if (av[1] && (ft_strncmp(av[1], "here_doc", 8) == 0 && ac < 6))
		return (ft_putstr_fd(INPUT_ERROR, 2), 1);
	if (ac < 5)
		return (ft_putstr_fd(INPUT2_ERROR, 2), 2);
	parse_bonus(envp, av);
	ft_init_pipes(&pipes, ac, av, envp);
	if (pipes.here_doc)
		start_here_doc(&pipes);
	else
	{
		fd_in = open_file(av[1], 2);
		fd_out = open_file(av[ac -1], 1);
		dup2(fd_in, STDIN_FILENO);
		while (pipes.cmd < ac - 2)
			main_process(&av[pipes.cmd++], envp);
		dup2(fd_out, STDOUT_FILENO);
		process(av[ac - 2], envp, NULL);
	}
}
