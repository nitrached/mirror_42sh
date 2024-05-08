/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** multiple_occurrences.c
*/

#include "minishell.h"
#include "my.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <string.h>

static int win_size(void)
{
    struct winsize ws;

    if (ioctl(STDIN_FILENO, TIOCGWINSZ, &ws) != 0 &&
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) != 0 &&
    ioctl(STDERR_FILENO, TIOCGWINSZ, &ws) != 0) {
        fprintf(stderr,
        "ioctl() failed (%d): %s\n", errno, strerror(errno));
        return 0;
    }
    return ws.ws_col;
}

static int compare_str(const char *files, const char *model, format_t *format)
{
    int i = 0;

    if (files[0] == '.')
        return 0;
    for (; files[i] == model[i]; i++);
    if (i == my_strlen(model)) {
        if (format->first) {
            printf("\n");
            format->first = false;
        }
        if (format->size * (format->max_length + 2) +
        format->max_length > format->width) {
            printf("\n");
            format->size = 0;
        }
        printf("%-*s  ", format->max_length, files);
        format->size++;
        return 1;
    }
    return 0;
}

static void check_occurrences(char **files, const char *model,
    format_t *format, bool *isOccur)
{
    for (int i = 0; files[i]; i++) {
        if (compare_str(files[i], model, format)) {
            (*isOccur) = true;
        }
    }
}

static int get_max_length(char **files)
{
    int max_length = 0;
    int length = 0;

    for (int i = 0; files[i]; i++) {
        length = my_strlen(files[i]);
        if (length > max_length) {
            max_length = length;
        }
    }
    return max_length;
}

void several_occurrences(char **files, input_t *input, char *model)
{
    format_t format = {0, win_size(), true, get_max_length(files)};
    bool isOccur = false;

    check_occurrences(files, model, &format, &isOccur);
    if (isOccur) {
        printf("\n$> ");
        if (input->buffer_size > 0)
            printf("%s", input->buffer);
        fflush(stdout);
    }
}
