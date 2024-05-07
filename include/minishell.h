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

int my_minishell(char **env);
int command_handler(minishell_t *minishell);
//command handler
int check_path(minishell_t *minishell);
int my_cd(minishell_t *minishell);
int my_env(minishell_t *minishell);
int my_setenv(minishell_t *minishell);
int my_unsetenv(minishell_t *minishell);
int my_exit(minishell_t *minishell);

static const command_handler_t COMMAND_HANDLER_TAB[] = {
    {"cd", &my_cd},
    {"env", &my_env},
    {"setenv", &my_setenv},
    {"unsetenv", &my_unsetenv},
    {"exit", &my_exit},
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

//handle_pipe
int parse_pipe(minishell_t *minishell, char **line, char ***args);

//handle_redirections
int find_redirection(char *command_line, minishell_t *minishell);

    #define USER_INPUT minishell->user_input
    #define ENV minishell->env
    #define OLD_CD minishell->old_cd
    #define INDEX minishell->command_index
    #define STATUS minishell->status
    #define P_STATUS minishell->pipe_status

#endif /* !MINISHELL_H_ */
