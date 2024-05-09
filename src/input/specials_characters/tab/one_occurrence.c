/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** one_occurence.c
*/

#include "minishell.h"
#include "my.h"

static void complete(const char *files, int i, input_t *input)
{
    bool isSpe = false;

    for (; files[i]; i++) {
        input->c = files[i];
        add_char(input, &isSpe);
    }
    input->c = ' ';
    add_char(input, &isSpe);
}

static int compare_str(const char *files, const char *model, input_t *input)
{
    int i = 0;

    for (; files[i] == model[i]; i++);
    if (i == my_strlen(model)) {
        complete(files, i, input);
        return 1;
    }
    return 0;
}

void one_occurrence(char **files, input_t *input, char *model)
{
    for (int i = 0; files[i]; i++) {
        if (compare_str(files[i], model, input))
            return;
    }
}
