/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** occurrence.c
*/

#include "minishell.h"
#include "my.h"

static int compare_str(const char *files, const char *model)
{
    int i = 0;

    for (; files[i] == model[i]; i++);
    if (i == my_strlen(model))
        return 1;
    return 0;
}

int count_occurrences(char **files, char *model)
{
    int nbOccur = 0;

    for (int i = 0; files[i]; i++) {
        if (compare_str(files[i], model))
            nbOccur++;
    }
    return nbOccur;
}
