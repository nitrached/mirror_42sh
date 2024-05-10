/*
** EPITECH PROJECT, 2024
** mirror_42sh
** File description:
** free_tab
*/
#include "my.h"
#include <stdlib.h>

void free_tab(char **tab)
{
    if (tab == NULL)
        return;
    for (int i = 0; tab[i] != NULL; i++)
        free(tab[i]);
    free(tab);
}
