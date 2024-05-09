/*
** EPITECH PROJECT, 2024
** dev_42
** File description:
** check_function.c
*/

#include "minishell.h"

int check_function(char ***files)
{
    (*files) = retrieve_files("/bin");
    return 0;
}
