/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguacide <jguacide@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 09:28:10 by jguacide          #+#    #+#             */
/*   Updated: 2023/11/06 17:41:51 by jguacide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*temp;
	void	*ptr;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	new_lst = NULL;
	while (lst != NULL)
	{
		ptr = f(lst->content);
		temp = ft_lstnew(ptr);
		if (temp == NULL)
		{
			ft_lstclear(&new_lst, del);
			del(ptr);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, temp);
		lst = lst->next;
	}
	return (new_lst);
}
/*
void	*f(void *ptr)
{
		char *c;

		c = ptr;
		*c = 'T';
		return ((void *)c);
}

void	del(void *ptr)
{
		ptr = NULL;
		return ;
}

int	main(void)
{
		t_list *head;
		t_list *new;
		t_list *current;
		int i = 0;
		t_list *copy;

		char    str[] = "Hello";
		char    str1[] = "Hello";
		char    str2[] = "Hello";
		char    str3[] = "Hello";
		char    str4[] = "Hello";

		head = NULL;
		new = ft_lstnew(str);
		ft_lstadd_back(&head, new);
		new = ft_lstnew(str1);
		ft_lstadd_back(&head, new);
		new = ft_lstnew(str2);
		ft_lstadd_back(&head, new);
		new = ft_lstnew(str3);
		ft_lstadd_back(&head, new);
		new = ft_lstnew(str4);
		ft_lstadd_back(&head, new);
		current = head;
		while (current != NULL)
		{
				printf("Before: %s\n", (char *)current->content);
				current = current->next;
		}
		copy = ft_lstmap(head, f, del);

		current = head;
		while (current != NULL)
		{
				printf("After: %s\n", (char *)current->content);
				current = current->next;
		}
		ft_lstclear(&copy, dle)
		ft_lstclear(&head, del);
		return (0);
}*/
