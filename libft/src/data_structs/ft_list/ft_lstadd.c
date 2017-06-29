/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 17:22:56 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/21 16:47:54 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dstruct/ftlist.h>

void	ft_lstadd(t_list **alst, t_list *new)
{
	new->next = *alst;
	*alst = new;
}
