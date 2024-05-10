/*
** EPITECH PROJECT, 2024
** mirror_42sh
** File description:
** to_wordarray_multi_delim
*/
#include "minishell.h"
#include <string.h>
#include <stdlib.h>
#include "my.h"

static char **copy_tab(word_array_t *multi)
{
    char **new_tab = NULL;
    int len = 0;

    for (; multi->tab[len] != NULL; len++);
    new_tab = malloc(sizeof(char *) * (len + 1));
    for (int i = 0; i < len; i++)
        new_tab[i] = my_strdup(multi->tab[i]);
    new_tab[len] = NULL;
    return new_tab;
}

static
int check_word_delim(char *str, char *delimiters)
{
    int t = 0;

    while (delimiters[t] != '\0') {
        if (str[t] == '\0')
            return 0;
        if (str[t] != delimiters[t])
            return 0;
        t++;
    }
    return 1;
}

static
void fill_tab(word_array_t *multi, char *ptr, char *delimiters, char *str)
{
    multi->tab = realloc(multi->tab, sizeof(char *) * (multi->tab_index + 4));
    (multi->tab)[multi->tab_index] = calloc(strlen(ptr) + 1, sizeof(char));
    strcpy((multi->tab)[multi->tab_index], ptr + multi->start);
    (multi->tab)[multi->tab_index + 1]
    = calloc((strlen(delimiters) + 1), sizeof(char));
    strncpy((multi->tab)[multi->tab_index + 1],
    str + multi->index, strlen(delimiters));
    (multi->tab)[multi->tab_index + 2]
    = calloc(strlen(str) - multi->index + strlen(delimiters), sizeof(char));
    strcpy((multi->tab)[multi->tab_index + 2],
    str + multi->index + strlen(delimiters));
    (multi->tab)[multi->tab_index + 3] = NULL;
}

static
void fill_ptr(char *str, word_array_t *multi, char *ptr)
{
    for (int j = 0; j < multi->index; j++)
        ptr[j] = str[j];
}

static
char *check_delimiters(char *str, char *delimiters[], word_array_t *multi)
{
    char *ptr = NULL;

    for (int i = 0; delimiters[i] != NULL; i++) {
        if (check_word_delim(str + multi->index, delimiters[i])) {
            ptr = malloc(sizeof(char) * (multi->index + 1));
            fill_ptr(str, multi, ptr);
            ptr[multi->index] = '\0';
            fill_tab(multi, ptr, delimiters[i], str);
            multi->tab_index += 2;
            multi->index += strlen(delimiters[i]);
            multi->start += strlen(ptr) + strlen(delimiters[i]);
            return check_delimiters(str, delimiters, multi);
        }
    }
    return NULL;
}

static
int exists(char *str, char *delimiters[])
{
    for (int i = 0; delimiters[i] != NULL; i++) {
        if (strstr(str, delimiters[i]) != NULL)
            return 1;
    }
    return 0;
}

char **my_str_to_wordarray_multi_delim(char *str, char *delimiters[])
{
    word_array_t *multi = malloc(sizeof(word_array_t));
    char **tab = NULL;

    if (!exists(str, delimiters)) {
        free(multi);
        return NULL;
    }
    multi->tab = NULL;
    multi->tab_index = 0;
    multi->index = 0;
    multi->start = 0;
    for (; multi->index < (int)(strlen(str)); multi->index++) {
        check_delimiters(str, delimiters, multi);
    }
    tab = copy_tab(multi);
    free(multi->tab);
    free(multi);
    return tab;
}
