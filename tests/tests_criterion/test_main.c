#include <criterion/criterion.h>
#include "my.h"
#include "minishell1.h"

// Test du main avec argc invalide
Test(main, argc_invalid)
{
    char *argv[] = {"program_name", "argument1", NULL};
    char *env[] = {"env_var1=value1", "env_var2=value2", NULL};
    int result = main(2, argv, env);

    cr_assert_eq(result, 84, "Expected return value: 84");
}

// Test du main avec argc valide
Test(main, argc_valid)
{
    char *argv[] = {"program_name", NULL};
    char *env[] = {"env_var1=value1", "env_var2=value2", NULL};
    int result = main(1, argv, env);

    cr_assert_eq(result, 0, "Expected return value: 0");
}

// Test de l'initialisation de la structure minishell1_t
Test(main, init_struct)
{
    char *argv[] = {"program_name", NULL};
    char *env[] = {"env_var1=value1", "env_var2=value2", NULL};

    minishell1_t *minishell = innit_struct(env);
    cr_assert_not_null(minishell, "Expected non-null minishell structure");
    free(minishell);
}

// Test de l'appel de la fonction minishell1
Test(main, minishell1_call)
{
    char *argv[] = {"program_name", NULL};
    char *env[] = {"env_var1=value1", "env_var2=value2", NULL};
    int result = main(1, argv, env);

    minishell1_t *minishell = innit_struct(env);
    cr_assert_eq(result, minishell1(minishell), "Expected return value from minishell1");
    free(minishell);
}
