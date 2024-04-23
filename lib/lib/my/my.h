/*
** EPITECH PROJECT, 2023
** C-POOL
** File description:
** my.h.c
*/

#ifndef LINKED_LIST
    #define LINKED_LIST

typedef struct linked_list {
    int i;
    void *data;
    struct linked_list *next;
    struct linked_list *prev;
} linked_list_t;

int get_int(linked_list_t *list);
char *get_string(linked_list_t *list);
double get_double(linked_list_t *list);
float get_float(linked_list_t *list);
short get_short(linked_list_t *list);
linked_list_t *new_linked_list(void *data, linked_list_t *previous, int i);
void push(linked_list_t *list, void *data);
#endif

#ifndef MY_LIB
    #define MY_LIB

int get_digit(int nb, int i);
void set_digit(int *nb, int i, int digit);

int is_char_lower(char c);
int is_char_upper(char c);
int is_letter(char c);
int is_digit(char c);
int is_char_printable(char c);

char *my_get_base(unsigned long long nb, int base);

void char_to_uppercase(char *c);
void char_to_lowercase(char *c);
void my_swapchar(char *a, char *b);

int my_printf(char *format, ...);
int my_put_double(double nb, int precision);
int my_putchar(char c);
int my_put_nbr(int nb);
int my_putstr(char const *str);
int my_isneg(int nb);
void my_swap(int *a, int *b);
int my_strlen(char const *str);
int my_getnbr(char const *str);
void my_sort_int_array(int *tab, int size);
int my_compute_power_rec(int nb, int power);
int my_compute_square_root(int nb);
int my_is_prime(int nb);
int my_find_prime_sup(int nb);
char *my_strcpy(char *dest, char const *src);
char *my_strncpy(char *dest, char const *src, int n);
char *my_revstr(char *str);
char *my_strstr(char *str, char const *to_find);
int my_strcmp(char const *s1, char const *s2);
int my_strncmp(char const *s1, char const *s2, int n);
char *my_strupcase(char *str);
char *my_strlowcase(char *str);
char *my_strcapitalize(char *str);
int my_str_isalpha(char const *str);
int my_str_isnum(char const *str);
int my_str_islower(char const *str);
int my_str_isupper(char const *str);
int my_str_isprintable(char const *str);
int my_showstr(char const *str);
int my_showmem(char const *str, int size);
char *my_strcat(char *dest, char const *src);
char *my_strncat(char *dest, char const *src, int nb);
//char **my_str_to_word_array(char const *str);
char **my_str_to_word_array(char const *str, char ch);
int my_show_word_array(char const **tab);
char *my_strrchr(const char *str, int ch);
char *my_strdup(const char *src);
#endif

#ifndef MY_TAB_H_
    #define MY_TAB_H_

typedef struct my_tab {
    char **tab;
    int len;
} my_tab_t;

my_tab_t *my_tab_init(void);
void my_tab_add_line(my_tab_t *ptr, const char *line);
void my_tab_destroy(my_tab_t *ptr);
my_tab_t *get_conv_tab(char *format);
char *return_nbr_base_x(int ten_base);
char *return_nbr_base_X(int ten_base);
#endif
