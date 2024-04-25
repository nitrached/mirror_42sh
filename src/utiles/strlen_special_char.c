/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** strlen_special_char.c
*/

int strlen_special_char(char *str)
{
    double count = 0;

    for (int i = 0; str[i]; i++) {
        if (str[i] < 0) {
            count += 0.5;
            continue;
        }
        count++;
    }
    return count;
}
