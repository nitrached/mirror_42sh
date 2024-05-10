/*
** EPITECH PROJECT, 2024
** dev_42
** File description:
** check_function.c
*/

#include "minishell.h"

void check_function(char ***files)
{
    (*files) = retrieve_files("/bin");
}
