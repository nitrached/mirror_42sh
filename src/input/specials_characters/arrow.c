/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** arrow.c
*/

#include <unistd.h>
#include "../../../include/minishell.h"
#include "../../../include/my.h"

void arrow(input_t *input)
{
    read(STDIN_FILENO, &input->c, 1);
    read(STDIN_FILENO, &input->c, 1);
    if (input->c == 'A' || input->c == 'B') {
        // printf("\033[%dD", 2);
        // printf("%c[2K\r", 27);
        // my_putstr("\033[C");
        // printf("\33[2K\r");
        // printf("\x1b[2K");
        // printf("%s", "heiut");
        int i = 0;
        int len = my_strlen(input->buffer);
        // printf("Len : %d\n", my_strlen(input->buffer));
        for (i = 0; i < len; i++) {
            my_putstr("\b \b");
        }
        free(input->buffer);
        // input->buffer_size = my_strlen("zebi") + 1;
        input->buffer = malloc(sizeof(char) * 4);
        input->buffer = "zebi";
        my_putstr(input->buffer);
        input->buffer_size = 4;
        // printf("buffer size : %ld\n", input->buffer_size);
        input->cursor_position = my_strlen(input->buffer);
        // printf("cursor pos : %lf\n", input->cursor_position);
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
