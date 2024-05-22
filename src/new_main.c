#include "pipex.h"

MAIN : 1. check input argc check_commands(use it twice, with argv[2],
	and argv[3])

	2. create pipe

	3. call fork id1 if id1 = 0 execute child function
		/ in child : open the infile;

4. call fork id2 
	idem

5. wait for children

int	main(int argc, char *argv[], char *env[])
{
	if (argc != 5)
		return (ft_printf("Input format: program infile cmd cmd outfile\n"));

	t_generic_data *pipex_data = calloc(sizeof(t_generic_data));
	t_generic_data->first_cmd = retrieve_commands(argv, env);
}