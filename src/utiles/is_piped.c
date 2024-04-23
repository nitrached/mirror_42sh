/*
** EPITECH PROJECT, 2024
** minishell_2
** File description:
** is_piped
*/

int is_piped(char *command_line)
{
    for (int i = 0; command_line[i] != '\0'; i++) {
        if (command_line[i] == '|')
            return (1);
    }
    return (0);
}
