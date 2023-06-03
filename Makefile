# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/22 10:08:41 by eralonso          #+#    #+#              #
#    Updated: 2023/06/03 19:08:45 by eralonso         ###   ########.fr        #
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
NAME		:=	minishell

#<--------------------------------->VARS<------------------------------------>#
NULL		:=	
SPACE		:=	$(NULL) #

#<--------------------------------->ROOTS<----------------------------------->#
LIB_ROOT	:=	lib/

LIBFT_ROOT	:=	$(LIB_ROOT)libft/
RDLINE_ROOT	:=	$(LIB_ROOT)readline/

SRC_ROOT	:=	src/
OBJ_ROOT	:=	.objs/
DEP_ROOT	:=	.deps/
INC_ROOT	:=	inc/

#<-------------------------------->LIBRARYS<--------------------------------->#
LIB_A		:=	$(RDLINE_ROOT)libreadline.a $(RDLINE_ROOT)libhistory.a \
				$(LIBFT_ROOT)libft.a 

LIB_ADD_DIR	:=	-L$(RDLINE_ROOT) -L$(LIBFT_ROOT)

LIB_SEARCH	:=	-lreadline -lhistory -ltermcap -lft

#<-------------------------------->HEADERS<---------------------------------->#
HEADERS		:=	$(INC_ROOT)
HEADERS		+=	$(addsuffix $(INC_ROOT),$(LIBFT_ROOT))
HEADERS		+=	$(RDLINE_ROOT)

#<---------------------------------->DIRS<----------------------------------->#
SRC_DIRS	:=	./:built-ins/:utils/:debug/:parser/
SRC_DIRS	:=	$(subst :,$(SPACE),$(SRC_DIRS))
SRC_DIRS	:=	$(addprefix $(SRC_ROOT),$(SRC_DIRS))
SRC_DIRS	:=	$(subst $(SPACE),:,$(SRC_DIRS))

#<--------------------------------->FILES<---------------------------------->#
FILES		:=	main validate_input parse_env echo utils \
				validate_utils debug_cmd tokenizer token_utils \
				tk_checker stair stair_utils lstt_utils conversions \
				cmd_utils tk_cutter 

#<--------------------------------->SRCS<----------------------------------->#
SRCS		:=	$(addsuffix .c,$(FILES))

#<----------------------------->OBJS && DEPS<------------------------------->#
OBJS		:=	$(addprefix $(OBJ_ROOT),$(subst .c,.o,$(SRCS)))
DEPS		:=	$(addprefix $(DEP_ROOT),$(subst .c,.d,$(SRCS)))

#<-------------------------------->COMANDS<---------------------------------->#
INCLUDE		:=	$(addprefix -I,$(HEADERS))
RM			:=	rm -rf
MKD			:=	mkdir -p
MK			:=	Makefile
CFLAGS		:=	-Wall -Wextra -Werror -fsanitize=address
MKFLAGS		:=	--no-print-directory
MUTE		:=	&> /dev/null
CC			:=	gcc

#<--------------------------------->VPATHS<---------------------------------->#

vpath %.c $(SRC_DIRS)
vpath %.d $(DEP_ROOT)

#<-------------------------------->FUNCTIONS<-------------------------------->#

define msg_creating
	printf "\r$(3)$(1): $(YELLOW)$(2).$(DEF_COLOR)                                                                 \r"
	sleep 0.1
	printf "\r$(3)$(1): $(YELLOW)$(2)..$(DEF_COLOR)                                                                \r"
	sleep 0.1
	printf "\r$(3)$(1): $(YELLOW)$(2)...$(DEF_COLOR)                                                               \r"
	sleep 0.1
endef

create_dir = $(shell $(MKD) $(1))

#<--------------------------------->RULES<----------------------------------->#

# TA GUAY  && printf "$(GREEN)SUCCESS$(DEF_COLOR)                               \r" && sleep 0.2 || (printf "$(RED)\n\tFAILURE: $(<F)\n$(DEF_COLOR)\n" && exit 1)
all :
	$(MAKE) $(MKFLAGS) librarys
	$(MAKE) $(MKFLAGS) $(NAME)

librarys :
	$(MAKE) $(MKFLAGS) -C $(LIBFT_ROOT)
	$(MAKE) $(MKFLAGS) rdline

$(DEP_ROOT)%.d : %.c | $(call create_dir,$(DEP_ROOT))
	$(CC) $(CFLAGS) -MMD -MF $@ -DREADLINE_LIBRARY=1 $(INCLUDE) -c $< && rm -rf $(addsuffix .o,$*)
	sed -i.tmp '1 s|:| $@ :|' $@ && rm -rf $(addsuffix .tmp,$@)
	sed -i.tmp '1 s|^$*|$(OBJ_ROOT)$*|' $@ && rm -rf $(addsuffix .tmp,$@)

$(OBJ_ROOT)%.o : %.c %.d $(LIB_A) | $(call create_dir,$(OBJ_ROOT))
	$(call msg_creating,Object,$*,$(PINK))
	$(CC) $(CFLAGS) -DREADLINE_LIBRARY=1 $(INCLUDE) -c $< -o $@

$(NAME) : $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIB_ADD_DIR) $(LIB_SEARCH) $(LIB_A) -o $@
	echo "\n$(GREEN)Minishell has been compiled\nNOS LO COMEMOS$(DEF_COLOR)"

rdline :
	pwd $(MUTE)
	cd ./lib/readline/ $(MUTE) && ./configure $(MUTE)
	make -C ./lib/readline/ $(MUTE)

clean :
	$(MAKE) $(MKFLAGS) clean -C $(RDLINE_ROOT)
	$(MAKE) $(MKFLAGS) clean -C $(LIBFT_ROOT)
	$(RM) $(OBJ_ROOT) $(DEP_ROOT)
	echo ""
	echo "$(RED)All OBJS && DEPS has been removed$(DEF_COLOR)"
	echo ""

fclean :
	$(MAKE) $(MKFLAGS) clean
	$(MAKE) $(MKFLAGS) fclean -C $(LIBFT_ROOT)
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

ifeq (0,$(shell cd $(DEP_ROOT) $(MUTE); echo $$?))
-include $(DEPS)
endif