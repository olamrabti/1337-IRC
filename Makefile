NAME = ircserv
CC = c++
FLAGS = -Wall -Wextra -Werror -std=c++98 
SRC =  main.cpp NonBlockingSocket.cpp  Server.cpp
HEADERS = NonBlockingSocket.hpp  Server.hpp

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