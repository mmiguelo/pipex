/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 10:49:48 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/01/27 09:14:52 by mmiguelo         ###   ########.fr       */
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
			perror(FORK_ERROR);
	}
	return (0);
}
