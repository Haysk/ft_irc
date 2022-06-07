NAME = ircserv
CC = clang++
HEAD = -Iinclude

# Flag [-MMD -MP] create an depedance with a [.d] files to hpp files
# Used to check if the hpp files changed
CPPFLAGS = -Wall -Wextra -std=c++98 -MMD -MP

# No need to edit the path of th file
# This will be automaticaly
FILES = Server.cpp \
		Datas.cpp \
		User.cpp \
		Channel.cpp \


SRC_PATH = $(shell find src -type d)
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

test:
	make -C unitTest

tclean:
	make -C unitTest clean

tfclean:
	make -C unitTest fclean

tre:
	make -C unitTest re

clean:
	rm -rf $(OBJ)
	rm -rf $(OBJ_PATH)
	
-include $(OBJ:.o=.d)

fclean: clean
	rm -rf $(NAME)

re: fclean all
