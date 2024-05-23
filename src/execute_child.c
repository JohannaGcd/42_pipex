#include "pipex.h"

// METHOD:
// This function executes the child process specified.
// Step 1: retrieves the command given, using argv
// Step 2: set_in_and_out opens the files specified & redirects the fd
// Step 3: executes the command
// Step 4: if execve fails, exits with error code.
int	execute_child(char *argv[], int fd[], char *env[], size_t child)
{
	char	**cmd_child;

	cmd_child = retrieve_cmds(cmd, env); // toprotect
	if (!cmd_child)
	{
		return
	}
	if (set_in_and_out(argv, fd, 1) == 1)
		return (perror("Error redirecting input/output"), EXIT_FAILURE);
	execve(cmd_child[0], cmd_child, env);
	perror("Error with execve");
	if (errno == ENOENT)
		exit(127);
	exit(EXIT_FAILURE);
}

int	open_file(char *file, size_t child_i)
{
	int	fd;

	if (child_i == 1)
	{
		fd = open(file, O_RDONLY, 0777);
		// Protect
		return (fd);
	}
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	// protect
	return (fd);
}

// protect & close unused fd
int	set_in_and_out(char **argv, int pipe[], size_t child_i)
{
	int read_end;
	int write_end;

	if (child_i == 1)
	{
		read_end = open_file(argv[1]);
		write_end = pipe[1];
		close(pipe[0]);
	}
	read_end = pipe[0];
	write_end = open_file(argv[4], 1);
	close(pipe[1]);
	write_end = get_write_end(char *file, pipe[1], child_i);
	// protect
	if (dup2(read_end, STDIN_FILENO) == -1)
		return (perror("Error redirecting STDIN to infile"), EXIT_FAILURE);
	if (dup2(write_end, STDOUT_FILENO) == -1)
		return (perror("Error redirecting pipe to STDOUT"), EXIT_FAILURE);
	return (0);
}