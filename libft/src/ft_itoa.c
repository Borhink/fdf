/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 12:22:07 by qhonore           #+#    #+#             */
/*   Updated: 2015/12/12 14:20:56 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	intlen(int n)
{
	int		len;

	len = 0;
	while (n >= 10)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static int	neg_to_pos(int *n)
{
	if (*n < 0)
	{
		*n = -(*n);
		return (1);
	}
	else
		return (0);
}

static char	*expected_return(void)
{
	char	*str;

	str = (char*)malloc(sizeof(char) * 12);
	if (!str)
		return (NULL);
	str[0] = '-';
	str[1] = '\0';
	ft_strcat(str, ft_itoa(214748364));
	str[10] = '8';
	str[11] = '\0';
	return (str);
}

static int	div_maker(int len)
{
	int		div;

	div = 1;
	while (len--)
	{
		div *= 10;
	}
	return (div);
}

char		*ft_itoa(int n)
{
	int		i;
	int		neg;
	int		len;
	int		div;
	char	*str;

	i = 0;
	if (n == -2147483648)
		return (expected_return());
	neg = neg_to_pos(&n);
	len = intlen(n);
	if (!(str = (char*)malloc(sizeof(char) * (len + neg + 2))))
		return (NULL);
	if (neg)
		str[i++] = '-';
	div = div_maker(len);
	while (div)
	{
		str[i++] = ((n / div) % 10) + 48;
		div /= 10;
	}
	str[i] = '\0';
	return (str);
}
