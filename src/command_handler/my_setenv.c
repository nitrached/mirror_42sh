/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** my_setenv
*/
#include <stdlib.h>
#include "my.h"
#include <stddef.h>
#include "minishell.h"

static char *setup_newenv_null(char **args, char *new_env)
{
    new_env = malloc(sizeof(char *) * (my_strlen(args[1]) + 2));
    new_env = my_strcpy(new_env, args[1]);
    new_env = my_strcat(new_env, "=");
    new_env = my_strcat(new_env, "\0");
    return (new_env);
}

static char *setup_newenv_basic(char **args, char *new_env)
{
    new_env = malloc(sizeof(char *) *
    (my_strlen(args[1]) + my_strlen(args[2]) + 2));
    new_env = my_strcpy(new_env, args[1]);
    new_env = my_strcat(new_env, "=");
    new_env = my_strcat(new_env, args[2]);
    new_env = my_strcat(new_env, "\0");
    return (new_env);
}

static char *setup_newenv(char **args)
{
    char *new_env = NULL;

    if (args[2] == NULL)
        new_env = setup_newenv_null(args, new_env);
    else
        new_env = setup_newenv_basic(args, new_env);
    return (new_env);
}

static int env_exists(minishell_t *minishell, int len, char **new_env)
{
    if (my_strncmp(USER_INPUT[1], ENV[len],
        my_strlen(USER_INPUT[1])) == 0
        && ENV[len][my_strlen(USER_INPUT[1])] == '=') {
        *new_env = setup_newenv(USER_INPUT);
        ENV[len] = *new_env;
        return 1;
    }
    return 0;
}

int my_setenv(minishell_t *minishell)
{
    size_t len = 0;
    char *new_env = NULL;

    if (USER_INPUT[1] == NULL)
        return my_env(minishell);
    if (!my_str_isalpha(USER_INPUT[1])) {
        my_putstr_fd("setenv: Variable name must contain ", 2);
        my_putstr_fd("alphanumeric characters.\n", 2);
        return 1;
    }
    for (; ENV[len] != NULL; len++) {
        if (env_exists(minishell, len, &new_env))
            return 1;
    }
    new_env = setup_newenv(USER_INPUT);
    ENV = my_tab_addline(ENV, len, new_env);
    return 1;
}
