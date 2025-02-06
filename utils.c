/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:22:46 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/02/06 16:08:53 by mmiguelo         ###   ########.fr       */
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

int	parse(char **envp)
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
	return (i);
}
