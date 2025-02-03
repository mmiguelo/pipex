/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 10:49:48 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/02/03 10:54:12 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char **argv)
{
	int		fd[2];
	// fd[0] -> read
	// fd[1] -> write
	pid_t	id;

	if (argc == 5)
	{
		pipe(fd);
		if (pipe(fd) == -1)
			perror(PIPE_ERROR);
		id = fork();
		if (id == -1)
		{
			perror(FORK_ERROR);
			close(fd[0]);
			close(fd[1]);
		}
	}
	else
	{
		ft_putstr_fd("Wrong input. Try .pipex file1 cmd1 cmd2 file2\n", 2);
		exit(42);
	}
	return (0);
}
