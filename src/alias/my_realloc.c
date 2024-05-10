/*
** EPITECH PROJECT, 2023
** realloc
** File description:
** reallocate a tab in another tab
*/

#include <stdio.h>
#include "minishell.h"
#include <stdlib.h>
#include <stddef.h>

static alias_t *my_strcpy_realloc(alias_t *dest, alias_t const *src)
{
    dest->command = src->command;
    dest->name = src->name;
    return dest;
}

static alias_t *my_strdup(const alias_t *src)
{
    alias_t *new_str;

    if (src == NULL) {
        return NULL;
    }
    new_str = malloc(sizeof(alias_t));
    if (new_str == NULL) {
        return NULL;
    }
    my_strcpy_realloc(new_str, src);
    return new_str;
}

alias_t **my_realloc(alias_t **old_tab, alias_t *lign_to_add)
{
    int nbr_lign = 0;
    int new_nbr_lign = 0;
    int i = 0;
    alias_t **new_tab;

    while (old_tab[nbr_lign] != NULL) {
        nbr_lign++;
    }
    new_nbr_lign += nbr_lign + 1;
    new_tab = malloc(sizeof(alias_t *) * (new_nbr_lign + 1));
    while (i < nbr_lign) {
        new_tab[i] = old_tab[i];
        i++;
    }
    new_tab[new_nbr_lign - 1] = my_strdup(lign_to_add);
    new_tab[new_nbr_lign] = NULL;
    free(old_tab);
    return new_tab;
}
