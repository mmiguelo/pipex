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