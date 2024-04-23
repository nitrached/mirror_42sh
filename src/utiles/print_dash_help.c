/*
** EPITECH PROJECT, 2024
** minishell1_2
** File description:
** print_dash_help
*/
#include "my.h"

int print_dash_help(void)
{
    my_putstr("minishell1\n");
    my_putstr("Usage:\n");
    my_putstr("minishell1 [command]\n");
    my_putstr("minishell1 -h\n");
    my_putstr("minishell1 --help\n");
    return (0);
}
