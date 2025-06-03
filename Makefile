UNAME_S := $(shell uname -s)
SDL2_PATH = $(HOME)/SDL2
SDL2_image_PATH = $(HOME)/SDL2_image
GLAD_INCLUDE = ./ext/glad/include/glad
EXT_INCLUDE = ./ext/glad/include
F_SANITIZE_ADDRESS = -fsanitize=address -g
EXPORT_SDL := $(shell export DYLD_LIBRARY_PATH="~/SDL2/lib:$DYLD_LIBRARY_PATH")

ifeq ($(UNAME_S),Linux)
    PLATFORM_DEFINES = -DLINUX
    LIBS = -lGL -lSDL2
endif

ifeq ($(UNAME_S),Darwin)
    PLATFORM_DEFINES = -DMACOS
    LIBS = -framework OpenGL -L$(SDL2_PATH)/lib -lSDL2 -L$(SDL2_image_PATH)/lib -lSDL2_image -fsanitize=address -g
endif

CXX = g++
CXXFLAGS = $(PLATFORM_DEFINES)
INCLUDE = -I$(SDL2_PATH)/include -I./include -I./ext/glad/include/glad -I./ext/glad/include -I$(SDL2_image_PATH)/include
LDFLAGS = $(LIBS)

SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:.cpp=.o)
GLAD_OBJ = ext/glad/src/glad.o
TARGET = scop

all: $(TARGET)
	echo $(EXPORT_SDL)

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