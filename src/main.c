#include "pipex.h"

// METHOD:
// Step 1: Main initializes an array to store the id of each child;
// and an array to store the file descriptors for the pipe.
// Step 2: Checks if argc isn't 5
// Step 3: Executes the first fork, stores in id_array[0];
// if id_array[0] == 0 -> Executes the first child
// Step 4: Executes the second fork, stores in id_array[1];
// if id_array[1] == 0 -> Executes the second child
// Step 5: Executes wait_for_children,
// which calls waitpid for both and returns the exit status
// of the second child.
int	main(int argc, char *argv[], char *env[])
{
	pid_t id_array[2];
	int fd[2];

	if (argc != 5)
		return (ft_printf("Input format: program infile cmd cmd outfile\n"));
	if (pipe(fd) == -1)
		return (perror("Error creating pipe."), EXIT_FAILURE);
	id_array[0] = fork();
	if (id_array[0] == -1)
		return (perror("Error forking second child process."), EXIT_FAILURE);
	if (id_array[0] == 0)
		execute_child(argv, fd, env, 1);
	id_array[1] = fork();
	if (id_array[1] == -1)
		return (perror("Error forking second child process."), EXIT_FAILURE);
	close(fd[1]);
	if (id_array[1] == 0)
		execute_child(argv, fd, env, 2);
	return (wait_for_children(id_array[0], id_array[1], fd));
}
