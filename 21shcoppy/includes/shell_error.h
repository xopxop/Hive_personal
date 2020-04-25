/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_error.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 06:09:01 by dthan             #+#    #+#             */
/*   Updated: 2020/04/07 06:09:02 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_ERROR_H
# define SHELL_ERROR_H
# include <unistd.h>
# include <stdlib.h>
# include "../libft/includes/libft.h"

# define MY_ENOMEM "Out of memory"
# define CD_ENOTDIR "cd: not a directory: "
# define CD_ENOENT "cd: no such file or directory: "
# define CD_EACCES "cd: permission dinied: "
# define CD_EMARG "cd: too many arguments"
# define CD_ENOPWD "cd: string not in pwd: "
# define SYNTAX_UNEXPECTED_TOKEN "21sh: syntax error near unexpected token `"
# define SYNTAX_CMDNF "21sh: command not found : "
# define SHELL_ENOENT "21sh: no such fine or directory: "

void			ft_error_malloc(void);
int	error_monitor(char *first, char *second, char *third, char *fourth, \
					int ret_value, int exit_value);

#endif
