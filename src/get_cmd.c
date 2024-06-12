/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguacide <jguacide@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:36:01 by jguacide          #+#    #+#             */
/*   Updated: 2024/06/12 13:09:59 by jguacide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// METHOD:
// The function retrieve_commands retrieves the commands inputed via argv.
// Step by step process:
// 1. get_cmd initializes a double array with the command and flags
// 2. get_env_path loops through env until it finds the PATH substring
// 3. split PATH into a double array with each binary path
// 4. get_cmd_path 1.checks for direct paths first, 2.otherwise it loops through
// the double array path_dir (ie. splitted PATH) 3. it calls on format_bin_path
// to add "/ + cmd[0]" at the end of the binary path 4. then it tests the path
// using the function access.
char	**retrieve_cmds(char *argv, char *env[])
{
	char	**cmd;
	char	*env_path;
	char	*cmd_path;
	char	**path_substr;

	cmd = get_cmd(argv);
	if (!cmd)
		return (NULL);
	env_path = get_env_path(env);
	if (!env_path)
		return (free_double(cmd), NULL);
	path_substr = ft_split(env_path, ':');
	if (!path_substr)
	{
		free_double(cmd);
		return (free (env_path), NULL);
	}
	cmd_path = get_cmd_path(path_substr, cmd[0]);
	if (!cmd_path)
	{
		free_double(cmd);
		free_double(path_substr);
		return (free(env_path), NULL);
	}
	free_double(path_substr);
	free(cmd[0]);
	cmd[0] = cmd_path;
	return (cmd);
}

char	**get_cmd(char *str)
{
	int		i;
	char	**cmd;

	if (!str)
		return (perror("empty cmd"), NULL);
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

char	*get_cmd_path(char **path_dir, char *cmd)
{
	int		i;
	char	*full_cmd_path;
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
				return (free(path_dir), NULL);
			if (access(full_path, X_OK) == 0)
				return (full_path);
			free(full_path);
			i++;
		}
	}
	return (ft_strdup(cmd));
}

char	*check_direct_paths(char *cmd)
{
	if (cmd[0] == '/'
		|| cmd[0] == '.'
		|| cmd[0] == '~')
		return (ft_strdup(cmd));
	return (NULL);
}

char	*format_bin_path(char *path_dir, char *cmd)
{
	char	*formatted_path;
	char	*step1_path;

	step1_path = ft_strjoin(path_dir, "/");
	if (!step1_path)
		return (NULL);
	formatted_path = ft_strjoin(step1_path, &cmd[0]);
	if (!formatted_path)
		return (free(step1_path), NULL);
	return (free(step1_path), formatted_path);
}
