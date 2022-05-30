NAME = ircserv
CC = clang++
HEAD = -Iinclude
CFLAGS = -Wall -Wextra $(DEBUG) -std=c++98 
# DEBUG += -fsanitize=address

FILES = main.cpp \


SRC_PATH = $(shell find src -type d)
vpath %.c $(foreach dir, $(SRC_PATH), $(dir))

OBJ_PATH = objs
OBJ = $(addprefix $(OBJ_PATH)/, $(FILES:%.c=%.o))


all :   $(NAME) 

$(NAME) : $(OBJ_PATH) $(OBJ)
	$(CC) $(CFLAGS) $(HEAD) $(OBJ) -o ${NAME}

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

$(OBJ_PATH)/%.o : %.cpp
	@$(CC) $(CFLAGS) $(HEAD) -c $< -o $@ 


clean:
	rm -rf $(OBJ)
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -rf $(NAME)

re: fclean all