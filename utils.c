/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:22:46 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/02/06 17:44:26 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int	parse(char **envp, char **argv)
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
	i = 0;
	if (!argv[2] || (argv[2] && !argv[2][0])
			|| !argv[3] || (argv[3] && !argv[3][0]))
	{
		ft_putstr_fd("Wrong input. Try ./pipex file1 cmd1 cmd2 file2\n", 2);
		exit(3);
	}
	return (i);
}
