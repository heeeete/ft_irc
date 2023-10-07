CXX = c++

CXXFLAGS = -std=c++98
OPT			= -g -fsanitize=address

NAME = ircserv

SRCS = main.cpp \
		Server.cpp \
		Client.cpp \
		parsing.cpp \
		Channel.cpp \
		commands/cap.cpp \
		commands/pass.cpp \
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
