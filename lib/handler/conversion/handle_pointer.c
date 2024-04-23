/*
** EPITECH PROJECT, 2023
** myprintf
** File description:
** handle_pointer.c
*/

#include "../../include/my.h"
#include "../../include/my_parser.h"
#include <stdarg.h>

static int contains(char const *str, char c)
{
    int i = 0;
    int found = 0;

    while (!found && str[i] != '\0') {
        found = str[i] == c;
        i++;
    }
    return found;
}

int handle_pointer(parser_t *parser, va_list *ap, int size)
{
    unsigned long long arg_int = va_arg(*ap, unsigned long long);
    char *arg = my_get_base(arg_int, 16);
    int arg_length = my_strlen(arg);
    char *width = handle_width(parser, arg_length + 2);
    char *precision = handle_precision(parser, arg_length, arg);

    if (arg_int == NULL)
        return size + my_putstr("(nil)");
    size += my_putstr(width) + my_putstr("0x");
    size += my_putstr(precision) + my_putstr(arg);
    free(arg);
    free(width);
    free(precision);
    return size;
}
