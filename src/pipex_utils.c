#include "pipex.h"
#include <stdlib.h>

char	*free_double(char **str)
{
	int	i;

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

int	wait_for_children(pid_t id1, pid_t id2, int fd[])
{
	int	status1;
	int	status2;

	close(fd[0]);
	close(fd[1]);

	waitpid(id1, &status1, 0); // can i send NULL instead of status1?
	waitpid(id2, &status2, 0);
	return (check_status(status2));
}

int	check_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (127);
}
