/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:22:46 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/02/06 11:38:28 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free(char **str)
{
	while (*str)
		free(*str++);
	free(str);
}

void	parse(char **envp)
{
	if (!envp || !*envp)
	{
		ft_putstr_fd(ENVP_ERROR, 2);
		exit(1);
	}
	while (*envp && ft_strnstr(*envp, "PATH=", 5) == 0)
		envp++;
	if (!*envp)
	{
		ft_putstr_fd(PATH_ERROR, 2);
		exit(2);
	}
}