/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchadwic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 18:50:31 by cchadwic          #+#    #+#             */
/*   Updated: 2019/09/12 18:34:36 by cchadwic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

static int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || \
			c == '\r');
}

int			ft_atoi(const char *str)
{
	size_t				i;
	unsigned long int	res;
	int					sign;

	i = 0;
	res = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if ((res > 922337203685477580 || (res == 922337203685477580
						&& (str[i] - '0') > 7)) && sign == 1)
			return (-1);
		else if ((res > 922337203685477580 || (res == 922337203685477580
						&& (str[i] - '0') > 8)) && sign == -1)
			return (0);
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return ((int)(res * sign));
}
