/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgurova <dariagurova91@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 18:46:02 by dgurova           #+#    #+#             */
/*   Updated: 2017/12/22 13:51:53 by dgurova          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int		ft_abs(int nb)
{
	unsigned int nbr;

	nbr = (nb < 0) ? (unsigned int)-nb : nb;
	return (nbr);
}
