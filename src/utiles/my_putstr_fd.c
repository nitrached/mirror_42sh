/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** my_put_str_fd
*/
#include <unistd.h>

int my_putstr_fd(char const *str, int fd)
{
    int i = 0;

    while (str[i] != '\0') {
        write(fd, &str[i], 1);
        i++;
    }
    return (0);
}
