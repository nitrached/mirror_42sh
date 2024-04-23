/*
** EPITECH PROJECT, 2024
** B-PSU-200-REN-2-1-42sh-elie.stroun
** File description:
** read_command
*/
#include "../include/my.h"
#include "../include/minishell.h"

void read_command(minishell_t *minishell)
{
    INPUTS->line = get_line();
    if (INPUTS->line == NULL) {
        minishell->status = 84;
        return;
    }
    INPUTS->semicolon = sh_word_array(INPUTS->line, ";");
    return;
}
