NAME = ircserv
CC = c++
FLAGS = -Wall -Wextra -Werror -std=c++98 
SRC =  main.cpp irc_server.cpp
HEADERS = irc_server.hpp

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