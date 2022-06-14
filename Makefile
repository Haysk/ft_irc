NAME	= mytest

CC	= clang++

CFLAGS	= -Wall -Werror -Wextra -std=c++98

LFLAGS	= -Wall -Werror Wextra -I. -lm

INC	= -Iincludes. 

SRCDIR	= srcs
INCDIR	= includes
OBJDIR	= objs

SRCS  := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(INCDIR)/*.hpp)
OBJS	= $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

RM	= rm -rf

$(NAME):	$(OBJS)
	@$(CC) $(OBJS) $(LFLAGS) -o $@
	@echo "Linking complete!"

$(OBJS):	$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@
	@echo "Compiled "$<" successfully!"

all:	$(NAME)

clean:
	$(RM) $(OBJS)

fclean:		clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:		all clean fclean re
