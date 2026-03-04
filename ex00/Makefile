NAME = btc
CXX = c++ -std=c++20
CXXFLAGS = -Wall -Wextra -Werror
SRC_DIR = src/
OBJ_DIR = obj/
INC_DIR = include/
SRCS = $(SRC_DIR)main.cpp $(SRC_DIR)BitcoinExchange.cpp
OBJS = $(SRCS:$(SRC_DIR)%.cpp=$(OBJ_DIR)%.o)
HEADERS = $(INC_DIR)BitcoinExchange.hpp

all: $(NAME)

$(NAME) : $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp $(HEADERS) | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
