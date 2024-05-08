/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** tab.c
*/

#include "../../../../include/minishell.h"
#include "../../../../lib/include/my.h"
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

char **retrieve_files(void)
{
    struct dirent *dirp;
    DIR *dir = opendir(".");
    char **buffer = 0;
    int i = 0;

    if (!dir) {
        my_putstr("wrongdir\n");
        return 0;
    }
    for (; (dirp = readdir(dir)) != NULL; i++) {
        buffer = realloc(buffer, sizeof(char *) * (i + 2));
        buffer[i] = my_strdup(dirp->d_name);
        buffer[i + 1] = 0;
    }
    closedir(dir);
    return buffer;
}

static char *get_word(char *string, int string_size)
{
    int i = string_size;

    if (i == 0)
        string = "\0";
    i--;
    for (; i >= 0 && string[i] > 32; i--);
    i++;
    for (int j = 0; j < i; j++) {
        string++;
    }
    return string;
}

void tab(input_t *input)
{
    char **files = retrieve_files();
    char *model = get_word(input->buffer, (int)input->buffer_size);

    if (count_occurrences(files, model) > 1)
        several_occurrences(files, input, model);
    else
        one_occurrence(files, input, model);
    free(files);
}
