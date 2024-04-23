##
## EPITECH PROJECT, 2023
## Untitled (Workspace)
## File description:
## Makefile
##

NAME		= 42sh

SRCS		= src/main.c\
			  src/minishell.c\
			  src/parse_command.c\
			  src/read_command.c\
			  src/utiles/init_struct.c\
			  src/check_parsing/check_pipe.c\
			  src/check_parsing/check_redirections.c\
			  src/utiles/my_putstr_fd.c\
			  src/utiles/sh_word_array.c\
			  src/utiles/tab_del_line.c\
			  src/utiles/get_line.c\
			  src/utiles/my_getenv.c\
			  src/utiles/print_dash_help.c\
			  src/utiles/tab_addline.c\
			  src/utiles/my_tabdup.c\
			  src/utiles/get_last_line_tab.c\
			  src/utiles/handle_error.c\
			  src/utiles/is_piped.c


OBJS     = $(SRCS:.c=.o)

CFLAGS   = -Wall -Wextra -I include -I lib/include -g

	GREEN=\033[1;32m
	YELLOW=\033[1;93m
	GREY=\033[2;49m
	ITALIC=\033[3m
	NC=\033[0m

all: $(NAME)

$(NAME): build_lib $(OBJS)
		@ gcc -o $(NAME) $(OBJS) -L./lib -lmy

build_lib:
	make -C ./lib

clean:
	make fclean -C ./lib
	$(RM) $(OBJS)
	find . -name "#*#" -delete -o -name "*~" -delete
	$(RM) coding-style-reports.log
	$(RM) vgcore*
	clear

fclean: clean
	$(RM) a.out
	$(RM) lib/libmy.a
	$(RM) $(NAME)
	clear

re: fclean all

debug: fclean
debug: CFLAGS += -g
debug: all

.c.o:
	@ $(CC) -o $(subst .c,.o,$<) -c $< $(CFLAGS) \
		&& echo -e "[ ${GREEN}OK${NC} ] ${GREY}$<${NC}" \
		|| echo -e "[ ${YELLOW}KO${NC} ] ${ITALIC}$<${NC}"

.PHONY: re fclean clean all .c.o
