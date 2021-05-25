int		main(void)
{
    int     fd;
    int     ret;
    char    *line;

    if av
    
    fd = open("c:/0gnl/war_machine/tests/line.txt", O_RDONLY);
    if (fd == -1)
        return (-1);
    ret = 1;
    while (ret > 0)
    {
        ret = get_next_line(fd, &line);
        if (1)
            printf("%s\n", line);
        free(line);
    }
    get_next_line(fd, &line);
    if (1)
        printf("%s\n", line);
    free(line);
    close(fd);
}