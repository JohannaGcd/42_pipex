#include "pipex.h"

char *free_double(char **str)
{
	int i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

// TODO: exit or return

// exit or return: anything malloc free in function and exit(x);
// in child : exit(x);
// in main return ;
// in main for pipe: free and exit(x);

// micha suggests: wait free and exit. waits for children, free and exit.


