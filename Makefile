# ============================================================================= #
# VARIABLES

NAME		:= makaina

SRC_DIR		:= ./src
LIB_DIR		:= ./lib

UTL_DIR		:= ./util
GRP_DIR		:= ./graphic
COR_DIR		:= ./core
WRL_DIR		:= ./world

INC_DIR		:= ./include
EXT_DIR		:= ./external

BUILD_TYPE	?= debug

# ============================================================================ #
# COMPILER SETTINGS

CC			:= gcc
CFLAGS		:= -I $(INC_DIR) -I $(EXT_DIR)

CXX			:= g++

ifeq ($(BUILD_TYPE), release)
	CXXFLAGS = -Wall -Wextra -O2 -DNDEBUG -std=c++17
else
	CXXFLAGS = -Wall -Wextra -Werror -Wpedantic -g -O0 -std=c++17
endif

CXXFLAGS	+= -I $(INC_DIR) -I $(EXT_DIR)
LDFLAGS		:= -L $(LIB_DIR) -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl

RM			:= rm -rf

# ============================================================================ #
# SOURCES

# --------------------------------- C Files ---------------------------------- #

C_SRC		:= $(LIB_DIR)/glad.c

C_OBJ		:= $(C_SRC:.c=.o)

# -------------------------------- C++ Files --------------------------------- #

LIB_FILES	:= stb_image.cpp

UTL_FILES	:= iomanip.cpp \

GRP_FILES	:= Texture.cpp \
			   Mesh.cpp \

COR_FILES	:= object/EBO.cpp \
			   object/VAO.cpp \
			   object/VBO.cpp \
			   Camera.cpp \
			   Shader.cpp \
			   Window.cpp \

WRL_FILES	:= World.cpp \
			   terrainGenerator.cpp \

SRC_FILES	:= main.cpp

CXX_SRC		:= $(SRC_FILES) \
			   $(addprefix $(UTL_DIR)/, $(UTL_FILES)) \
			   $(addprefix $(GRP_DIR)/, $(GRP_FILES)) \
			   $(addprefix $(COR_DIR)/, $(COR_FILES)) \
			   $(addprefix $(WRL_DIR)/, $(WRL_FILES)) \

CXX_OBJ		:= $(addprefix $(LIB_DIR)/, $(LIB_FILES:.cpp=.o)) \
			   $(addprefix $(SRC_DIR)/, $(CXX_SRC:.cpp=.o)) \

# --------------------------------- Objects ---------------------------------- #

OBJ			:= $(C_OBJ) $(CXX_OBJ)

# ============================================================================ #
# RULES

all		: $(NAME)

$(NAME)	: $(C_OBJ) $(CXX_OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) $(LDFLAGS) -o $@

clean	:
	$(RM) $(OBJ)

fclean	: clean
	$(RM) $(NAME)

re		: fclean all

# ============================================================================ #
# PHONY

.PHONY	: all clean fclean re
