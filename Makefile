## File stuff
SHELL		=	/bin/zsh

FNAMES		=	vector_test.cpp stack_test.cpp map_test.cpp\
				main.cpp

SRCS		= $(addprefix $(SRCS_DIR)/,$(FNAMES))
SPEED_SRCS	= $(addprefix $(SRCS_DIR)/,speed_test.cpp)
OBJS		= $(addprefix $(OBJS_DIR)/,$(notdir $(FNAMES:.cpp=.o)))
DEPS		= $(addprefix $(DEPS_DIR)/,$(notdir $(FNAMES:.cpp=.d)))

INCLUDE_DIR	= include
SRCS_DIR	= src
OBJS_DIR	= build
DEPS_DIR	= $(OBJS_DIR)
## Compilation

CXX			= c++
CXXFLAGS		= -Wall -Werror -Wextra -std=c++98 -pedantic\
				  #-g -fsanitize=address -fsanitize=leak
INCLUDES	= -I $(INCLUDE_DIR)
LIBS		=

## Other
NAME			= tests
NAME_FT_SPEED	= ft_speed
NAME_STD_SPEED	= std_speed
RM				= rm -rf
MAKE			= make -s

ECHO			= echo -e


# Colors
BLACK		= \033[0;30m
RED			= \033[0;31m
GREEN		= \033[0;32m
ORANGE		= \033[0;33m
BLUE		= \033[0;34m
PURPLE		= \033[0;35m
CYAN		= \033[0;36m
GRAY		= \033[0;37m
WHITE		= \033[0;38m
RESET		= \033[0m


## Targets
all: $(NAME) speed

speed: $(NAME_FT_SPEED) $(NAME_STD_SPEED)

$(NAME_FT_SPEED): $(SPEED_SRCS)
	@$(ECHO) "$(GREEN)>>>>> Creating $(RESET)$(@)$(RESET)"
	@$(CXX) $(CXXFLAGS) -D STD=0 $(INCLUDES) $(SPEED_SRCS) -o $@

$(NAME_STD_SPEED): $(SPEED_SRCS)
	@$(ECHO) "$(GREEN)>>>>> Creating $(RESET)$(@)$(RESET)"
	@$(CXX) $(CXXFLAGS) -D STD=1 $(INCLUDES) $(SPEED_SRCS) -o $@

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp | $(OBJS_DIR)
	@$(ECHO) "$(GREEN)>>>>> Compiling $(RESET)$(notdir $<)$(GREEN) -> $(RESET)$(notdir $@)$(RESET)"
	@$(CXX) $(CXXFLAGS) -MMD -MP -c $(INCLUDES) $< -o $@

$(OBJS_DIR):
	@mkdir $(OBJS_DIR)
	@$(ECHO) "$(CYAN)Creating directory $(BLUE)'$(WHITE)$(OBJS_DIR)$(BLUE)'$(RESET)"

# regular targets
$(NAME): $(OBJS)
	@$(ECHO) "$(GREEN)>>>>> Linking <<<<<$(RESET)"
	$(CXX) $(CXXFLAGS) $(OBJS) $(LIBS) -o $(NAME)

clean:
	@$(ECHO) "$(GREEN)>>>>> Cleaning <<<<<$(RESET)"
	@$(RM) $(OBJS) $(DEPS)

fclean: clean
	@$(ECHO) "Applying full clean"
	@$(RM) $(OBJS_DIR) $(DEPS_DIR) $(NAME) $(NAME_FT_SPEED) $(NAME_STD_SPEED)

re: fclean all

vars:
	@$(ECHO) "$(GREEN)CFLAGS: $(WHITE)$(CXXFLAGS)$(RESET)"
	@$(ECHO) "$(GREEN)CC: $(WHITE)$(CXX)$(RESET)"
	@$(ECHO) "$(GREEN)FNAMES: $(WHITE)$(FNAMES)$(RESET)"
	@$(ECHO) "$(GREEN)SRCS: $(WHITE)$(SRCS)$(RESET)"
	@$(ECHO) "$(GREEN)OBJS: $(WHITE)$(OBJS)$(RESET)"
	@$(ECHO) "$(GREEN)DEPS: $(WHITE)$(DEPS)$(RESET)"

.PHONY: all clean fclean re init

-include $(DEPS)
