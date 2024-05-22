#ifndef PIPEX
# define PIPEX

# include "../lib/src/ft_printf/ft_printf.h"
# include "../lib/src/get_next_line/get_next_line.h"
# include "../lib/src/libft/libft.h"
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

// pipex.c

// get_cmd.c

char		*get_cmd_path(char *env[], char *cmd);
char		**get_cmd(char *str);

// pipex_utils.c
char		*free_double(char **str);
int			check_status(int status);

typedef struct s_generic_data
{
	int		fd[2];
	int		infile;
	int		outfile;
	char	**argv;
	char	**env;
	char	**first_cmd;
	char	**second_cmd;
}			t_generic_data;

#endif
