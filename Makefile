# ============================================================================ #
# VARIABLES

NAME	= makaina

SRC_DIR	= ./src
INC_DIR = ./inc
LIB_DIR = ./lib
EXT_DIR = ./ext

# ============================================================================ #
# COMPILATIONS SETTINGS

INCLUDES	= -I $(INC_DIR) -I $(LIB_DIR)

CC			= gcc
CFLAGS		= $(INCLUDES)

CXX			= g++
CXXFLAGS	= -Wall -Wextra -Werror -Wpedantic -O0 -std=c++17 -g \
			  $(INCLUDES)
LDFLAGS		= -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl

RM			= rm -rf

# ============================================================================ #
# SOURCES

EXT_C		= glad/glad.c
EXT_CXX		= imgui/imgui.cpp \
			  imgui/imgui_draw.cpp \
			  imgui/imgui_impl_glfw.cpp \
			  imgui/imgui_impl_opengl3.cpp \
			  imgui/imgui_tables.cpp \
			  imgui/imgui_widgets.cpp \
			  stb/stb_image.cpp

SRC			= component/Terrain.cpp \
			  core/object/EBO.cpp \
			  core/object/VAO.cpp \
			  core/object/VBO.cpp \
			  core/Camera.cpp \
			  core/Engine.cpp \
			  core/Shader.cpp \
			  core/Window.cpp \
			  graphic/mesh/MeshFlat.cpp \
			  graphic/mesh/Mesh.cpp \
			  graphic/mesh/MeshBasic.cpp \
			  graphic/texture/TextureFramebuffer.cpp \
			  graphic/texture/TextureNoise.cpp \
			  graphic/texture/TextureBasic.cpp \
			  graphic/texture/Texture.cpp \
			  util/iomanip.cpp \
			  main.cpp

OBJ			= $(addprefix $(SRC_DIR)/, $(SRC:.cpp=.o)) \
			  $(addprefix $(EXT_DIR)/, $(EXT_C:.c=.o)) \
			  $(addprefix $(EXT_DIR)/, $(EXT_CXX:.cpp=.o)) \

# ============================================================================ #
# RULES

all		: $(NAME)

$(NAME)	: $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)

clean	:
	$(RM) $(OBJ)

fclean	: clean
	$(RM) $(NAME)

re		: fclean all

# ============================================================================ #
# PHONY

.PHONY	: all clean fclean re
