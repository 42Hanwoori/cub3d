#include "cub3d.h"

int		check_extension(char *s, char *s_ext)
{
	size_t	i;
	
	i = 0;
	while (s[i])
		i++;
	if (i >= ft_strlen(s_ext))
	{
		i -= ft_strlen(s_ext);
		if (ft_strcmp(&s[i], s_ext) == 0)
			return (1);
	}
	return (0);
}

int		main(int argc, char **argv)
{
	t_set	set;

	if (argc < 2 || !check_extension(argv[1], ".cub"))
		return (exit_error(&set));
	else if (!set_information(&set, argv[1]))
		return (exit_error(&set));
	if (argc == 3 && !ft_strcmp(argv[2], "--save"))
		return (process_bmp(&set));
	else if (argc >= 3)
		return (exit_error(&set));
	else
		process_program(&set);
	return (0);
}