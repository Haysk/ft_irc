NAME = ircTest
CC = clang++
HEAD = -Iinclude

# Flag [-MMD -MP] create an depedance with a [.d] files to hpp files
# Used to check if the hpp files changed
CPPFLAGS = -Wall -Wextra -std=c++98 -MMD -MP

# No need to edit the path of th file
# This will be automaticaly
FILES = mainTest.cpp \
		Datas.cpp \
		User.cpp \
		Channel.cpp \
		datasTest.cpp

SRC_PATH = $(shell find .. -type d)
vpath %.cpp $(foreach dir, $(SRC_PATH), $(dir))

OBJ_PATH = objs
OBJ = $(addprefix $(OBJ_PATH)/, $(FILES:%.cpp=%.o))


all :   $(NAME) 

$(NAME) : $(OBJ_PATH) $(OBJ)
	$(CC) $(CPPFLAGS) $(HEAD) $(OBJ) -o ${NAME}

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

$(OBJ_PATH)/%.o : %.cpp
	@$(CC) $(CPPFLAGS) $(HEAD) $< -o $@ -c

clean:
	rm -rf $(OBJ)
	rm -rf $(OBJ_PATH)
	
-include $(OBJ:.o=.d)

fclean: clean
	rm -rf $(NAME)

re: fclean all

