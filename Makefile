CXX = c++

CXXFLAGS = -std=c++98
OPT			= -g -fsanitize=address

NAME = ircserv

SRCS = main.cpp \
		Server.cpp \
		Client.cpp \
		Channel.cpp \
		parsing.cpp \
		commands/invite.cpp \
		commands/join.cpp \
		commands/kick.cpp \
		commands/mode.cpp \
		commands/nick.cpp \
		commands/notice.cpp \
		commands/part.cpp \
		commands/pass.cpp \
		commands/ping.cpp \
		commands/privmsg.cpp \
		commands/quit.cpp \
		commands/topic.cpp \
		commands/user.cpp 
		
DEPS = Server.hpp \
		Irc.hpp \
		Client.hpp \
		Channel.hpp \
		Message.hpp \
		DefineReplies.hpp

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
