################################################################################
#                               VARIABLES                                      #
################################################################################

RMV = rm -rf
CPP = c++ 
CFLAGS = -Wall -Werror -Wextra -g -pedantic -std=c++98 #-fsanitize=address
NAME = btc 
TOTAL_FILES = $(words $(SOURCES))

DIRECTORIES_UTILS = obj
DIRECTORI_SOURCE = src
OBJECTS = $(addprefix $(DIRECTORIES_UTILS)/, $(SOURCES:.cpp=.o))
DEPENDENCIES = $(addprefix $(DIRECTORIES_UTILS)/, $(SOURCES:.cpp=.d))
INCLUDES = $(addprefix -I, inc)
SOURCES = main.cpp BitcoinExchange.cpp

################################################################################
#                               BOLD COLORS                                    #
################################################################################

END = \033[m
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
PURPLE = \033[35m
CIAN = \033[36m

################################################################################
#  FONT                                                                        #
################################################################################

ligth = \033[1m
dark = \033[2m
italic = \033[3m

################################################################################
#                               MAKE RULES                                     #
################################################################################

all: dir progress

print:
	@echo "$(INCLUDES)"
	@echo "$(OBJECTS)"
	@echo $(DIRECTORIES_UTILS) 
$(NAME): $(OBJECTS)
	$(CPP) $(CFLAGS) $(INCLUDES) $(OBJECTS) -o $(NAME)
	@echo "\n✅ ==== $(BLUE)$(ligth)Project $(NAME) compiled!$(END) ==== ✅"

$(DIRECTORIES_UTILS)/%.o:$(DIRECTORI_SOURCE)/%.cpp
	@printf "  $(ligth)Compiling $(BLUE)$<$(END)      "
	@$(CPP) $(CFLAGS) $(INCLUDES) -MMD -c $< -o $@
	@$(call progress,$<)

dir:
	-mkdir -p $(DIRECTORIES_UTILS)
progress: $(OBJECTS) $(NAME)

################################################################################
#                               CLEAN                                          #
################################################################################

clean:
	$(RMV) $(OBJECTS) $(DIRECTORIES_UTILS) $(NAME)
	echo "✅ ==== $(PURPLE)$(ligth)$(NAME) object files cleaned!$(END) ==== ✅"

fclean: clean
	$(RMV) $(NAME)
	echo "✅ ==== $(PURPLE)$(ligth)$(NAME) executable files and name cleaned!$(END) ==== ✅"

define progress
	@$(eval COMPILED_FILES=$(shell expr $(COMPILED_FILES) + 1))
	@bash -c 'PROG_BAR_WIDTH=50; \
	PROGRESS=$$(($(COMPILED_FILES) * $$PROG_BAR_WIDTH / $(TOTAL_FILES))); \
	EMPTY=$$(($$PROG_BAR_WIDTH - $$PROGRESS)); \
	PROGRESS=$$((PROGRESS < 0 ? 0 : PROGRESS)); \
	EMPTY=$$((EMPTY < 0 ? 0 : EMPTY)); \
	printf "\r$(ligth)[$(GREEN)"; \
	for ((i = 0; i < $$PROGRESS; i++)); do echo -n "█"; done; \
	for ((i = 0; i < $$EMPTY; i++)); do echo -n " "; done; \
	printf "$(END)$(ligth)] "; \
	printf "%d%%$(END)" $$((100 * $(COMPILED_FILES) / $(TOTAL_FILES)));'
endef

-include $(DEPENDENCIES)

re: fclean all
.PHONY: all clean progress fclean
COMPILED_FILES=0
.SILENT: