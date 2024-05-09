/*
** EPITECH PROJECT, 2024
** 42shMAIN
** File description:
** terminal_settings.c
*/

#include <termios.h>
#include <unistd.h>
#include "my.h"

void set_non_canonical(struct termios *old)
{
    struct termios new;

    tcgetattr(STDIN_FILENO, old);
    new = *old;
    new.c_lflag &= ~(ICANON | ECHO);
    new.c_cc[VMIN] = 1;
    new.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &new);
}

void reset_term(struct termios *old)
{
    tcsetattr(STDIN_FILENO, TCSANOW, old);
    if (isatty(STDIN_FILENO))
        my_putchar('\n');
}
