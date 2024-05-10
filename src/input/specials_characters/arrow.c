/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** arrow.c
*/

#include <unistd.h>
#include "../../../include/minishell.h"
#include "../../../include/my.h"
#include <malloc.h>
#include <string.h>

void arrow(input_t *input, minishell_t *minishell)
{
    read(STDIN_FILENO, &input->c, 1);
    read(STDIN_FILENO, &input->c, 1);
    if (input->c == 'A') {
        if (minishell->history_nav == -1 || minishell->history_nav <= 0)
            return;
        minishell->history_nav--;
        for (; input->cursor_position > 0; input->cursor_position--)
            my_putstr("\033[D");
        my_putstr("\033[K");
        free(input->buffer);
        int len = strlen(minishell->tab_history[minishell->history_nav]);
        input->buffer = malloc(sizeof(char) * (len + 1));
        for (int i = 0; i < len; i++)
            input->buffer[i] = minishell->tab_history
            [minishell->history_nav][i];
        input->buffer[len] = 0;
        input->buffer_size = len;
        my_putstr(input->buffer);
        input->buffer_size = my_strlen(input->buffer);
        input->cursor_position = my_strlen(input->buffer);
        return;
    }
    if (input->c == 'B') {
        if (minishell->history_nav == -1)
            return;
        for (; input->cursor_position > 0; input->cursor_position--)
            my_putstr("\033[D");
        my_putstr("\033[K");
        free(input->buffer);
        minishell->history_nav++;
        // printf("history nav %d\n", minishell->history_nav);
        int i = 0;
        while (minishell->tab_history[i] != NULL)
            i++;
        if (minishell->tab_history[minishell->history_nav + 1] == NULL) {
            input->buffer = malloc(sizeof(char) * 1);
            input->buffer[0] = 0;
            input->buffer_size = 0;
            my_putstr(input->buffer);
            input->buffer_size = my_strlen(input->buffer);
            input->cursor_position = my_strlen(input->buffer);
            return;
        }
        int len = strlen(minishell->tab_history[minishell->history_nav]);
        input->buffer = malloc(sizeof(char) * (len + 1));
        for (int i = 0; i < len; i++)
            input->buffer[i] = minishell->tab_history
            [minishell->history_nav][i];
        input->buffer[len] = 0;
        input->buffer_size = len;
        my_putstr(input->buffer);
        input->buffer_size = my_strlen(input->buffer);
        input->cursor_position = my_strlen(input->buffer);
        return;
    }
    if (input->c == 'C' &&
    input->cursor_position < my_strlen(input->buffer)) {
        if (input->buffer[(int) input->cursor_position + 1] < 0)
            input->cursor_position++;
        input->cursor_position++;
        my_putstr("\033[C");
        return;
    }
    if (input->c == 'D' && input->cursor_position > 0) {
        if (input->buffer[(int) input->cursor_position - 1] < 0)
            input->cursor_position--;
        input->cursor_position--;
        my_putstr("\033[D");
    }
}
