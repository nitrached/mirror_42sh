/*
** EPITECH PROJECT, 2023
** C-POOL
** File description:
** my_strlen.c
*/

int my_strlen(char const *str)
{
    int size = 0;

    while (str[size] != '\0')
        size++;
    return size;
}
