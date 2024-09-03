# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/25 21:52:00 by hshimizu          #+#    #+#              #
#    Updated: 2024/09/03 22:21:23 by hshimizu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= PmergeMe

CXX			:= c++
CXXFLAGS	:= -Wall -Wextra -Werror
CXXFLAGS	+= -std=c++98 -g

SRCS		:= main.cpp
SRCS		+= PmergeMe.cpp

OBJS		:= $(SRCS:.cpp=.o)
DEPS		:= $(SRCS:.cpp=.d)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) -MMD -MP $< -o $@

clean:
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

-include $(DEPS)
