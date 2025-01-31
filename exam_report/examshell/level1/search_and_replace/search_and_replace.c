#include <unistd.h>

int ft_strlen(char *str)
{
    int ct;

    ct = 0;
    while (*str++)
        ct++;
    return (ct);
}

int main(int argc, char **argv)
{
    if (argc == 4 && ft_strlen(argv[2]) == 1 && ft_strlen(argv[3]) == 1)
    {
        while (*argv[1])
        {
            if (*argv[1] == *argv[2] && *argv[2] != *argv[3])
                *argv[1] = *argv[3];
            write(1, &*argv[1], 1);
            *argv[1]++;
        }
    }
    write (1, "\n", 1);
    return (0);
}