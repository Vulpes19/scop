UNAME_S := $(shell uname -s)
HOMEBREW_PATH = /opt/homebrew
GLAD_INCLUDE = ./ext/glad/include/glad
EXT_INCLUDE = ./ext/glad/include
F_SANITIZE_ADDRESS = -fsanitize=address -g

ifeq ($(UNAME_S),Linux)
    PLATFORM_DEFINES = -DLINUX
    LIBS = -lGL -lSDL2
endif

ifeq ($(UNAME_S),Darwin)
    PLATFORM_DEFINES = -DMACOS
    LIBS = -framework OpenGL -L$(HOMEBREW_PATH)/lib -lSDL2 -L$(HOMEBREW_PATH)/lib -lSDL2_image -L$(HOMEBREW_PATH)/lib -lSDL2_ttf -fsanitize=address -g
endif

CXX = g++
CXXFLAGS = $(PLATFORM_DEFINES)
INCLUDE = -I$(HOMEBREW_PATH)/include/SDL2 -I./include -I./ext/glad/include/glad -I./ext/glad/include
LDFLAGS = $(LIBS)

SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:.cpp=.o)
GLAD_OBJ = ext/glad/src/glad.o
TARGET = scop

all: $(TARGET)

re: fclean all

$(TARGET): $(OBJS) $(GLAD_OBJ)
	$(CXX) -o $@ $^ $(GLAD) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

$(GLAD_OBJ): ext/glad/src/glad.c
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

fclean: clean
	rm -f $(TARGET)