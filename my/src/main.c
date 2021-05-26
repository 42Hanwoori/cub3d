#include "cub3d.h"

int		main(int argc, char **argv)
{
	t_set	set;

	if (argc < 2 || !check_extension(argv[1], ".cub"))
		return (exit_error(&set));
	else if (!set_information(&set, argv[1]))
		return (exit_error(&set));
	if (argc == 3 && !ft_strcmp(argv[2], "--save"))
		return (process_bmp(&set));
	else
		process_program(&set);
	return (0);
}
