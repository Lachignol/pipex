NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

SRCDIR = srcs
SRCBONUSDIR = srcs_bonus
INCLUDEDIR = includes
LIBFTDIR = libft
OBJS_DIR = objs
OBJS_BONUS_DIR = objs_bonus

LIBFT = $(LIBFTDIR)/libft.a

FILES = pipex.c pipex_func.c path_func.c check_integrity_func.c \

FILES_BONUS = pipex_bonus.c pipex_func_bonus.c here_doc_func_bonus.c path_func_bonus.c check_integrity_func_bonus.c error_func_bonus.c \

SRCS = $(addprefix $(SRCDIR)/, $(FILES))

SRCS_BONUS = $(addprefix $(SRCBONUSDIR)/, $(FILES_BONUS))

OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJS_DIR)/%.o)

OBJS_BONUS = $(SRCS_BONUS:$(SRCBONUSDIR)/%.c=$(OBJS_BONUS_DIR)/%.o)

INCLUDES = -I$(INCLUDEDIR) -I$(LIBFTDIR)

all: $(NAME)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(OBJS_BONUS_DIR):
	mkdir -p $(OBJS_BONUS_DIR)

$(OBJS_DIR)/%.o: $(SRCDIR)/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_BONUS_DIR)/%.o: $(SRCBONUSDIR)/%.c | $(OBJS_BONUS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFTDIR) -lft -o $@

bonus: $(OBJS_BONUS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_BONUS) -L$(LIBFTDIR) -lft -o $(NAME)_bonus

clean:
	rm -rf $(OBJS_DIR) $(OBJS_BONUS_DIR)
	$(MAKE) -C $(LIBFTDIR) clean

fclean: clean
	rm -f $(NAME) $(NAME)_bonus
	$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus
