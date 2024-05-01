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

    #define REDIRECT minishell->redirect
    #define PIPES minishell->pipes
    #define VARIABLES minishell->variables
    #define INDEXES minishell->indexes
    #define INPUTS minishell->inputs

typedef struct variables_s {
    char **env;
    char *old_cd;
} variables_t;

typedef struct pipes_s {
    bool is_piped;
    int nb_commands;
    int pipefd[2];
    int *pid;
} pipes_t;

typedef struct redirect_s {
    bool is_redirect;
    int stdout_savior;
    int stdin_savior;
    int first_read;
    int last_write;
} redirect_t;

typedef struct indexes_s {
    int command_index;
    int cpt;
} indexes_t;

typedef struct inputs_s {
    char *line;
    char **semicolon;
    char **exec;
} inputs_t;

typedef struct minishell_s {
    variables_t *variables;
    indexes_t *indexes;
    redirect_t *redirect;
    inputs_t *inputs;
    pipes_t *pipes;
    int status;
} minishell_t;

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
    void (*ptr)(input_t *input);
} keybind_t;


int my_minishell(char **env);
//int command_handler(minishell_t *minishell);
////command handler
//int check_path(minishell_t *minishell);
//int my_cd(minishell_t *minishell);
//int my_env(minishell_t *minishell);
//int my_setenv(minishell_t *minishell);
//int my_unsetenv(minishell_t *minishell);
//int my_exit(minishell_t *minishell);

//static const command_handler_t COMMAND_HANDLER_TAB[] = {
//    {"cd", &my_cd},
//    {"env", &my_env},
//    {"setenv", &my_setenv},
//    {"unsetenv", &my_unsetenv},
//    {"exit", &my_exit},
//    {NULL, NULL}
//};

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
minishell_t *init_struct(char **env);
char **sh_word_array(char *string, char *delimiter);

char *my_getenv(char *str, char **env);
int my_putstr_fd(char const *str, int fd);
char **my_tab_addline(char **tab, size_t size, char *str);
int print_dash_help(void);
char **my_tabdup(char **tab);
int tab_delline(char ***tab, int len, int line_to_del);
void remove_last_char(char **buffer, const size_t buffer_size);
//int is_piped(char *command_line);
int get_last_line_tab(char **tab);
int handle_signal(int wait_status);
void handle_error_tab(int i, int num_sig);
int handle_error(char *command);
int pipe_error(char **args, char *command);

void read_command(minishell_t *minishell);
//parsing
void parse_pipe(minishell_t *minishell, int index);
int check_pipes(minishell_t *minishell, int i, int *len);
int check_redirections(minishell_t *minishell, int i, int *len);
int redirect_left(minishell_t *minishell, int i, int *len);
int redirect_right(minishell_t *minishell, int i, int *len);

//input
char *parse_input(void);
void reset_term(struct termios *old);
void set_non_canonical(struct termios *old);
void arrow(input_t *input);
void delete(input_t *input);
int add_char(input_t *input);

static const keybind_t tab_keybinds[3] = {
        {'\033', &arrow},
        {127, &delete},
        {0, 0},
};

//handle_pipe
//int parse_pipe(minishell_t *minishell, char **line, char ***args);

//handle_redirections
//int find_redirection(char *command_line, minishell_t *minishell);

#endif /* !MINISHELL_H_ */
