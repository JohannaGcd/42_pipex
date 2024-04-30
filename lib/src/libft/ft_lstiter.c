/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguacide <jguacide@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 11:59:20 by jguacide          #+#    #+#             */
/*   Updated: 2023/10/31 13:32:38 by jguacide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(int))
{
	t_list	*current;

	if (lst == NULL || f == NULL)
		return ;
	current = lst;
	while (current != NULL)
	{
		f(current->content);
		current = current->next;
	}
}
/*
void	f(void *ptr)
{
	char *c;
	c = (char *)ptr;
	*c = 'T';

}

int main(void)
{
	t_list *head;
	t_list *new;
	int i = 0;
	t_list *temp;
	char	str[] = "Hello";
	char	str1[] = "Hello";
	char	str2[] = "Hello";
	char	str3[] = "Hello";
	char	str4[] = "Hello";

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

	temp = head;
	while (temp != NULL)	
	{
		printf("%s\n", (char *)temp->content);
		temp = temp->next;
	}
	temp = head;
	ft_lstiter(temp, f);
	while (temp != NULL)	
	{
		printf("%s\n", (char *)temp->content);
		temp = temp->next;
	}
	ft_lstclear(&head, del)
	return (0);
}
*/
