#include "pipex.h"

// METHOD:
// The function retrieve_commands retrieves the commands inputed via argv.
// Step by step process:
// 1. get_cmd initializes a double array with the command and flags
// 2. get_env_path loops through env until it finds the PATH substring
// 3. format_path splits PATH into a double array with each binary path
// 4. get_cmd_path 1.checks for direct paths first, 2.otherwise it loops through
// the double array path_dir (ie. splitted PATH) 3. it calls on format_bin_path
// to add "/ + cmd[0]" at the end of the binary path 4. then it tests the path
// using the function access.

char	**retrieve_commands(char *argv[], char *env[])
{
	char	**cmd;
	char	*env_path;
	char	*cmd_path;
	char	*cmd_path_step1;

	cmd = get_cmd(argv[3]);
	env_path = get_env_path(env);
	if (!env_path)
		return (free_double(cmd), NULL);
	cmd_path_step1 = format_env_path(env_path, cmd[0]);
	if (!cmd_path_step1)
	{
		free_double(cmd);
		free(env_path);
		return (NULL);
	}
	cmd_path = get_cmd_path(env_path, cmd[0]);
	if (!cmd_path)
	{
		free_double(cmd);
		free(env_path);
		free(cmd_path_step1);
		return (NULL);
	}
	free(cmd[0]);
	cmd[0] = cmd_path;
	return (cmd);
}

char	**get_cmd(char *str)
{
	int		i;
	char	**cmd;

	if (!str)
		return (perror("permission denied"), NULL);
	i = 0;
	cmd = ft_split(str, ' ');
	if (!cmd)
		return (NULL);
	return (cmd);
}

char	*get_env_path(char *env[])
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (env[i]);
		i++;
	}
	return (NULL);
}

char	*format_env_path(char *path, char *cmd)
{
	char	**path_dir;

	path_dir = ft_split(path, ':');
	if (!path_dir)
	{
		free_double(path_dir);
		return (perror("Error split PATH"), NULL);
	}
	return (path_dir);
}

char	*get_cmd_path(char **path_dir, char *cmd)
{
	char	*full_cmd_path;
	char	*step1_path;
	int		i;
	char	*full_path;

	full_cmd_path = check_direct_paths(cmd);
	if (full_cmd_path)
		return (full_cmd_path);
	else
	{
		i = 0;
		while (path_dir[i])
		{
			full_path = format_bin_path(path_dir[i], cmd);
			if (!full_path)
				return (NULL);
			if (access(full_path, X_OK) == 0)
				return (full_path);
			free(full_path);
			i++;
		}
		free(full_path);
	}
	return (ft_strdup(cmd));
}

char	*check_direct_paths(char *cmd)
{
	if (ft_strncmp(cmd, "/", 1) == 0)
	{
		free_double(path_dir);
		return (ft_strdup(cmd));
	}
	if (ft_strncmp(cmd, "./", 2) == 0)
	{
		free_double(path_dir);
		return (ft_strdup(cmd));
	}
	if (ft_strncmp(cmd, "../", 3) == 0)
	{
		free_double(path_dir);
		return (ft_strdup(cmd));
	}
	return (NULL);
}

char	*format_bin_path(char *path_dir, char *cmd)
{
	char *formatted_path;
	char *step1_path;

	step1_path = ft_strjoin(dir, "/");
	if (!step1_path)
		return (free_double(path_dir), NULL);
	formatted_path = ft_strjoin(step1_path, &cmd[0]);
	if (!formatted_path)
	{
		free(step1_path);
		return (free_double(path_dir), NULL);
	}
	return (formatted_path);
}