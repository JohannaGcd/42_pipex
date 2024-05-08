#include "pipex.h"

// This function takes the env and cmd double arrays
// finds and returns the correct binary path (if it exists)
char *get_cmd_path(char *env[], char **cmd)
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
	//TODO: protect split

	// Step 3: test the command with each substring to find the right binary path
	// -> note: first add "/" before joining potential path with the cmd 
	i = 0;
	while (path_dir[i] != NULL)
	{
		char *dir = path_dir[i];
		char *step1_path = ft_strjoin(dir, "/");
		if (!step1_path)
		{
			printf("error with first strjoin.");
			ft_free(path_dir); // TODO: see above, check ft_Free -> not sure it frees all the date inside
			return (NULL);
		}
		char *full_path = ft_strjoin(step1_path, cmd[0]); //TODO:protect strjoin
		if (access(full_path, X_OK) == 0)
		{
			ft_free(path_dir);
			return (full_path);
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
	// TODO: check how I can free split, doesn't seem to free all date inside but just to free the double pointer
	// TODO: protect function: what if str is empty?
	// TODO: is it here if i check whether it is a real command or not?
	
}





