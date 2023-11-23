# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thmeyer <thmeyer@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/22 10:36:10 by thmeyer           #+#    #+#              #
#    Updated: 2023/11/23 12:57:21 by thmeyer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ##################################### #
#               VARIABLES               #
# ##################################### #

NAME		=	ircserv

UNAME		=	$(shell uname)

NOCOLOR		=	\033[0m
BGREEN		=	\033[1;32m

HEADER		=	includes/ft_irc.hpp

MAKEFILE	=	Makefile

CC			=	c++
CFLAGS 		= 	-Wall -Wextra -Werror
CPPFLAGS	=	-std=c++98

RM 			= 	rm -rf

# ##################################### #
#                 PATHS                 #
# ##################################### #

SRCS_PATH	=	sources/

SRC_PARSING_PATH		=	$(SRCS_PATH)parsing/
SRC_EXECUTING_PATH		=	$(SRCS_PATH)executing/

OBJ_PARSING_PATH		=	$(SRC_PARSING_PATH).objs/
OBJ_EXECUTING_PATH		=	$(SRC_EXECUTING_PATH).objs/

OBJS_DIRS	=	$(OBJ_PARSING_PATH) $(OBJ_EXECUTING_PATH) 


# ##################################### #
#                SOURCES                #
# ##################################### #

SRC_PARSING_FILES		=	parsing.cpp errors.cpp

SRC_EXECUTING_FILES		=	main.cpp

SRCS_PARSING		=	$(addprefix $(SRC_PARSING_PATH), $(SRC_PARSING_FILES))
SRCS_EXECUTING		=	$(addprefix $(SRC_EXECUTING_PATH), $(SRC_EXECUTING_FILES))

SRCS	=	$(SRCS_PARSING) $(SRCS_EXECUTING) 


# ##################################### #
#                OBJECTS                #
# ##################################### #

OBJS_PARSING		=	$(addprefix $(OBJ_PARSING_PATH), $(SRC_PARSING_FILES:.cpp=.o))
OBJS_EXECUTING		=	$(addprefix $(OBJ_EXECUTING_PATH), $(SRC_EXECUTING_FILES:.cpp=.o))

OBJS	=	$(OBJS_PARSING)	$(OBJS_EXECUTING)	

$(OBJ_PARSING_PATH)%.o: $(SRC_PARSING_PATH)%.cpp $(MAKEFILE) $(HEADER)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

$(OBJ_EXECUTING_PATH)%.o: $(SRC_EXECUTING_PATH)%.cpp $(MAKEFILE) $(HEADER)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<


# ##################################### #
#                 RULES                 #
# ##################################### #

all:		$(OBJS_DIRS) $(NAME)

$(OBJS_DIRS):
			mkdir -p $(OBJS_DIRS)

$(NAME):	$(OBJS)
ifeq ($(UNAME),Linux)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $(NAME) $(OBJS)
	@echo "$(BGREEN)Linux Compilation Done$(NOCOLOR)"
else ifeq ($(UNAME),Darwin)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $(NAME) $(OBJS)
	@echo "$(BGREEN)Mac OS Compilation Done$(NOCOLOR)"
endif

run:
			$(MAKE) all
			./$(NAME)

clean:
			$(RM) $(OBJS)
			@echo "$(BGREEN)Clean done$(NOCOLOR)"

fclean:
			$(MAKE) clean
			$(RM) $(NAME)
			$(RM) $(OBJS_DIRS)
			@echo "$(BGREEN)Fclean done$(NOCOLOR)"

re:
			$(MAKE) fclean
			$(MAKE) all

.PHONY:		all run clean fclean re