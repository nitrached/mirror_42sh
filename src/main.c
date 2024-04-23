/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** main
*/
#include "my.h"
#include "minishell.h"
#include <stddef.h>
#include <stdlib.h>

int main(int argc, char **argv, char **env)
{
    if (argc == 2 && my_strcmp(argv[1], "-h") == 0)
        return print_dash_help();
    if (argc != 1)
        return 84;
    return my_minishell(env);
}
