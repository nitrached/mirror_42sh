/*
** EPITECH PROJECT, 2024
** minishell1_2
** File description:
** tab_del_line
*/
#include <stddef.h>
#include <stdlib.h>

int tab_delline(char ***tab, int len, int line_to_del)
{
    free((*tab)[line_to_del]);
    (*tab)[line_to_del] = NULL;
    for (int i = line_to_del; i < len - 1; i++) {
        (*tab)[i] = (*tab)[i + 1];
    }
    return 1;
}
