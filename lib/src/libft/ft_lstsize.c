/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguacide <jguacide@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 11:12:42 by jguacide          #+#    #+#             */
/*   Updated: 2023/10/31 13:58:08 by jguacide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*current;

	if (lst == NULL)
		return (0);
	current = lst;
	i = 1;
	while (current->next != NULL)
	{
		i++;
		current = current->next;
	}
	return (i);
}

/*
int main(void)
{

	t_list *head;
	t_list *new;
	int i;

	head = NULL;
	i = 0;
	while (i < 10)
	{
		new = ft_lstnew("hello");
		ft_lstadd_back(&head, new);
		i++;
	}
	int size;
	size = ft_lstsize(head);
	
	i = 0;
	t_list *temp;

	temp = head;
	while (temp != NULL)
	{
		printf("%s\n", (char *)temp->content);
		temp = temp->next;
	}
	printf("%d", size);
	ft_lstclear(&head, del);	
	return (0);
}
*/
