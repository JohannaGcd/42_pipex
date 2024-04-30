/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguacide <jguacide@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 11:49:22 by jguacide          #+#    #+#             */
/*   Updated: 2023/11/06 16:38:09 by jguacide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *newnode)
{
	t_list	*temp;

	temp = *lst;
	if (newnode == NULL)
		return ;
	if (lst == NULL || *lst == NULL)
	{
		*lst = newnode;
		return ;
	}
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = newnode;
}

/*int main(void)
{
	t_list *head;
	t_list *populate;
 	t_list *new;
	int i;
	i = 0;
	
	head = NULL;	
	while (i < 4)
	{
		populate = ft_lstnew("hello");
		ft_lstadd_front(&head, populate);
		i++;
	}
	new = ft_lstnew("HI!");
	ft_lstadd_back(&head, new);

	t_list *temp = head;
	while (temp != NULL)
	
		printf("%s \n", (char *)temp->content);
		temp = temp->next;
	}
	ft_lstclear(&head, del);
	return (0);
}*/
