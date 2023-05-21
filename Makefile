# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/22 10:08:41 by eralonso          #+#    #+#              #
#    Updated: 2023/05/21 13:14:41 by eralonso         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#<--------------------------------->COLORS<----------------------------------->#
DEF_COLOR	:=	\033[1;97m
WHITE_BOLD	:=	\033[1m
BLACK		:=	\033[1;90m
RED			:=	\033[1;91m
GREEN		:=	\033[1;92m
YELLOW		:=	\033[1;93m
BLUE		:=	\033[1;94m
PINK		:=	\033[1;95m
CIAN		:=	\033[1;96m

#<--------------------------------->NAME<------------------------------------>#
NULL		:=	
SPACE		:=	$(NULL) #

#<--------------------------------->NAME<------------------------------------>#
NAME		:=	minishell

#<--------------------------------->ROOTS<----------------------------------->#
LIB_ROOT	:=	lib/

ER_LIB_ROOT	:=	$(LIB_ROOT)er_lib/
LIBFT_ROOT	:=	$(ER_LIB_ROOT)libft/
PRINTF_ROOT	:=	$(ER_LIB_ROOT)ft_printf/
RDLINE_ROOT	:=	$(LIB_ROOT)readline/

SRC_ROOT	:=	src/
OBJ_ROOT	:=	.objs/
DEP_ROOT	:=	.deps/
INC_ROOT	:=	inc/

#<-------------------------------->LIBRARYS<--------------------------------->#
LIB_A		:=	$(LIBFT_ROOT)libft.a $(PRINTF_ROOT)libftprintf.a \
				$(RDLINE_ROOT)libreadline.a $(RDLINE_ROOT)libhistory.a

LIB_ADD_DIR	:=	-L$(RDLINE_ROOT) -L$(LIBFT_ROOT) -L$(PRINTF_ROOT) 

LIB_SEARCH	:=	-lreadline -lhistory -ltermcap -lft -lftprintf

LIB_EX		:=	readline history termcap ft ftprintf
LIB_EX		:=	$(addprefix lib,$(addsuffix .a,$(LIB_EX)))

#<-------------------------------->HEADERS<---------------------------------->#
HEADERS		=	$(INC_ROOT)
HEADERS		+=	$(PRINTF_ROOT)$(INC_ROOT)
HEADERS		+=	$(LIBFT_ROOT)
HEADERS		+=	$(RDLINE_ROOT)

#<---------------------------------->DIRS<----------------------------------->#
SRC_DIRS	:=	./:built-ins/:utils/:debug/:parser/
SRC_DIRS	:=	$(subst :,$(SPACE),$(SRC_DIRS))
SRC_DIRS	:=	$(addprefix $(SRC_ROOT),$(SRC_DIRS))
SRC_DIRS	:=	$(subst $(SPACE),:,$(SRC_DIRS))

LIB_DIRS	:=	$(LIB_ROOT):$(ER_LIB_ROOT):$(LIBFT_ROOT):$(PRINTF_ROOT):$(RDLINE_ROOT)

#<--------------------------------->FILES<---------------------------------->#
FILES		:=	main validate_input parse_env block_management cmd_create \
				echo utils split_cmd validate_utils debug_cmd

#<--------------------------------->SRCS<----------------------------------->#
SRCS		:=	$(addsuffix .c,$(FILES))

#<----------------------------->OBJS && DEPS<------------------------------->#
OBJS		:=	$(addprefix $(OBJ_ROOT),$(subst .c,.o,$(SRCS)))
DEPS		:=	$(addprefix $(OBJ_ROOT),$(subst .c,.d,$(SRCS)))

#<-------------------------------->COMANDS<---------------------------------->#
INCLUDE		:=	$(addprefix -I,$(HEADERS))
RM			:=	rm -rf
MKD			:=	mkdir -p
MK			:=	Makefile
CFLAGS		:=	-Wall -Wextra -Werror # -fsanitize=address
MKFLAGS		:=	--no-print-directory
MUTE		:=	&> /dev/null
CC			:=	gcc

#<--------------------------------->VPATHS<---------------------------------->#

vpath %.c $(SRC_DIRS)

#<--------------------------------->RULES<----------------------------------->#
$(OBJ_ROOT)%.o : %.c $(LIB_A) $(MK)
	$(MKD) $(@D)
	printf "\r$(PINK)Compiling: $(YELLOW)$(notdir $<).$(DEF_COLOR)          							          						\r"
	sleep 0.2
	printf "\r$(PINK)Compiling: $(YELLOW)$(notdir $<)..$(DEF_COLOR)                   			 										\r"
	sleep 0.2
	printf "\r$(PINK)Compiling: $(YELLOW)$(notdir $<)...$(DEF_COLOR)            		        										\r"
	sleep 0.2
	$(CC) $(CFLAGS) -MMD -DREADLINE_LIBRARY=1 $(INCLUDE) -c $< -o $@ && printf "$(GREEN)SUCCESS$(DEF_COLOR)                               \r" && sleep 0.2 || (printf "$(RED)\n\tFAILURE: $(<F)\n$(DEF_COLOR)\n" && exit 1)

all :
	$(MAKE) librarys
	$(MAKE) $(MKFLAGS) $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIB_ADD_DIR) $(LIB_SEARCH) $(LIB_A) -o $@
	echo "\n$(GREEN)Minishell has been compiled\nNOS LO COMEMOS$(DEF_COLOR)"

librarys :
	$(MAKE) $(MKFLAGS) -C $(ER_LIB_ROOT)
	$(MAKE) $(MKFLAGS) rdline

rdline :
	pwd $(MUTE)
	cd ./lib/readline/ $(MUTE) && ./configure $(MUTE)
	make -C ./lib/readline/ $(MUTE)

clean :
	$(MAKE) $(MKFLAGS) clean -C $(RDLINE_ROOT)
	$(MAKE) $(MKFLAGS) clean -C $(ER_LIB_ROOT)
	$(RM) $(OBJ_ROOT)
	echo ""
	echo "$(RED)All OBJS && DEPS has been removed$(DEF_COLOR)"
	echo ""

fclean :
	$(MAKE) $(MKFLAGS) clean
	$(MAKE) $(MKFLAGS) fclean -C $(ER_LIB_ROOT)
	$(RM) $(NAME)
	echo ""
	echo "$(RED)Program has been removed$(DEF_COLOR)"

re :
	$(MAKE) $(MKFLAGS) fclean
	$(MAKE) $(MKFLAGS) all
	echo ""
	echo "$(CIAN)Minishell has been recompiled$(DEF_COLOR)"

.PHONY : all clean fclean re librarys rdline

.SILENT :

# .LIBPATTERNS : lib%.a lib%.so

-include $(DEPS)