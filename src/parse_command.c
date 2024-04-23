/*
** EPITECH PROJECT, 2024
** B-PSU-200-REN-2-1-42sh-elie.stroun
** File description:
** parse_command
*/

#include "../include/my.h"
#include "../include/minishell.h"

void take_off_spaces(minishell_t *minishell)
{
    int len = 0;

    for (; INPUTS->exec[len] != NULL; len++);
    for (int i = 0; INPUTS->exec[i] != NULL; i++) {
        if (INPUTS->exec[i][0] == ' ' || INPUTS->exec[i][0] == '\t') {
            tab_delline(&INPUTS->exec, len, i);
            len--;
        }
    }
}

void print_debug(minishell_t *minishell)
{
    for(int i = 0; INPUTS->exec[i] != NULL; i++) {
        my_printf(" command [%s]\n", INPUTS->exec[i]);
    }
    my_printf("read [%d] ; write [%d]\n", REDIRECT->first_read, REDIRECT->last_write);
    my_printf("\n\n");
}

int execute_command(minishell_t *minishell)
{
    INPUTS->exec = sh_word_array(INPUTS->exec[0], " \t");
    take_off_spaces(minishell);
    print_debug(minishell);
    return 1;
}

int parse_redirection(minishell_t *minishell, char *sh_pipe)
{

    int len = 0;

    INPUTS->exec = sh_word_array(sh_pipe, "<>");
    for (; INPUTS->exec[len] != NULL; len++)
        my_printf("[%d] = [%s]\n", len, INPUTS->exec[len]);
    for (int i = 0; INPUTS->exec[i] != NULL; i++) {
        if (redirect_left(minishell, i, &len) != 1) {
            my_printf("error\n");
            return 0;
        }
        if (redirect_right(minishell, i, &len) != 1) {
            my_printf("error\n");
            return 0;
        }
    }
    print_debug(minishell);
    execute_command(minishell);
    return 1;
}

void parse_pipe(minishell_t *minishell, int index)
{
    my_printf("je parse\n");
    char **sh_pipe = sh_word_array(INPUTS->semicolon[index], "|");

    for (; sh_pipe[PIPES->nb_commands] != NULL; PIPES->nb_commands++);
    for (int i = 0; sh_pipe[i] != NULL; i++) {
        if (sh_pipe[i][0] == '|') {
            tab_delline(&sh_pipe, PIPES->nb_commands, i);
            PIPES->nb_commands--;
            continue;
        }
    }
    while(sh_pipe[INDEXES->command_index] != NULL) {
        my_printf("pipe[%s]\n", sh_pipe[INDEXES->command_index]);
        if (!parse_redirection(minishell, sh_pipe[INDEXES->command_index]))
        return;
        REDIRECT->is_redirect = false;
        REDIRECT->first_read = 1;
        REDIRECT->last_write = 0;
        INDEXES->command_index++;
    }
    return;
}
