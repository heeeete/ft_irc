CXX = c++

CXXFLAGS 	= -std=c++98
OPT			= -Wall -Werror -Wextra

NAME = ircserv

SRC = main.cpp \
		Server.cpp \
		Client.cpp \
		parsing.cpp \
		Channel.cpp \

SRC_CMD = 	commands/pass.cpp \
			commands/nick.cpp \
			commands/user.cpp \
			commands/join.cpp \
			commands/ping.cpp \
			commands/invite.cpp \
			commands/kick.cpp \
			commands/mode.cpp \
			commands/notice.cpp \
			commands/part.cpp \
			commands/privmsg.cpp \
			commands/quit.cpp \
			commands/topic.cpp

DEPS = Server.hpp \
		Irc.hpp \
		Client.hpp \
		Channel.hpp \
		Message.hpp \
		DefineReplies.hpp


SRCS = $(SRC) $(SRC_CMD)

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS) $(DEPS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME) $(OPT)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
