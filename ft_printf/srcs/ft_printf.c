/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 23:46:29 by dthan             #+#    #+#             */
/*   Updated: 2019/12/05 23:54:20 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	printf(const char *format, ...)
{
	va_list arg;
	int i;
	int count_byte;

	va_start(arg, format);
	i = 0;
	count_byte = 0;
	while(format[i++] != '\0')
		if (format[i++] == '%')
		{
			count_byte++;
//			parse_and_print(arg, format, i);
		}
		else
		{
			ft_putchar(format[i]);
			count_byte++;
		}
	va_end(arg);
	return (count_byte);
}
