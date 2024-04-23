/*
** EPITECH PROJECT, 2023
** myprintf
** File description:
** handle_flag_minus_f.c
*/

#include "../../include/my.h"
#include "../../include/my_parser.h"

static int contains(char *str, char c)
{
    int found = 0;
    int i = 0;

    while (!found && str[i] != '\0') {
        found = str[i] == c;
        i++;
    }
    return found;
}

static void replace(char *str, char c)
{
    int i = 0;

    while (str[i] != '\0') {
        str[i] = c;
        i++;
    }
}

int handle_flag_minus_f(parser_t *parser, flag_arguments_t *flag_args)
{
    int size = 0;

    if (contains(parser->flags, '-')) {
        replace(flag_args->width, ' ');
        size += my_put_double(flag_args->arg_double, parser->precision);
        size += my_putstr(flag_args->width);
    } else {
        size += my_putstr(flag_args->width);
        size += my_put_double(flag_args->arg_double, parser->precision);
    }
    return size;
}
