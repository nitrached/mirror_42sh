/*
** EPITECH PROJECT, 2023
** myprintf
** File description:
** handle_n.c
*/

#include "../../include/my.h"
#include "../../include/my_parser.h"
#include <stdarg.h>

int handle_n(parser_t *parser, va_list *ap, int size)
{
    int *arg = va_arg(*ap, int *);

    *arg = size;
    return size;
}
