/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_p.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 04:07:20 by dthan             #+#    #+#             */
/*   Updated: 2020/01/06 21:16:10 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"
#define HEX_MASK 15
#define SHIFF_HEX_MASK 4
#define MAX_HEX_STRLEN 17

/*
** This ft will taking care of type pointer
** Getting the adress from the argument then put it in an unsigned long long
** interger
** Convered the number into a string with ft_number_conversion, using the
** mask to get the hex value
** Ft_percison_hex to deal with the precision
** Ft_pd_handle to deal with the padding
*/

void	type_p(t_info *info, va_list arg, size_t *ct)
{
	unsigned long long	num;
	char				*str;
	char				*hex;

	hex = "0123456789abcdef";
	num = (long long)va_arg(arg, long long);
	if (num == 0)
	{
		str = ft_strnew(5);
		str = "(nil)";
	}
	else
		str = ft_number_conversion(num, HEX_MASK, SHIFF_HEX_MASK, \
			MAX_HEX_STRLEN, hex);
	ft_percision_hex(info, &str);
	ft_pad_handle(info, &str);
	write(STDOUT, str, *ct = ft_strlen(str));
	free(str);
}
