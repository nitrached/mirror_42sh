/*
** EPITECH PROJECT, 2023
** myprintf
** File description:
** handle_width.c
*/

#include <stdlib.h>
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

static char *get_str(char c, int size)
{
    char *str = malloc(sizeof(char) * (size + 1));
    int i = 0;

    while (i < size) {
        str[i] = c;
        i++;
    }
    str[i] = '\0';
    return str;
}

static int get_nb_char(parser_t *parser, int arg_length)
{
    if (parser->precision)
        return parser->width - parser->precision;
    else
        return parser->width - arg_length;
}

char *handle_width(parser_t *parser, int arg_length)
{
    char *width = NULL;
    int i = 0;

    while (FUNC_HANDLER_WIDTH[i].f != NULL) {
        if (FUNC_HANDLER_WIDTH[i].conversion == parser->conversion) {
            width = FUNC_HANDLER_WIDTH[i].f(parser, arg_length);
            break;
        }
        i++;
    }
    if (FUNC_HANDLER_WIDTH[i].conversion == '\0') {
        width = malloc(sizeof(char));
        width[0] = '\0';
    }
    return width;
}
