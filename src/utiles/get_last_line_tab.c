/*
** EPITECH PROJECT, 2024
** minishell_2
** File description:
** get_last_line_tab
*/
#include <stddef.h>

int get_last_line_tab(char **tab)
{
    int i = 0;

    for (; tab[i] != NULL; i++);
    return i - 1;
}
