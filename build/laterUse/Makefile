CXX = clang++
CXXDEPFLAGS = -MMD -MP
CXXINCLUDEFLAGS = -I../vendor/GLFW/include -I../vendor/glad/include -I../vendor/glm
CXX_LINKER_FLAGS = -L../vendor/GLFW/lib -lglfw -L../vendor/glad/lib -lGL -L../vendor/glm/lib
CXXFLAGS = -Wall -Wextra -O3 -std=c++17 -fopenmp $(CXXINCLUDEFLAGS) $(CXX_LINKER_FLAGS) $(CXXDEPFLAGS)


# Directories
SRC_DIRS = ../../vendor/glad/src ../../src/camera ../../src/core ../../src/debug ../../src/entity ../../src/multithreading ../../src/physics ../../src/renderer ../../src/shader ../../src/window

# Source files
#SRC_FILES = $(wildcard ../vendor/glad/src/*.cpp ../src/camera/*.cpp ../src/core/*.cpp ../src/debug/*.cpp ../src/entity/*.cpp ../src/multithreading/*.cpp ../src/physics/*.cpp ../src/renderer/*.cpp ../src/shader/*.cpp ../src/window/*.cpp)

SRC_FILES = $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.cpp))

# Object files
OBJ_FILES = $(SRC_FILES:.cpp=.o)

# Dependency files
DEP_FILES = $(OBJ_FILES:.o=.d)

# Executable
EXEC = start_game_engine

# Default target
all: $(EXEC)

# Link
$(EXEC): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Include dependency files
-include $(DEP_FILES)

# Clear

clear:
	rm -rf $(OBJ_FILES) $(DEP_FILES)

c: 
	rm -rf $(EXEC)

run:
	./$(EXEC)

# Phony targets
.PHONY: all clear
