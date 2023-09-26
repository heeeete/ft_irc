CXX = c++

CXXFLAGS = -std=c++98 -Wall -Wextra -Wall

NAME = ircserv

SRCS = main.cpp \
		Server.cpp

# DEPS = ScalarConve

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS) $(DEPS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
