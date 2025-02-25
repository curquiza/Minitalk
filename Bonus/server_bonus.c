/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmanolis <tmanolis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 15:45:57 by tmanolis          #+#    #+#             */
/*   Updated: 2021/09/17 15:32:34 by tmanolis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static size_t	len;

void	print_pid(void)
{
	int pid;
	
	pid = getpid();
	if (pid != -1)
	{
		ft_putstr_fd("PID : ", 1);
		ft_putnbr_fd(pid, 1);
		ft_putchar_fd('\n', 1);
	}
	else
		ft_putstr_fd("Couldn't get the PID\n", 2);
}

void	convert_bits_to_char(char *stock)
{
	int				i;
	unsigned char	c;
	unsigned char	temp;

	i = 7;
	c = 0;
	while(i >= 0)
	{
		temp = 1;
		if (stock[i] == '1')
		{
				temp <<= (7 - i);
				c |= temp;
		}
		i--;
	}
	free(stock);
	ft_putchar_fd(c, 1);
}

void	ft_handler(int signum)
{
	char	*stock;

	if (len == 0)
		stock = ft_initialize();
	if (signum == SIGUSR1)
		stock[len] = '1';
	else if (signum == SIGUSR2)
		stock[len] = '0';
	len++;
	if (len == 8)
	{
		stock[len] = '\0';
		convert_bits_to_char(stock);
		len = 0;
	}
}

int		main(void)
{
	struct	sigaction sa;

	len = 0;
	sa.sa_handler = ft_handler;
	sa.sa_flags = 0;
	print_pid();
	while (1)
	{
		if (sigaction(SIGUSR1, &sa, NULL) == -1)
			ft_putstr_fd("Couldn't get the signal\n", 2);
		if (sigaction(SIGUSR2, &sa, NULL) == -1)
			ft_putstr_fd("Couldn't get the signal\n", 2);
		pause();
	}
	return (0);
}
