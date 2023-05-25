# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/18 12:39:13 by eralonso          #+#    #+#              #
#    Updated: 2023/05/25 17:04:18 by eralonso         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#----------------------------------->COLORS<-----------------------------------#
DEF_COLOR = \033[1;39m
WHITE = \033[1m
BLACK = \033[1;30m
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
PINK = \033[1;35m
CIAN = \033[1;36m

#------------------------------------>NAME<------------------------------------#
NAME = libft.a

#---------------------------------->VARS<--------------------------------------#
NULL :=	
SPACE := $(NULL) #

#---------------------------------->ROOTS<-------------------------------------#
INC_ROOT := inc/
SRC_ROOT := src/
OBJ_ROOT := .objs/

#----------------------------------->HEADER<-----------------------------------#
HEADERS := $(INC_ROOT)

#----------------------------------->DIRS<-------------------------------------#
SRC_DIRS	:=	./:ctype/:lists/:matrix/:stdio/:stdlib/:$\
				strings/:string/:unistd/:stdio/ft_printf/
				
SRC_DIRS	:=	$(subst :,$(SPACE),$(SRC_DIRS))
SRC_DIRS	:=	$(addprefix $(SRC_ROOT),$(SRC_DIRS))
SRC_DIRS	:=	$(subst $(SPACE),:,$(SRC_DIRS))

#----------------------------------->FILES<----–-------------------------------#
FILES =	ft_memset ft_bzero ft_memcpy ft_memmove \
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
		ft_strchri \
		ft_flags_checker ft_checker ft_printf ft_chars_utils \
		ft_nbrs_utils ft_ptr_utils

#----------------------------------->FILES<----–-------------------------------#
SRCS = $(addsuffix .c,$(FILES))

#------------------------------->OBJ && DEPS<----------------------------------#
OBJS = $(addprefix $(OBJ_ROOT),$(subst .c,.o,$(SRCS)))

DEP = $(addsuffix .d,$(basename $(OBJS)))

#----------------------------------->COMANDS<----------------------------------#
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
MDP = mkdir -p
AR = ar curs
MKFLAGS := --no-print-directory
INCLUDE = $(addprefix -I,$(HEADERS))

#----------------------------------->VPATHS<-----------------------------------#

vpath %.c $(SRC_DIRS)

#------------------------------------>RULES<-----------------------------------#
$(OBJ_ROOT)%.o: %.c
	$(MDP) $(@D)
	printf "$(PINK)      \rCompiling: $(YELLOW)$(<F)...$(DEF_COLOR)      \r"
	$(CC) -MT $@ $(CFLAGS) -MMD -MP $(INCLUDE) -c $< -o $@

all : 
	echo ""
	$(MAKE) $(MKFLAGS) $(NAME)

$(NAME) : $(OBJS)
	$(AR) $(NAME) $(OBJS)
	printf "\n$(GREEN)LIBRARY: '$(subst .a,,$@)' has been created.$(DEF_COLOR)\n"

clean :
	$(RM) -r $(OBJ_ROOT)

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

-include $(DEP)
