/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:54:28 by whan              #+#    #+#             */
/*   Updated: 2020/11/02 15:48:37 by whan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*free)(void *))
{
	t_list **pp;
	t_list *temp;

	pp = lst;
	if (!lst)
		return ;
	while (*pp)
	{
		temp = (*pp)->next;
		free((*pp)->content);
		free(*pp);
		*pp = temp;
	}
}
