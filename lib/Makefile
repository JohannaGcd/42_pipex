# ---------*---------- Makefile ----------*----------

NAME = libftprintfgnl.a

####### INGREDIENTS ########

SRC_DIR 	:= src
DIR_LIBFT	:= libft
DIR_PRINTF	:= ft_printf
DIR_GNL		:= get_next_line

SRCS_PRINTF	:= ft_printf.c ft_printf.h print_address.c print_char.c \
			   print_digit_bighex.c print_digit.c print_digit_unsigned.c print_string.c
SRCS_GNL	:= get_next_line.c get_next_line_utils.c
SRCS_LIBFT	:= ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
			   ft_isdigit.c ft_isprint.c ft_itoa.c \
			   ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
			   ft_putendl_fd.c ft_putstr_fd.c ft_putnbr_fd.c ft_split.c ft_strchr.c ft_strdup.c \
			   ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c \
			   ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_lstsize.c \
			   ft_toupper.c ft_lstnew.c ft_lstadd_back.c ft_lstclear.c ft_lstdelone.c ft_lstadd_front.c ft_lstlast.c
##			   ft_lstiter.c ft_lstmap.c \

SRCS_LIBFT		:= $(SRCS_LIBFT:%=$(SRC_DIR)/$(DIR_LIBFT)/%)
SRCS_PRINTF		:= $(SRCS_PRINTF:%=$(SRC_DIR)/$(DIR_PRINTF)/%)
SRCS_GNL		:= $(SRCS_GNL:%=$(SRC_DIR)/$(DIR_GNL)/%)

BUILD_DIR		:= .build
OBJ_LIBFT		:= $(SRCS_LIBFT:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
OBJ_PRINTF		:= $(SRCS_PRINTF:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
OBJ_GNL			:= $(SRCS_GNL:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

######## UTENSILS ########

CFLAGS			:= -Wall -Wextra -Werror -g

RM 				:= rm -rf

DIR_PUP			= mkdir -p $(@D)

######## RECIPES ########

all: $(NAME)

$(NAME): $(OBJ_LIBFT) $(OBJ_PRINTF) $(OBJ_GNL)
	ar -rcs $(NAME) $(OBJ_LIBFT) $(OBJ_PRINTF) $(OBJ_GNL)
	$(info created $(NAME))

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_PUP)
	cc $(CFLAGS) -c $< -o $@
	$(info compiled $< into $@)

clean:
	$(RM) $(BUILD_DIR)

fclean: clean
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

print-%:
	$(info $($*))

######## SPEC ########

.PHONY: clean fclean
