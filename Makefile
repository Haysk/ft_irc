NAME	= parser

SDIR	= ./srcs/

ODIR	= ./objs/

IDIR	= ./includes/

DDIR	= ./deps/

SRCS	= $(wildcard $(SDIR)*.cpp)

OBJS	= $(SRCS:$(SDIR)%.cpp=$(ODIR)%.o)

DEP	= $(OBJS:$(ODIR)%.o=$(DDIR)%.d)

FLAGS	= -Wall -Werror -Wextra -MMD -MP -std=c++98

RM	= rm -rf

$(ODIR)%.o: $(SDIR)%.cpp
	c++ $(FLAGS) $(INC) -o $@ -c $< -I $(IDIR)

all:	$(NAME)

$(NAME):	$(OBJS)
	c++ $(FLAGS) $(INC) $(OBJS) -o $(NAME)

-include $(DEP)

clean:
	$(RM) $(OBJS)
	$(RM) $(DEP)

fclean:		clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:		all clean fclean re
