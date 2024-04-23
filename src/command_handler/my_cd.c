/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** my_cd
*/
#include "minishell.h"
#include "my.h"
#include <stddef.h>
#include <unistd.h>
static int handle_error_cd(char *path)
{
    if (!my_strcmp(path, "HOME"))
        my_putstr_fd("cd: Can't change to home directory.\n", 2);
    else {
        if (access(path, F_OK) == 0) {
            my_putstr_fd(path, 2);
            my_putstr_fd(": Not a directory.\n", 2);
            return -1;
        }
        my_putstr_fd(path, 2);
        my_putstr_fd(": No such file or directory.\n", 2);
    }
    return 84;
}

static int handle_home_cd(minishell_t *minishell, char *savior)
{
    if (chdir(my_getenv("HOME=", ENV)) == -1)
        return handle_error_cd("HOME");
    OLD_CD = savior;
    return 1;
}

static int handle_back_cd(minishell_t *minishell, char *savior)
{
    if (OLD_CD == NULL) {
        my_putstr_fd(": No such file or directory.\n", 2);
        return 1;
    }
    if (chdir(OLD_CD) != -1)
        OLD_CD = savior;
    return 1;
}

int my_cd(minishell_t *minishell)
{
    char *savior = getcwd(NULL, 0);

    if (USER_INPUT[1] == NULL
        || !my_strcmp(USER_INPUT[1], "~")
        || !my_strcmp(USER_INPUT[1], "~/"))
        return handle_home_cd(minishell, savior);
    if (!my_strcmp(USER_INPUT[1], "-")) {
        return handle_back_cd(minishell, savior);
    } else if (chdir(USER_INPUT[1]) == -1) {
        handle_error_cd(USER_INPUT[1]);
        return 1;
    }
    OLD_CD = savior;
    return 1;
}
