/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 08:26:23 by dthan             #+#    #+#             */
/*   Updated: 2020/05/22 17:31:54 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

int			char_to_term(int c)
{
	return (write(STDERR_FILENO, &c, 1));
}

static void	ft_print_output(t_lst *lst, t_terminal term, int width_col)
{
	int		i;
	int		j;
	t_lst	*current;

	i = -1;
	j = 0;
	while (++i < term.rows && lst != NULL)
	{
		j = -1;
		while (++j < term.cols && lst != NULL)
		{
			if (lst->elem.position == true)
				ft_dprintf(STDERR_FILENO, "%s", tgetstr("us", NULL));
			if (lst->elem.selected == true)
				ft_dprintf(STDERR_FILENO, "%s", tgetstr("so", NULL));
			ft_dprintf(STDERR_FILENO, "%s%*s", lst->elem.av, width_col - \
												lst->elem.max_length, "");
			if (lst->elem.position == true)
				ft_dprintf(STDERR_FILENO, "%s", tgetstr("ue", NULL));
			if (lst->elem.selected == true)
				ft_dprintf(STDERR_FILENO, "%s", tgetstr("se", NULL));
			lst = lst->next;
		}
		ft_putchar_fd('\n', STDERR_FILENO);
	}
}

void		ft_display(t_select *select)
{
	struct winsize	w;
	int				input_size;
	int				width_col;

	if (select->head == NULL)
	{
		tputs(tgetstr("cl", NULL), 1, char_to_term);
		exit(EXIT_SUCCESS);
	}
	tputs(tgetstr("cl", NULL), 1, char_to_term);
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	input_size = ft_count_elems(select->head);
	width_col = (ft_finding_longest_elem(select->head) + 1);
	select->term.cols = w.ws_col / width_col;
	select->term.rows = (input_size == select->term.cols) ? 1 : \
								(input_size / select->term.cols) + 1;
	if (select->term.rows > w.ws_row)
		return ;
	ft_print_output(select->head, select->term, width_col);
}
