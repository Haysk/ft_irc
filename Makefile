NAME = ircserv
CC = clang++
HEAD = -Iincludes

# Flag [-MMD -MP] create an depedance with a [.d] files to hpp files
# Used to check if the hpp files changed
CPPFLAGS = -Wall -Wextra -std=c++98 -MMD -MP -g3

# No need to edit the path of th file
# This will be automaticaly
FILES = main.cpp \
		Socket.cpp \
		Server.cpp \
		Channel.cpp \
		Command.cpp \
		Datas.cpp \
		User.cpp \
		utils.cpp \
		parsing_tester.cpp \
#		registration_tester.cpp \

SRC_PATH = $(shell find srcs -type d)
vpath %.cpp $(foreach dir, $(SRC_PATH), $(dir))

OBJ_PATH = objs
OBJ = $(addprefix $(OBJ_PATH)/, $(FILES:%.cpp=%.o))


all :   $(NAME) 

$(NAME) : $(OBJ_PATH) $(OBJ)
	@$(CC) $(CPPFLAGS) $(HEAD) $(OBJ) -o ${NAME}
	@echo "ircserv executable ready !"

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

$(OBJ_PATH)/%.o : %.cpp
	@$(CC) $(CPPFLAGS) $(HEAD) $< -o $@ -c
	@echo "Compiled "$<" successfully!"


clean:
	@rm -rf $(OBJ)
	@echo "objects files removed"
	@rm -rf $(OBJ_PATH)
	@echo "objects directory removed"
	
-include $(OBJ:.o=.d)

fclean: clean
	rm -rf $(NAME)

re: fclean all
