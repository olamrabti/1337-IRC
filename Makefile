NAME = ircserv
CC = c++
FLAGS = -Wall -Wextra -Werror -std=c++98 -fsanitize=address 
SRC =  main.cpp\
		NonBlockingSocket.cpp\
		Server.cpp Channel.cpp\
		Client.cpp\
		invite.cpp\
		mode.cpp\
		topic.cpp\
		join.cpp\
		kick.cpp\
		user.cpp\
		nick.cpp\
		pass.cpp\
		prvmsg.cpp\
		secbot.cpp\

HEADERS = NonBlockingSocket.hpp\
			Server.hpp Channel.hpp\
			Client.hpp\

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(SRC) -o $(NAME)
	
%.o: %.cpp $(HEADERS)
	$(CC) $(FLAGS) -c $< -o $@

clean : 
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all