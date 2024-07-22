/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguacide <jguacide@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:36:38 by jguacide          #+#    #+#             */
/*   Updated: 2024/07/22 15:53:16 by jguacide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../lib/src/ft_printf/ft_printf.h"
# include "../lib/src/get_next_line/get_next_line.h"
# include "../lib/src/libft/libft.h"
# include <errno.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

# define EXIT_FAILURE 1

// execute_child.c
int		open_file(char *file, size_t child_i);
int		execute_child(char *argv[], int fd[], char *env[], size_t child);
int		set_in_and_out(char *argv[], int pipe[], size_t child_i);
int		redirect_fds(int read_end, int write_end);
int		close_pipes(size_t child_i, int pipe[]);

// get_cmd.c
char	**retrieve_cmds(char *argv, char *env[]);
char	**retrieve_env_path(char *env[]);
char	*get_cmd_path(char *env[], char *cmd);
char	**get_cmd(char *str);
char	*get_env_path(char *env[]);
char	*check_direct_paths(char *cmd);
char	*format_bin_path(char *path_dir, char *cmd);

// pipex_utils.c
char	*free_double(char **str);
int		open_file(char *file, size_t child_i);
int		set_in_and_out(char **argv, int pipe[], size_t child_i);
int		wait_for_children(pid_t id1, pid_t id2, int fd[]);
int		check_status(int status);

#endif
