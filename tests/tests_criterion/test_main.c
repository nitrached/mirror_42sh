#include <criterion/criterion.h>
#include "my.h"
#include "minishell.h"

// Test du main avec argc invalide

Test(main_function, when_argument_is_dash_h_should_return_print_dash_help) {
    char *argv[] = {"./42sh", "-h", NULL};
    char *env[] = {NULL};
    int argc = 2;
    int result = main(argc, argv, env);
    cr_assert_eq(result, 0, "Expected return value: 0, got: %d", result);
}

