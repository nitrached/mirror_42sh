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

static
void clean_input(input_t *input)
{
    for (; input->cursor_position > 0; input->cursor_position--)
        my_putstr("\033[D");
    my_putstr("\033[K");
    free(input->buffer);
}

static
void nothing_input(input_t *input)
{
    input->buffer = malloc(sizeof(char) * 1);
    input->buffer[0] = 0;
    input->buffer_size = 0;
    my_putstr(input->buffer);
    input->buffer_size = my_strlen(input->buffer);
    input->cursor_position = my_strlen(input->buffer);
}

static
void arrow_up(input_t *input, minishell_t *minishell)
{
    int len = 0;

    if (minishell->history_nav == -1 || minishell->history_nav <= 0)
        return;
    minishell->history_nav--;
    clean_input(input);
    len = strlen(minishell->tab_history[minishell->history_nav]);
    input->buffer = malloc(sizeof(char) * (len + 1));
    for (int i = 0; i < len; i++)
        input->buffer[i] = minishell->tab_history
        [minishell->history_nav][i];
    input->buffer[len] = 0;
    input->buffer_size = len;
    my_putstr(input->buffer);
    input->buffer_size = my_strlen(input->buffer);
    input->cursor_position = my_strlen(input->buffer);
}

static
void complete_arrow_down(input_t *input, minishell_t *minishell)
{
    int i = 0;
    int len = strlen(minishell->tab_history[minishell->history_nav]);

    input->buffer = malloc(sizeof(char) * (len + 1));
    for (i = 0; i < len; i++)
        input->buffer[i] = minishell->tab_history
        [minishell->history_nav][i];
    input->buffer[len] = 0;
    input->buffer_size = len;
    my_putstr(input->buffer);
    input->buffer_size = my_strlen(input->buffer);
    input->cursor_position = my_strlen(input->buffer);
}

static
void arrow_down(input_t *input, minishell_t *minishell)
{
    int i = 0;

    if (minishell->history_nav == -1)
        return;
    clean_input(input);
    minishell->history_nav++;
    while (minishell->tab_history[i] != NULL)
        i++;
    if (minishell->history_nav == i)
        return nothing_input(input);
    if (minishell->history_nav == i + 1) {
        minishell->history_nav--;
        return nothing_input(input);
    }
    complete_arrow_down(input, minishell);
}

void arrow(input_t *input, minishell_t *minishell)
{
    read(STDIN_FILENO, &input->c, 1);
    read(STDIN_FILENO, &input->c, 1);
    if (input->c == 'A')
        return arrow_up(input, minishell);
    if (input->c == 'B')
        return arrow_down(input, minishell);
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
