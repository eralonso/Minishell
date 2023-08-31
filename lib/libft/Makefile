# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/13 11:42:31 by eralonso          #+#    #+#              #
#    Updated: 2023/07/13 11:42:32 by eralonso         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#----------------------------------->COLORS<-----------------------------------#
DEF_COLOR	:=	\033[1;39m
WHITE		:=	\033[1m
BLACK		:=	\033[1;30m
RED			:=	\033[1;31m
GREEN		:=	\033[1;32m
YELLOW		:=	\033[1;33m
BLUE		:=	\033[1;34m
PINK		:=	\033[1;35m
CIAN		:=	\033[1;36m

#---------------------------------->NAME<--------------------------------------#
NAME		:=	libft.a

#---------------------------------->VARS<--------------------------------------#
NULL 		:=	
SPACE 		:=	$(NULL) #

#---------------------------------->ROOTS<-------------------------------------#
SRC_ROOT	:=	src/
OBJ_ROOT	:=	.objs/
DEP_ROOT	:=	.deps/
INC_ROOT	:=	inc/

#---------------------------------->HEADERS<-----------------------------------#
HEADERS 	:=	$(INC_ROOT)

#----------------------------------->DIRS<-------------------------------------#
SRC_DIRS	:=	./:ctype/:stype/:lists/:matrix/:stdio/:stdlib/:$\
				strings/:string/:unistd/:stdio/ft_printf/
SRC_DIRS	:=	$(subst :,$(SPACE),$(SRC_DIRS))
SRC_DIRS	:=	$(addprefix $(SRC_ROOT),$(SRC_DIRS))
SRC_DIRS	:=	$(subst $(SPACE),:,$(SRC_DIRS))

#----------------------------------->FILES<----–-------------------------------#
FILES		:=	ft_memset ft_bzero ft_memcpy ft_memmove \
				ft_memchr ft_memcmp ft_strlen ft_isalpha \
				ft_isdigit ft_isalnum ft_isascii ft_isprint \
				ft_toupper ft_tolower ft_strchr ft_strrchr \
				ft_strncmp ft_strrncmp ft_strlcpy ft_strlcat \
				ft_strnstr ft_atoi ft_calloc ft_strdup \
				ft_substr ft_strjoin ft_strtrim ft_split ft_itoa \
				ft_strmapi ft_striteri ft_putchar_fd ft_putstr_fd \
				ft_putendl_fd ft_putnbr_fd \
				ft_lstnew ft_lstadd_front ft_lstsize \
				ft_lstlast ft_lstadd_back ft_lstclear \
				ft_lstdelone ft_lstiter ft_lstmap \
				get_next_line ft_nbrlen_base ft_matrixlen ft_isnumdup \
				ft_isint ft_isnum ft_atoll ft_close ft_isspace \
				ft_strchri ft_strcat ft_isblank ft_strchrjoin \
				ft_strwnchr  ft_isempty ft_strnstri ft_matrixjoin \
				ft_matrixdup ft_strtolower ft_strtoupper \
				ft_matrixjoin_size ft_free ft_free_size ft_matrix_remainder \
				ft_flags_checker ft_checker ft_printf ft_chars_utils \
				ft_nbrs_utils ft_ptr_utils

#----------------------------------->FILES<----–-------------------------------#
SRCS		:=	$(addsuffix .c,$(FILES))

#------------------------------->OBJ && DEPS<----------------------------------#
OBJS		:=	$(addprefix $(OBJ_ROOT),$(subst .c,.o,$(SRCS)))
DEPS		:=	$(addprefix $(DEP_ROOT),$(subst .c,.d,$(SRCS)))

#----------------------------------->COMANDS<----------------------------------#
INCLUDE		:=	$(addprefix -I,$(HEADERS))
RM			:=	rm -rf
MKD			:=	mkdir -p
MK			:=	Makefile
CFLAGS		:=	-Wall -Wextra -Werror #-fsanitize=address
MKFLAGS		:=	--no-print-directory
MUTE		:=	&> /dev/null
CC			:=	gcc
AR 			:=	ar curs

#----------------------------------->VPATHS<-----------------------------------#

vpath %.c $(SRC_DIRS)
vpath %.d $(DEP_ROOT)

#<-------------------------------->FUNCTIONS<-------------------------------->#

define msg_creating
	printf "\r$(3)$(1): $(YELLOW)$(2).$(DEF_COLOR)                                                                 \r"
	sleep 0.01
	printf "\r$(3)$(1): $(YELLOW)$(2)..$(DEF_COLOR)                                                                \r"
	sleep 0.01
	printf "\r$(3)$(1): $(YELLOW)$(2)...$(DEF_COLOR)                                                               \r"
	sleep 0.01
endef

create_dir = $(shell $(MKD) $(1))

#------------------------------------>RULES<-----------------------------------#

all : 
	echo ""
	$(MAKE) $(MKFLAGS) $(NAME)

$(DEP_ROOT)%.d : %.c | $(call create_dir,$(DEP_ROOT))
	$(call msg_creating,Dependence,$*,$(BLUE))
	$(CC) $(CFLAGS) -MMD -MF $@ $(INCLUDE) -c $< && rm -rf $(addsuffix .o,$*)
	sed -i.tmp '1 s|:| $@ :|' $@ && rm -rf $(addsuffix .tmp,$@)
	sed -i.tmp '1 s|^$*|$(OBJ_ROOT)$*|' $@ && rm -rf $(addsuffix .tmp,$@)

$(OBJ_ROOT)%.o : %.c %.d | $(call create_dir,$(OBJ_ROOT))
	$(call msg_creating,Object,$*,$(PINK))
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME) : $(DEPS) $(OBJS)
	$(AR) $(NAME) $(OBJS)
	printf "\n$(GREEN)LIBRARY: '$(subst .a,,$@)' has been created.$(DEF_COLOR)\n"

clean :
	$(RM) $(OBJ_ROOT) $(DEP_ROOT)

fclean :
	$(MAKE) $(MKFLAGS) clean
	$(RM) $(NAME)
	echo "$(RED)LIBRARY: '$(subst .a,,$(NAME))' has been removed.$(DEF_COLOR)"

re :
	$(MAKE) $(MKFLAGS) fclean
	$(MAKE) $(MKFLAGS) all
	echo "$(CIAN)LIBRARY: '$(subst .a,,$(NAME))' has been remake$(DEF_COLOR)"
	echo ""

.PHONY : all bonus clean fclean re

.SILENT :

-include $(DEPS)
