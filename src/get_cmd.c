#include "pipex.h"

// This function takes the env and cmd double arrays
// finds and returns the correct binary path (if it exists)
char *get_cmd_path(char *env[], char *cmd)
{
	// Step 1: loop through env[][], find PATH substring
	int i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			break;
		i++;
	}
	// Step 2: skip "PATH=" and split the substring
	char *PATH = env[i] + 5;
	char **path_dir = ft_split(PATH, ':');
	if (!path_dir)
		free_double(path_dir);
	// TODO: Split lines 14 -> here in another function (to avoid repeating this step twice) and give the path dir as input to this function

	
	// Step X: check if it's a relative or absolute path -> "./pipex" or "/bin/ls"
	if (ft_strncmp(cmd, "/", 1) == 0)
		return (ft_strdup(cmd));
	if (ft_strncmp(cmd, "./", 2) == 0)
		return (ft_strdup(cmd));
	if (ft_strncmp(cmd, "../", 3) == 0)
		return (ft_strdup(cmd));
	// Step 3: test the command with each substring to find the right binary path
	// -> note: first add "/" before joining potential path with the cmd 
	i = 0;
	char *error_message;
	while (path_dir[i] != NULL)
	{
		char *dir = path_dir[i];
		char *step1_path = ft_strjoin(dir, "/");
		if (!step1_path)
		{
			printf("error with first strjoin.");
			free_double(path_dir); 
			return (NULL);
		}
		char *full_path = ft_strjoin(step1_path, &cmd[0]);
		if (!full_path)
		{
			free_double(path_dir);
			free(step1_path);
			return (NULL);
		}
		if (access(full_path, X_OK) == 0)
		{
			free_double(path_dir);
			free(step1_path);
			return (full_path);
		}
		else 
		{
			if (errno == ENOENT)
				return (perror("File or directory does not exist.\n"), NULL);
			else if (errno == EACCES)
				return (perror("Access denied.\n"), NULL);
			else
			{
				error_message = strerror(errno);
				return (error_message); 
			}
		}
		free(full_path);
		i++;
	}	
	ft_free(path_dir);
	return (NULL);
}

// This function gets the complete command and potential argument from argv
// and transforms it into a double array
// (ie -> "ls -la" become double array with "ls" and "-la")
// TODO: maybe split cmd's in childprocesses because not needed by parent and by other child
char **get_cmd(char *str)
{
	int i;
	char **cmd;
	
	i = 0;
	cmd = ft_split(str, ' ');
	if (!cmd)
	{
		ft_free(cmd); 
	}
	return (cmd);
}





