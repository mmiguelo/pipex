/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 19:03:29 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/02/06 12:50:33 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h> // variadic
# include <unistd.h> // write
# include <stdio.h> // test printf
# include <stdlib.h> //free malloc
# include "../../includes/libft.h"

int	ft_printf(const char *str, ...);
int	ft_putchar(char c);
int	ft_putstr(char *str);
int	ft_putnbr(int n);
int	ft_puthex(unsigned int n, char c);
int	ft_putptr(void *n);
int	ft_pututoa(unsigned int n);

#endif
