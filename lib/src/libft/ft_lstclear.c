/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/29 12:09:49 by jguacide      #+#    #+#                 */
/*   Updated: 2023/11/06 17:09:48 by jguacide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst)
{
	t_list	*current;
	t_list	*next;

	current = *lst;
	if (lst == NULL || *lst == NULL)
		return ;
	while (current != NULL)
	{
		next = current->next;
		current->content = 0;
		free(current);
		current = next;
	}
	*lst = NULL;
}
/*
void	del(void *ptr)
{
	t_list	*head;
	t_list	*new;
	t_list	*temp;
	int		i;

	ptr = NULL;
	return ;
}*/
/*
int	main(void)
{
	i = 0;
	head = NULL;
	while (i < 5)
	{
		new = ft_lstnew("hello");
		ft_lstadd_back(&head, new);
		i++;
	}
	temp = head;
	while (temp != NULL)
	{
		printf("%s\n", (char *)temp->content);
		temp = temp->next;
	}
	ft_lstclear(&(head->next->next), del);
	temp = head;
	while (temp != NULL)
	{
		printf("Second:%s\n", (char *)temp->content);
		temp = temp->next;
	}
}
*/
