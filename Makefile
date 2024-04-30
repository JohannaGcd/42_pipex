# ------------ Makefile ------------ #

NAME 			:= pipex

# ------------ Ingredients ------------ #

SRCS			:= test.c
OBJS			:= $(SRCS:.c=.o)

LIBS			:= ftprintfgnl
LIBS_TARGET		:= lib/libftprintfgnl.a

# ------------ Utensils ------------ #

CFLAGS			:= -Wall -Wextra -Werror -g -fsanitize=address
RM				:= rm -f

# ------------ Recipes ------------ #

all: $(NAME)

$(NAME): $(OBJS) $(LIBS_TARGET)
	cc $(CFLAGS) $(OBJS) -L $(dir $(LIBS_TARGET)) -l $(LIBS) -o $(NAME)

$(B_NAME): $(B_OBJ) $(LIBS_TARGET)
	cc $(CFLAGS) $(B_OBJ) -L $(dir $(LIBS_TARGET)) -l $(LIBS) -o $(B_NAME)

%.o:%.c
	cc $(CFLAGS) -c $< -o $@

$(LIBS_TARGET):
	$(MAKE) -C $(dir $(LIBS_TARGET))

clean:
	$(MAKE) clean -C $(dir $(LIBS_TARGET))
	$(RM) $(OBJS)
	$(RM) $(B_OBJ)

fclean: clean
	$(MAKE) fclean -C $(dir $(LIBS_TARGET))
	$(RM) $(NAME) 
	$(RM) bonus/$(B_NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

print-%:
	$(info $($*))

# ------------ Specifications ------------ #

.PHONY: clean fclean re new all
