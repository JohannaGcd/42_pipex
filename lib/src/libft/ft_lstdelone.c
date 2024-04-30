/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguacide <jguacide@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 10:07:08 by jguacide          #+#    #+#             */
/*   Updated: 2023/11/06 17:06:27 by jguacide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst)
{
	if (lst == NULL)
		return ;
	free (lst);
}

/*
void	del(int content)
{
	free(content);
	return ;  
}

int main(void)
{
	t_list *head;
	t_list *new;
	t_list *temp;
	t_list *to_del;

	int i;
	i = 0;
	head = NULL;
	while (i < 5)
	{
		new = ft_lstnew("Hello");
		ft_lstadd_back(&head, new);
		i++;
	}
	to_del = ft_lstnew("test");
	ft_lstadd_back(&head, to_del);
	temp = head;
	while (temp != NULL)
	{
		printf("%s\n", (char *)(temp->content));
		temp = temp->next;
	}
	ft_lstdelone(to_del, del);	
	temp = head;
	while (temp != NULL)
	{
		printf("%s\n", (char *)(temp->content));
		temp = temp->next;
	}
	ft_lstclear(&head, del);
}*/
