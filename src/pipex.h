#ifndef PIPEX
# define PIPEX

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>


# include "../lib/src/ft_printf/ft_printf.h"
# include "../lib/src/get_next_line/get_next_line.h"
# include "../lib/src/libft/libft.h"

// pipex.c


// get_cmd.c

char *get_cmd_path(char *env[], char *cmd);
char **get_cmd(char *str);

// pipex_utils.c
char *free_double(char **str);

#endif
