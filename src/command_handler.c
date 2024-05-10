/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** command_handler
*/
#include <stddef.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"
#include "my.h"


int command_handler(minishell_t *minishell)
{
    if (USER_INPUT[0] == NULL)
        return 1;
    for (int i = 0; minishell->alias[i]; i++) {
        if (my_strcmp(minishell->alias[i]->name, USER_INPUT[0]) == 0) {
            free(USER_INPUT[0]);
            USER_INPUT = my_tabdup(minishell->alias[i]->command);
        }
    }
    for (int i = 0; COMMAND_HANDLER_TAB[i].command != NULL; i++) {
        if (my_strcmp(COMMAND_HANDLER_TAB[i].command, USER_INPUT[0]) == 0) {
            COMMAND_HANDLER_TAB[i].handler(minishell);
            return 1;
        }
        if (my_strcmp(USER_INPUT[0], "alias") == 0) {
            minishell->alias = alias_cmd(USER_INPUT, minishell->alias);
            return 1;
        }
    }
    return check_path(minishell);
}
