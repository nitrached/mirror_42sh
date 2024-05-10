/*
** EPITECH PROJECT, 2024
** init_alias
** File description:
** init_alias
*/

#include "minishell.h"
#include "my.h"
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

static char *open_file(char *file_name)
{
    char *rc;
    int fd = open(file_name, O_RDONLY | O_CREAT);
    struct stat fileStat;
    int size;

    if (fd == -1)
        return NULL;
    if (stat(file_name, &fileStat) == -1)
        return NULL;
    if (stat(file_name, &fileStat) == 0)
        size = fileStat.st_size;
    rc = malloc(sizeof(char) * (size + 1));
    read(fd, rc, size);
    rc[size] = '\0';
    close(fd);
    return rc;
}

char *suite(char *arg)
{
    char *modif_arg = malloc(sizeof(char) * (strlen(arg) - 1));
    int j = 0;

    for (int i = 0; arg[i] != '\0'; i++) {
        if (i != 0 && arg[i + 1] != '\0') {
            modif_arg[j] = arg[i];
            j++;
        }
    }
    modif_arg[j] = '\0';
    return modif_arg;
}

static alias_t *put_in_alias(alias_t *alias, char *rc)
{
    char **arg = sub_sh_word_array(rc, " =");
    int verif = 0;

    alias->command = malloc(sizeof(char *));
    for (int i = 0; arg[i] != NULL; i++) {
        if ((arg[i][0] == '\"' || arg[i][0] == '\'') && verif == 1) {
            alias->command = malloc(sizeof(char) * (strlen(arg[i]) - 1));
            alias->command = my_str_to_wordarray(arg[i], " \"");
        }
        if ((arg[i][0] == '\"' || arg[i][0] == '\'') && verif == 0) {
            alias->name = malloc(sizeof(char) * (strlen(arg[i]) - 1));
            alias->name = suite(arg[i]);
            verif = 1;
        }
    }
    return alias;
}

static alias_t *malloc_line_alias(alias_t *alias)
{
    alias = malloc(sizeof(alias_t));
    alias->command = NULL;
    alias->name = NULL;
    return alias;
}

int count_nb_alias(char **tab_rc)
{
    int nb = 0;

    if (tab_rc == NULL)
        return 1;
    for (int i = 0; tab_rc[i]; i++)
        if (tab_rc[i][0] != '#' && strncmp("alias", tab_rc[i], 5) == 0)
            nb++;
    if (nb == 0)
        return 1;
    return nb;
}

alias_t **init_alias(void)
{
    char *rc = open_file("42shrc");
    char **tab_rc = my_str_to_wordarray(rc, "\n");
    int nb_alias = count_nb_alias(tab_rc);
    alias_t **alias = malloc(sizeof(alias_t *) * (nb_alias + 1));
    int j = 0;

    free(rc);
    if (tab_rc == NULL)
        return NULL;
    for (int i = 0; tab_rc[i]; i++) {
        if (tab_rc[i][0] != '#' && strncmp("alias", tab_rc[i], 5) == 0) {
            alias[j] = malloc_line_alias(alias[j]);
            alias[j] = put_in_alias(alias[j], tab_rc[i]);
            j++;
        }
    }
    alias[j] = NULL;
    free_tab(tab_rc);
    return alias;
}
