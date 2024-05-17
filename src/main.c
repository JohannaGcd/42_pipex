/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/30 10:55:50 by jguacide      #+#    #+#                 */
/*   Updated: 2024/05/17 12:25:49 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>

int	main(int argc, char *argv[], char *env[])
{
	char	*first_cmd_path;
	char	**first_cmd = NULL;
	char	*second_cmd_path;
	char	**second_cmd = NULL;
	int		fd[2];
	pid_t	id1;
	int		infile;
	pid_t	id2;
	int		outfile;
	int		status2;
	int		status1;

	// Step 1: get the command and the binary path to execute it (also checks for wrong input)
	if (argc != 5)
		return (write(1, "wrong argument input", 20), 0);
	if (ft_strncmp(argv[2], "", 1) == 0)
	{
		first_cmd[0] = ft_strdup(argv[2]);
		first_cmd[1] = "\0";
	}
	else
	{
		first_cmd = get_cmd(argv[2]);
		if (first_cmd == NULL)
			return (perror("Not a valid command"), EXIT_FAILURE);
	}
	first_cmd_path = get_cmd_path(env, first_cmd[0]);
	if (!first_cmd_path)
	{
		free_double(first_cmd);
		return (perror("Error allocating command path"), EXIT_FAILURE);
	}
	if (ft_strncmp(argv[3], "", 1) == 0)
	{
		second_cmd[0] = ft_strdup(argv[3]);
		second_cmd[1] = "\0";
	}
	else
	{
	    second_cmd = get_cmd(argv[3]);
		if (!second_cmd)
		{
			free_double(first_cmd);
			free(first_cmd_path);
			return (perror("Error allocating command path"), EXIT_FAILURE);
		}
	}
	second_cmd_path = get_cmd_path(env, second_cmd[0]);
	if (!second_cmd_path)
	{
		free_double(first_cmd);
		free(first_cmd_path);
	    free_double(second_cmd);
		return (perror("Error allocating command path"), EXIT_FAILURE);
	}
	// Step 2: create a pipe
	pipe(fd);
	if (pipe(fd) == -1)
		return (perror("Error creating pipe."), EXIT_FAILURE);
	// Step 3: Fork the first child process
	id1 = fork();
	if (id1 == -1)
		return (perror("Error forking child process."), EXIT_FAILURE);
	// Step 4: In the first child process, execute the first command
	if (id1 == 0)
	{
		// In First Child
		// Step 4.1: open the infile
		infile = open(argv[1], O_RDONLY, 0777);
		if (infile == -1)
		{
			free_double(first_cmd);
			free_double(second_cmd);
			free(first_cmd_path);
			free(second_cmd_path);
			return (perror("Error opening file"), EXIT_FAILURE);
		}
		// Step 4.2: use dup2 to redirect reading from STDIN to the infile. To remember: "dup2(int oldfd, int newfd)" -> "I want newfd to point to oldfd"
		if (dup2(infile, STDIN_FILENO) == -1)
			return (perror("Error redirecting STDIN to infile"), EXIT_FAILURE);
		// Step 4.3: likewise, redirect STDOUT to the write-end of the pipe (fd[1])
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			return (perror("Error redirecting pipe to STDOUT"), EXIT_FAILURE);
		// Step 4.4: close all unused fd.
		close(fd[0]);
		close(fd[1]);
		close(infile);
		// Step 4.5: use execve to perform the command.
		free(first_cmd[0]);
		first_cmd[0] = first_cmd_path;
		execve(first_cmd[0], first_cmd, env);
		free_double(first_cmd);
		free_double(second_cmd);
		free(first_cmd_path);
		free(second_cmd_path);
		perror("Error with execve");
		exit(EXIT_FAILURE);
	}
	// Step 5: close the unused fd before forking the second child. Here, second child doesn't need fd[1].
	close(fd[1]);
	// Step 6: Fork the second child
	id2 = fork();
	if (id2 == -1)
		return (perror("Error forking second child process."), 2);
	if (id2 == 0)
	{
		// In Second Child
		// Step 6.1: open the outfile
		outfile = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0777);
		if (outfile == -1)
			return (perror("Error opening outfile"), EXIT_FAILURE);
		// Step 6.2: redirect STDIN to the read-end of the pipe (fd[0])
		if (dup2(fd[0], STDIN_FILENO) == -1)
			return (perror("Error redirecting STDIN to fd[0]"), EXIT_FAILURE);
		// Step 6.3: redirect STDOUT to outfile
		if (dup2(outfile, STDOUT_FILENO) == -1)
			return (perror("Error redirecting STDOUT to outfile"), EXIT_FAILURE);
		// Step 6.4: close unused fd -> thanks to the redirection, execve will use STDOUT to output
		close(fd[0]);
		close(outfile);
		// Step 6.5: use execve to perform the second command.
		free(second_cmd[0]);
		second_cmd[0] = second_cmd_path;
		execve(second_cmd[0], second_cmd, env);
		free_double(second_cmd);
		free_double(first_cmd);
		free(second_cmd_path);
		free(first_cmd_path);
		perror("Error with execve");
		exit(EXIT_FAILURE);
	}
	// In Parent
	// Step 7: Close all remaining file descriptors.
	close(fd[0]);
	// Step 8: Wait for all children to execute, using waitpid for the second child to retrieve it's exit status
	// and wait(NULL) for all other children (ie. first child in this case);
	status2 = 0;
	status1 = 0;
	waitpid(id1, &status1, 0);
	waitpid(id2, &status2, 0);
	// wait(NULL);
	/*int status2 = 0;
	child2ExitStatus = 0;
	//pid_t s_child;
	waitpid(id2, &status2, 0);
	if (WIFEXITED(status2))
	{
		printf("status2 is: %d\n", status2);
		child2ExitStatus = WEXITSTATUS(status2);
		//return (WEXITSTATUS(status2))
		printf("status2 is: %d\n", status2);
		printf("child2ExitStatus is: %d\n", child2ExitStatus);
		//child2ExitStatus = 0;
		ft_printf("Child process terminated normally with exit status : %d\n",
			child2ExitStatus);
	}
	else {
		child2ExitStatus = 127;
		ft_printf("Child process did not terminate normally.\n");
	}*/
	// printf("after NULL %d", child2ExitStatus);
	// return (WEXITSTATUS(status2));
	free_double(first_cmd);
	free_double(second_cmd);
	free(first_cmd_path);
	free(second_cmd_path);
	return (check_status(status2));
}
