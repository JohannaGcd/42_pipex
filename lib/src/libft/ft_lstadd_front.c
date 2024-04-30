/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguacide <jguacide@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 11:05:16 by jguacide          #+#    #+#             */
/*   Updated: 2023/11/06 16:38:38 by jguacide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *newnode)
{
	if (lst == NULL || newnode == NULL)
		return ;
	newnode->next = *lst;
	*lst = newnode;
}

/*int main(void)
{
	t_list	*head = NULL;
	t_list	*temp;
	int i;
	i = 0;

	while (i < 5)
	{
		temp = ft_lstnew("hello");
		ft_lstadd_front(&head, temp);
		i++;
	}
	temp = head;
	while (temp != NULL)
	{
		printf("%s -", (char *)temp->content);
		temp = temp->next;	
	}
	ft_lstclear(&head, del);
	
	return (0);
}*/
