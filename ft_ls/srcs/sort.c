/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/16 22:01:27 by dthan             #+#    #+#             */
/*   Updated: 2020/03/16 22:01:28 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int     cmp(t_stat file1, t_stat file2)
{
    return (ft_strcmp(file1.name, file2.name) > 0);
}

void    ft_swap_stat(t_stat *file1, t_stat *file2)
{
    t_stat temp;
    temp.name = file1->name;
    temp.path = file1->path;
    temp.user_name = file1->user_name;
    temp.group_name = file1->group_name;
    temp.link = file1->link;
    temp.size = file1->size;
    temp.time = file1->time;
    temp.file_permission = file1->file_permission;
    temp.type = file1->type;
    temp.is_hidden = file1->is_hidden;
    temp.allow_open = file1->allow_open;
    temp.blocks = file1->blocks;

    file1->name = file2->name;
    file1->path = file2->path;
    file1->user_name = file2->user_name;
    file1->group_name = file2->group_name;
    file1->link = file2->link;
    file1->size = file2->size;
    file1->file_permission = file2->file_permission;
    file1->type = file2->type;
    file1->is_hidden = file2->is_hidden;
    file1->allow_open = file2->allow_open;
    file1->blocks = file2->blocks;

    file2->name = temp.name;
    file2->path = temp.path;
    file2->user_name = temp.user_name;
    file2->group_name = temp.group_name;
    file2->link = temp.link;
    file2->size = temp.size;
    file2->file_permission = temp.file_permission;
    file2->type = temp.type;
    file2->is_hidden = temp.is_hidden;
    file2->allow_open = temp.allow_open;
    file2->blocks = temp.blocks;
}

void    ft_sort_alphabet(t_node *lst)
{
    int is_in_order;
    t_node *ptr;

    is_in_order = NO;
    while(is_in_order == NO && (lst))
    {
        ptr = lst;
        is_in_order = YES;
        while (ptr->next)
        {
            if (cmp(ptr->status, ptr->next->status))
            {
                ft_swap_stat(&ptr->status, &ptr->next->status);
                is_in_order = NO;
            }
            ptr = ptr->next;
        }
    }
}

void ft_sort(t_node *lst, int options)
{
    (void)options;
    ft_sort_alphabet(lst);
}