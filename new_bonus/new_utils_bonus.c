/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_utisl_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 21:20:42 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/02/13 21:20:42 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	parse_bonus(char **envp, char **argv)
{
	int	i;

	if (!envp || !*envp)
	{
		ft_putstr_fd(ENVP_ERROR, 2);
		exit(1);
	}
	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	if (!envp[i])
	{
		ft_putstr_fd(PATH_ERROR, 2);
		exit(2);
	}
	i = -1;
	while (argv[++i])
	{
		if (argv[i] && !argv[i][0])
		{
			ft_putstr_fd(INPUT2_ERROR, 2);
			exit(3);
		}
	}
	return ;
}

void	ft_init_pipes(t_pipex *pipes, int argc, char **argv, char **envp)
{
	pipes->argc = argc;
	pipes->argv = argv;
	pipes->envp = envp;
	if (ft_strcmp("here_doc", argv[1]) == 0)
	{
		pipes->here_doc = true;
		pipes->cmd = 3;
	}
	else
	{
		pipes->here_doc = false;
		pipes->cmd = 2;
	}
}

void	process(char *argv, char **envp)
{
	char	**command;
	char	*path;

	command = ft_split(argv, ' ');
	if (!command || !command[0])
	{
		free(command);
		perror("Error splitting command");
		exit(2);
	}
	path = search_path(command[0], envp);
	if (!path)
	{
		ft_free(command);
		perror(COMMAND_NOT_FOUND);
		exit(3);
	}
	if (execve(path, command, envp) == -1)
	{
		perror(EXECVE_ERROR);
		ft_free(command);
		free(path);
		exit(4);
	}
}
