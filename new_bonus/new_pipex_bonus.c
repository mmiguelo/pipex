/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_pipex_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 21:09:03 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/02/13 21:09:03 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int main(int ac, char **av, char **envp)
{
    t_pipex pipes;

    if (av[1] && (ft_strncmp(av[1], "here_doc", 8) == 0 && ac < 6))
        return (ft_putstr_fd(INPUT_ERROR, 2), 1)
    if (ac < 5)
        return (ft_putstr_fd(INPUT2_ERROR, 2), 2)
    parse_bonus(envp, av);
    if (!pipes.here_doc)
    {

    }
    else
        start_here_doc(&pipes);
}