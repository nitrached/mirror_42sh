/*
** EPITECH PROJECT, 2024
** B-PSU-200-REN-2-1-42sh-elie.stroun
** File description:
** sh_word_array
*/

#include "../include/my.h"
#include "../../include/minishell.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

char **sub_sh_word_array(char *string, char *delimiter)
{
    char **result = malloc((strlen(string) * 2 + 1) * sizeof(char *));
    char *word = malloc(strlen(string) + 1);
    int i = 0, j = 0, k = 0;
    bool in_quotes = false;
    bool in_double_quotes = false;
    bool in_parentheses = false;

    while (string[i] != '\0') {
        if (string[i] == '\'')
            in_quotes = !in_quotes;
        if (string[i] == '\"')
            in_double_quotes = !in_double_quotes;
        if (string[i] == '\(')
            in_parentheses = true;
        if (string[i] == '\)')
            in_parentheses = false;
        if ((strchr(delimiter, string[i]) == NULL)
        || in_quotes || in_double_quotes || in_parentheses) {
            word[j++] = string[i];
        } else {
            word[j] = '\0';
            result[k++] = strdup(word);
            result[k++] = strndup(&string[i], 1);
            j = 0;
        }
        i++;
    }

    if (j > 0) {
        word[j] = '\0';
        result[k++] = strdup(word);
    }

    result[k] = NULL;
    free(word);
    return result;
}

char **sh_word_array(char *string, char *delimiter)
{
    int len = 0;
    char **result = sub_sh_word_array(string, delimiter);

    for (; result[len] != NULL; len++);
    for (int i = 0; i < len; i++) {
        if (result[i][0] == '\0') {
            tab_delline(&result, len, i);
            len--;
        }
    }
    return result;
}
