/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** minishell
*/

#ifndef MINISHELL_H_
    #define MINISHELL_H_
    #include <sys/types.h>
    #include <signal.h>
    #include <stddef.h>
    #include <stdbool.h>
    #include <termios.h>

typedef struct alias_s {
    char *name;
    char **command;
} alias_t;

typedef struct minishell_s {
    char **user_input;
    char **env;
    char *old_cd;
    char **args;
    int is_piped;
    int command_index;
    int pipefd[2];
    int last_stdout;
    int first_read;
    int final_write;
    int status;
    int pipe_status;
    int *pid;
    int cpt;
    int stdin_savior;
    int stdout_savior;
    char **tab_history;
    char **tab_history_time;
    int history_nav;
    alias_t **alias;
} minishell_t;

typedef struct word_array_s {
    char **tab;
    int start;
    int tab_index;
    int index;
} word_array_t;

typedef struct command_handler_s {
    char *command;
    int (*handler)(minishell_t *minishell);
} command_handler_t;

typedef struct command_s {
    int macro;
    char *error_message;
} command_t;

typedef struct input_s {
    char *buffer;
    size_t buffer_size;
    char c;
    double cursor_position;
} input_t;

typedef struct keybind_s {
    char key;
    void (*ptr)(input_t *input, minishell_t *minishell);
} keybind_t;

typedef struct format_s {
    int size;
    int width;
    bool first;
    int max_length;
}format_t;

typedef struct sub_sh_s {
    bool in_quotes;
    bool in_double_quotes;
    char *word;
    int j;
    int k;
    char **result;
} sub_sh_t;

int my_minishell(char **env);
int command_handler(minishell_t *minishell);
//command handler
int check_path(minishell_t *minishell);
int my_cd(minishell_t *minishell);
int my_env(minishell_t *minishell);
int my_setenv(minishell_t *minishell);
int my_unsetenv(minishell_t *minishell);
int my_exit(minishell_t *minishell);

//alias
alias_t **init_alias(void);
alias_t **alias_cmd(char **arg, alias_t **alias);
alias_t **my_realloc(alias_t **old_tab, alias_t *lign_to_add);
char **sub_sh_word_array(char *string, char *delimiter);
void free_alias(alias_t **alias);

//history
void add_command_to_tab(char *command, minishell_t *all);
void add_time_to_tab(minishell_t *all);
int display_history(minishell_t *all);

static const command_handler_t COMMAND_HANDLER_TAB[] = {
    {"cd", &my_cd},
    {"env", &my_env},
    {"setenv", &my_setenv},
    {"unsetenv", &my_unsetenv},
    {"exit", &my_exit},
    {"history", &display_history},
    {NULL, NULL}
};

static const command_t ERROR_MESSAGE[] = {
    {SIGHUP, "Hangup"},
    {SIGINT, "Interrupt"},
    {SIGQUIT, "Quit"},
    {SIGILL, "Illegal instruction"},
    {SIGTRAP, "Trace/BPT trap"},
    {SIGABRT, "Abort"},
    {SIGIOT, "IOT trap"},
    {SIGFPE, "Floating exception"},
    {SIGKILL, "Killed"},
    {SIGUSR1, "User signal 1"},
    {SIGUSR2, "User signal 2"},
    {SIGSEGV, "Segmentation fault"},
    {SIGBUS, "Bus error"},
    {SIGSYS, "Bad system call"},
    {SIGPIPE, "Broken pipe"},
    {SIGALRM, "Alarm clock"},
    {SIGTERM, "Terminated"},
    {SIGPWR, "Power failure"},
    {SIGIO, "IO"},
    {SIGURG, "Urgent condition on I/O channel"},
    {SIGSTOP, "STOP"},
    {SIGTSTP, "TSTP"},
    {SIGCONT, "Continued"},
    {SIGTTIN, "TTIN"},
    {SIGTTOU, "TTOU"},
    {SIGXCPU, "XCPU"},
    {SIGXFSZ, "XFSZ"},
    {SIGPROF, "PROF"},
    {SIGPOLL, "POLL"},
    {-1, NULL},
};

//utiles
minishell_t *init_struct(void);
char *get_line(void);
char *my_getenv(char *str, char **env);
int my_putstr_fd(char const *str, int fd);
char **my_tab_addline(char **tab, size_t size, char *str);
int print_dash_help(void);
char **my_tabdup(char **tab);
int tab_delline(char ***tab, int len, int line_to_del);
int is_piped(char *command_line);
int get_last_line_tab(char **tab);
int handle_signal(int wait_status);
void handle_error_tab(int i, int num_sig);
int handle_error(char *command);
int pipe_error(char **args, char *command, minishell_t *minishell);
char **my_str_to_wordarray_multi_delim(char *str, char *delimiters[]);
void remove_last_char(char **buffer, const size_t buffer_size);
void free_tab(char **tab);
void free_struc_minishell(minishell_t *minishell);

//handle_pipe
int parse_pipe(minishell_t *minishell, char **line, char ***args);

//handle_redirections
int find_redirection(char *command_line, minishell_t *minishell);

//input
char *parse_input(minishell_t *minishell);
void reset_term(struct termios *old);
void set_non_canonical(struct termios *old);
void arrow(input_t *input, minishell_t *minishell);
void delete(input_t *input, minishell_t *minishell);
int add_char(input_t *input, bool *isSpe);
void erase(input_t *input, minishell_t *minishell);
void tab(input_t *input, minishell_t *minishell);
void middle(input_t *input);
void remove_char_from_str(input_t *input);
int no_word(input_t *input, char **buffer);
void one_occurrence(char **files, input_t *input, char *model);
void several_occurrences(char **files, input_t *input, char *model);
int count_occurrences(char **files, char *model);
char **retrieve_files(char *path);
void check_function(char ***files);

static const keybind_t tab_keybinds[5] = {
    {'\033', &arrow},
    {127, &delete},
    {126, &erase},
    {9, &tab},
    {0, 0},
};

    #define USER_INPUT minishell->user_input
    #define ENV minishell->env
    #define OLD_CD minishell->old_cd
    #define INDEX minishell->command_index
    #define STATUS minishell->status
    #define P_STATUS minishell->pipe_status

#endif /* !MINISHELL_H_ */
