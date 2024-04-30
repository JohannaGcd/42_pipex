/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstlast.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/28 11:39:46 by jguacide      #+#    #+#                 */
/*   Updated: 2023/11/03 16:36:52 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*current;

	current = lst;
	if (current == NULL)
		return (NULL);
	while (current->next)
		current = current->next;
	return (current);
}

/*int	main(void)
{
	t_list	*head;
	t_list	*new;
	int		i;
	t_list	*temp;
	char	*last;

	i = 0;
	head = NULL;
	while (i < 5)
	{
		new = ft_lstnew("hello");
		ft_lstadd_front(&head, new);
		i++;
	}
	new = ft_lstnew("last");
	ft_lstadd_back(&head, new);
	// temp = head;
	temp = ft_lstlast(head);
	// while (temp != NULL)
	// {
	// 	printf("%s\n", (char *)temp->content);
	// 	temp = temp->next;
	// }
	printf("Answer: %s\n", (char *)(temp->content));
	ft_lstclear(&head, del);
	return (0);
}*/
