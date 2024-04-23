/*
** EPITECH PROJECT, 2023
** myprintf
** File description:
** handle_minus_flag.c
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

int handle_minus_flag(parser_t *parser, flag_arguments_t *flag_args)
{
    int size = 0;
    int i = 0;

    while (FUNC_HANDLER_FLAGS[i].conversion != '\0') {
        if (FUNC_HANDLER_FLAGS[i].conversion == parser->conversion) {
            size += FUNC_HANDLER_FLAGS[i].f(parser, flag_args);
            break;
        }
        i++;
    }
    return size;
}
