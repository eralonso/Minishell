# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/22 10:08:41 by eralonso          #+#    #+#              #
#    Updated: 2023/05/14 18:11:35 by eralonso         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#<--------------------------------->COLORS<----------------------------------->#
DEF_COLOR	=	\033[1;99m
WHITE_BOLD	=	\033[1m
BLACK		=	\033[1;90m
RED			=	\033[1;91m
GREEN		=	\033[1;92m
YELLOW		=	\033[1;93m
BLUE		=	\033[1;94m
PINK		=	\033[1;95m
CIAN		=	\033[1;96m

#<--------------------------------->NAME<------------------------------------>#
NAME		=	minishell

#<--------------------------------->DIRS<------------------------------------>#
LIBS_DIR	=	lib/

ER_LIB_DIR	=	$(LIBS_DIR)er_lib/
LIBFT_DIR	=	$(ER_LIB_DIR)libft/
PRINTF_DIR	=	$(ER_LIB_DIR)ft_printf/

RDLINE_DIR	=	$(LIBS_DIR)readline/

SRC_DIR		=	src/
OBJ_DIR		=	objs/

#<-------------------------------->LIBRARYS<--------------------------------->#
LIB_A		=	$(LIBFT_DIR)libft.a $(PRINTF_DIR)libftprintf.a \
				$(RDLINE_DIR)libreadline.a $(RDLINE_DIR)libhistory.a

LIB_SEARCH	=	-L$(RDLINE_DIR) -lreadline -lhistory -ltermcap -L$(LIBFT_DIR) \
				-L$(PRINTF_DIR) -lft -lftprintf

#<-------------------------------->HEADERS<---------------------------------->#
HEADERS		=	inc/
HEADERS		+=	$(PRINTF_DIR)inc/
HEADERS		+=	$(LIBFT_DIR)
HEADERS		+=	$(RDLINE_DIR)

#<--------------------------------->FILES<---------------------------------->#
FILES		=	minishell validate_input env parser built_echo utils

#<--------------------------------->SRCS<----------------------------------->#
SRCS		=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(FILES)))

#<----------------------------->OBJS && DEPS<------------------------------->#
OBJS		=	$(addprefix $(OBJ_DIR), $(subst .c,.o,$(SRCS)))
DEPS		=	$(subst .o,.d,$(OBJS))

#<-------------------------------->COMANDS<---------------------------------->#
INCLUDE		=	$(addprefix -I,$(HEADERS))
RM			=	rm -rf
MKD			=	mkdir -p
MK			=	Makefile
CFLAGS		=	-Wall -Wextra -Werror # -fsanitize=address
MKFLAGS		=	--no-print-directory
MUTE		=	&> /dev/null
CC			=	gcc

#<--------------------------------->RULES<----------------------------------->#
$(OBJ_DIR)%.o	:	%.c $(MK) $(LIB_A)
	@$(MKD) $(dir $@)
	@printf "$(PINK)Compiling: $(YELLOW)$(notdir $<)...$(DEF_COLOR)                    \r"
	@$(CC) $(CFLAGS) -MMD -DREADLINE_LIBRARY=1  $(INCLUDE) -c $< -o $@

all				: 
	@$(MAKE) librarys
	@$(MAKE) $(MKFLAGS) $(NAME)

$(NAME)			:	$(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIB_SEARCH) $(LIB_A) -o $@
	@echo "\n$(GREEN)Minishell has been compiled\nNOS LO COMEMOS$(DEF_COLOR)"

librarys		:
	@$(MAKE) $(MKFLAGS) -C $(ER_LIB_DIR)
	@$(MAKE) $(MKFLAGS) rdline

rdline			:
	@pwd ${MUTE}
	@cd ./lib/readline/ ${MUTE} && ./configure ${MUTE}
	@make -C ./lib/readline/ ${MUTE}

clean			:
	@$(MAKE) $(MKFLAGS) clean -C $(RDLINE_DIR)
	@$(MAKE) $(MKFLAGS) clean -C $(ER_LIB_DIR)
	@$(RM) $(OBJ_DIR)
	@echo ""
	@echo "$(RED)All OBJS && DEPS has been removed$(DEF_COLOR)"
	@echo ""

fclean			:
	@$(MAKE) $(MKFLAGS) clean
	@$(MAKE) $(MKFLAGS) fclean -C $(ER_LIB_DIR)
	@$(RM) $(NAME)
	@echo ""
	@echo "$(RED)Program has been removed$(DEF_COLOR)"

re				:
	@$(MAKE) $(MKFLAGS) fclean
	@$(MAKE) $(MKFLAGS) all
	@echo ""
	@echo "$(CIAN)Minishell has been recompiled$(DEF_COLOR)"

.PHONY			: all clean fclean re librarys rdline

-include		$(DEPS)