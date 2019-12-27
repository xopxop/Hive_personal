/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_s.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 04:34:28 by dthan             #+#    #+#             */
/*   Updated: 2019/12/23 04:34:38 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

/*
** ft printing for type_s
** RETURN VALUE: a string for type_s
*/

void    type_s(t_info *info, va_list arg, char **output)
{
    char *ctemp;
    char *str;

    ctemp = va_arg(arg, char*);
    str = ft_strdup(ctemp);
    ft_prec_handle(info, &str);
    ft_pad_handle(info, &str);
    *output = str;
}
