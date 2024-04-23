/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** my_getenv
*/
#include "my.h"
#include <stddef.h>
#include <unistd.h>
char *my_getenv(char *str, char **env)
{
    for (int i = 0; env[i] != NULL; i++) {
        if (!my_strncmp(str, env[i], my_strlen(str) - 1))
            return (env[i] + my_strlen(str));
    }
    return NULL;
}
