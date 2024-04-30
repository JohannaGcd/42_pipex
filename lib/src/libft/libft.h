/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 11:30:50 by jguacide      #+#    #+#                 */
/*   Updated: 2023/11/03 16:28:04 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

// Libraries
# include <bsd/string.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// PART 1 - Libc functions
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
size_t				ft_strlen(const char *s);
void				*ft_memset(void *s, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
int					ft_atoi(const char *nptr);
void				*ft_calloc(size_t nmemb, size_t size);
char				*ft_strdup(const char *s);

// PART 2 - Additional functions

char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);

// BONUS

typedef struct s_list
{
	int				content; // the number to sort
	int				index; // the number's positon in the stack
	int				push_cost; // how many commands in total
	bool			above_middle; // used to calculate the push_cost
	bool			cheapest; // the node that is cheapest to move
	struct s_list	*target_node; // the target node in the opposite stack
	struct s_list	*next; // pointer to the next node
}					t_list;

t_list				*ft_lstnew(int content);
void				ft_lstadd_front(t_list **lst, t_list *newnode);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lt);
void				ft_lstadd_back(t_list **lst, t_list *newnode);
void				ft_lstdelone(t_list *lst);
void				ft_lstclear(t_list **lst);
//void				ft_lstiter(t_list *lst, void (*f)(void *));
//t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
//						void (*del)(void *));

#endif
