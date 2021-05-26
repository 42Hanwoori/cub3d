#include "cub3d.h"

int	init_map(t_set *set, t_list *lst)
{
	int i;
	int j;

	i = 0;
	set->map_height = ft_lstsize(lst);
	set->map = (char **)malloc(sizeof(char *) * (set->map_height + 1));
	if (set->map == 0)
		return exit_error(set);
	set->map_width = get_max_line_size(lst);
	while (lst)
	{
		set->map[i] = (char *)malloc(sizeof(char) * (set->map_width + 1));
		if (set->map[i] == 0)
			return (exit_error(set));
		j = 0;
		while (j < set->map_width)
			set->map[i][j++] = ' ';
		set->map[i][set->map_width] = '\0';
		lst = lst->next;
		i++;
	}
	return (1);
}

int	fill_map(t_set *set, t_list *lst)
{
	int i;
	int j;
	char *line;
	int dir_count;

	i = -1;
	dir_count = 0;
	while (++i < set->map_height)
	{
		j = -1;
		line = (char *)lst->content;
		while (++j < (int)ft_strlen(line))
		{
			if (is_map_arg(line[j]) == -1)
				return (exit_error(set));
			set->map[i][j] = line[j];
			init_direction(set, i, j, &dir_count);
		}
		lst = lst->next;
	}
	if (dir_count == 0 || dir_count > 1)
		return (exit_error(set));
	return (1);
}

int	check_valid_map(t_set *set)
{
	int i;
	int j;

	i = 0;
	while (i < set->map_height)
	{
		j = 0;
		while (j < set->map_width)
		{
			if (set->map[i][j] != ' ')
			{
				if (!up_test(set, i, j))
					return (exit_error(set));
				if (!down_test(set, i, j))
					return (exit_error(set));
				if (!left_test(set, i, j))
					return (exit_error(set));
				if (!rigth_test(set, i, j))
					return (exit_error(set));
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	parse_map(t_set *set, t_list *lst)
{
	if (!init_map(set, lst))
		return (exit_error(set));
	if (!fill_map(set, lst))
		return (exit_error(set));
	ft_lstclear(&lst, free);
	if (!check_valid_map(set))
		return (exit_error(set));
	return (1);
}

int	read_map(t_set *set, char *line)
{
	t_list	*lst;
	int		begun;

	begun = 0;
	set->map_height = 0;
	set->map_width = 0;
	while (get_next_line(set->fd, &line) > 0)
	{
		if (*line != 0 && begun == 0)
		{
			lst = ft_lstnew(line);
			begun = 1;
		}
		else if (begun == 1)
			ft_lstadd_back(&lst, ft_lstnew(line));
		else
			free(line);
	}
	if (*line != 0)
		ft_lstadd_back(&lst, ft_lstnew(line));
	parse_map(set, lst);
	return (1);
}
