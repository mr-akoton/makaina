# ============================================================================= #
# VARIABLES

NAME		:= makaina

SRC_DIR		:= ./src
LIB_DIR		:= ./lib

UTL_DIR		:= ./utils
GRP_DIR		:= ./graphic
USI_DIR		:= ./ui
COR_DIR		:= ./core
ENG_DIR		:= ./engine

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
	CXXFLAGS = -Wall -Wextra -Wpedantic -O0 -std=c++17
endif

CXXFLAGS	+= -I $(INC_DIR) -I $(EXT_DIR) -I $(EXT_DIR)/imgui
LDFLAGS		:= -L $(LIB_DIR) -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl

RM			:= rm -rf

# ============================================================================ #
# SOURCES

# --------------------------------- C Files ---------------------------------- #

C_SRC		:= $(LIB_DIR)/glad.c

C_OBJ		:= $(C_SRC:.c=.o)

# -------------------------------- C++ Files --------------------------------- #

LIB_FILES	:= stb_image.cpp \
			   imgui.cpp \
			   imgui_demo.cpp \
			   imgui_draw.cpp \
			   imgui_impl_glfw.cpp \
			   imgui_impl_opengl3.cpp \
			   imgui_tables.cpp \
			   imgui_widgets.cpp \

UTL_FILES	:= getFileContent.cpp \

GRP_FILES	:= Texture.cpp \
			   Mesh.cpp \

USI_FILES	:= Interface.cpp \

COR_FILES	:= object/EBO.cpp \
			   object/VAO.cpp \
			   object/VBO.cpp \
			   Camera.cpp \
			   Shader.cpp \
			   Window.cpp \

ENG_FILES	:= Terrain.cpp \
			   Engine.cpp \

SRC_FILES	:= main.cpp

CXX_SRC		:= $(SRC_FILES) \
			   $(addprefix $(UTL_DIR)/, $(UTL_FILES)) \
			   $(addprefix $(GRP_DIR)/, $(GRP_FILES)) \
			   $(addprefix $(USI_DIR)/, $(USI_FILES)) \
			   $(addprefix $(COR_DIR)/, $(COR_FILES)) \
			   $(addprefix $(ENG_DIR)/, $(ENG_FILES)) \

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
