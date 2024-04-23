/*
** EPITECH PROJECT, 2023
** myprintf
** File description:
** handle_int.c
*/

#include <stdarg.h>
#include "../../include/my_parser.h"
#include "../../include/my.h"

static int get_int_length(int arg)
{
    int i = 0;

    while (arg > 0) {
        arg /= 10;
        i++;
    }
    return i;
}

int handle_int(parser_t *parser, va_list *ap, int size)
{
    int arg = va_arg(*ap, int);
    int arg_length = get_int_length(arg);
    char *width = handle_width(parser, arg_length);
    char *precision = handle_precision(parser, arg_length, NULL);
    flag_arguments_t *flag_args = malloc(sizeof(flag_arguments_t));

    flag_args->width = width;
    flag_args->precision = precision;
    flag_args->arg_int = arg;
    size += handle_minus_flag(parser, flag_args);
    free(flag_args);
    free(width);
    free(precision);
    return size;
}
