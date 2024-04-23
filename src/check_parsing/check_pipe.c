/*
** EPITECH PROJECT, 2024
** B-PSU-200-REN-2-1-42sh-elie.stroun
** File description:
** handle_pipe
*/
#include "../include/my.h"
#include "../include/minishell.h"

int check_pipes(minishell_t *minishell, int i, int *len)
{
    if (!my_strcmp(INPUTS->exec[i], "|")) {
        if (REDIRECT->is_redirect) {
            return my_putstr_fd("Ambiguous input redirect.\n", 2);
        }
        if (INPUTS->exec[i + 1] != NULL && !my_strcmp(INPUTS->exec[i + 1], "|")) {
            PIPES->is_piped = true;
            return 1;
        }
        return my_putstr_fd(" | is not valid\n", 2);
    }
    return 1;
}
