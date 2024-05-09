/*
** EPITECH PROJECT, 2024
** alias
** File description:
** alias
*/
#include "minishell.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

static sub_sh_t *init_struct_sh(char *string)
{
    sub_sh_t *sub_sh = malloc(sizeof(sub_sh_t));

    if (!sub_sh)
        return NULL;
    sub_sh->result = malloc((strlen(string) * 2 + 1) * sizeof(char *));
    sub_sh->word = malloc(strlen(string) + 1);
    sub_sh->k = 0;
    sub_sh->j = 0;
    sub_sh->in_quotes = false;
    sub_sh->in_double_quotes = false;
    return sub_sh;
}

static int condition(char *string, sub_sh_t *sub_sh, int i, char *delimiter)
{
    if (string[i] == '\'')
        sub_sh->in_quotes = !sub_sh->in_quotes;
    if (string[i] == '\"')
        sub_sh->in_double_quotes = !sub_sh->in_double_quotes;
    if ((strchr(delimiter, string[i]) == NULL)
        || sub_sh->in_quotes || sub_sh->in_double_quotes) {
        sub_sh->word[sub_sh->j] = string[i];
        sub_sh->j++;
    } else {
        sub_sh->word[sub_sh->j] = '\0';
        sub_sh->result[sub_sh->k] = strdup(sub_sh->word);
        sub_sh->k++;
        sub_sh->result[sub_sh->k] = strndup(&string[i], 1);
        sub_sh->k++;
        sub_sh->j = 0;
    }
    return 0;
}

char **sub_sh_word_array(char *string, char *delimiter)
{
    sub_sh_t *sub_sh = init_struct_sh(string);
    int i = 0;

    while (string[i] != '\0') {
        condition(string, sub_sh, i, delimiter);
        i++;
    }
    if (sub_sh->j > 0) {
        sub_sh->word[sub_sh->j] = '\0';
        sub_sh->result[sub_sh->k] = strdup(sub_sh->word);
        sub_sh->k++;
    }
    sub_sh->result[sub_sh->k] = NULL;
    free(sub_sh->word);
    return sub_sh->result;
}
