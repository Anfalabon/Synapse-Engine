#############################################---ALL PRIMARY FLAGS---####################################################

CXX 						= clang++
CXXVERSION 					= -std=c++17
CXX_AGGRESSIVE_WARNINGS 	= -Werror
CXX_WARNING_FLAGS 			= -Wall -Wextra
CXX_MEMORY_DEBUGGER 		= -fsanitize=address
CXX_DEBUGGING_FLAGS 		= -g
CXX_OPTIMIZATION_LEVEL 		= -Ofast
CXX_MULTITHREADING_FLAGS 	= -fopenmp	#this is prebuilt on my Machine but maybe we need to install it on some other Machine
CXX_DEPENDENCIES_FLAGS 		= -MMD -MP


#############################################---INCLUDE FLAGS---########################################################

VENDOR_DIR = GLFW glad/include glm imageLoader irrKlang LuaScriptingLibs assimp



#also including the custom include flags allows us to include headers with ' <> ' than just ' "" '
CXX_CUSTOM_INCLUDE_FLAGS 	= -I../src
CXX_EXTERNAL_INCLUDE_FLAGS 	= $(foreach directory, $(VENDOR_DIR), -I../vendor/$(directory))

#$(info $(CXX_EXTERNAL_INCLUDE_FLAGS))

CXX_INCLUDE_FLAGS += $(CXX_CUSTOM_INCLUDE_FLAGS)
CXX_INCLUDE_FLAGS += $(CXX_EXTERNAL_INCLUDE_FLAGS)


#CXX_CUSTOM_INCLUDE_FLAGS+=-I../src/core -I../src/window -I../src/physics -I../src/utils -I../src/math -I../src/scene -I../src/renderer -I../src/camera -I../src/debug -I../src/scripting -I../src/events -I../src/audio
#CXX_EXTERNAL_INCLUDE_FLAGS=-I../vendor/GLFW/include -I../vendor/glad/include -I../vendor/glm -I../vendor/imageLoader -I../vendor/irrKlang/include -I../vendor/include/LuaScriptingLibs

#############################################---MERGE ALL CXX FLAGS---##################################################


CXXLDFLAGS 	 = -fopenmp

CXXFLAGS 	+= $(CXXVERSION)
CXXFLAGS 	+= $(CXX_WARNING_FLAGS)
CXXFLAGS 	+= $(CXX_DEBUGGING_FLAGS)
CXXFLAGS 	+= $(CXX_OPTIMIZATION_LEVEL)
CXXFLAGS 	+= $(CXX_DEPENDENCIES_FLAGS)
CXXFLAGS 	+= $(CXX_MULTITHREADING_FLAGS)
CXXFLAGS 	+= $(CXX_INCLUDE_FLAGS)


##############################################---LINKING LIBRARY FLAGS---###############################################


EXTERNAL_LIBRARY_DIRS 				= GLFW glad imageLoader irrKlang LuaScriptingLibs
COMPILER_SUPPORTED_LIBRARY_LINKS 	= -fopenmp
EXTERNAL_LIBRARY_LINKS 				= -lglfw -lGL -lstbimage -lIrrKlang -llua

#CXXLDFLAGS = $(foreach library, $(EXTERNAL_LIBRARY_DIRS), -L../vendor/)

# Will also automate this
LDFLAGS  =	-L../vendor/GLFW/lib -lglfw \
			-L../vendor/glad/lib -lGL \
			-L../vendor/imageLoader/lib -lstbimage -Wl, -rpath ../vendor/imageLoader/lib \
			-L../vendor/irrKlang/bin/linux-gcc-64 -lIrrKlang -Wl, -rpath ../vendor/irrKlang/bin/linux-gcc-64 \
			-L../vendor/irrKlang/lib -lIrrKlang \
			-L../vendor/LuaScriptingLibs -llua \
			-L../vendor/assimp -lassimp


#################################################---SET DIRECTORIES---##################################################


# Directories
#SRC_DIR = audio  camera  core  debug  editor  events  main  Makefile  math  physics  renderer  scene  scripting  ui  utils  window
SRC_DIR 			= ../src
VENDOR_SRC_DIR 		= ../vendor/glad
OBJ_DIR 			= obj
DEP_DIR 			= dep


#########################################---GENERATE OBJ FILES FROM SRC FILES---########################################

#SRC_FILES = $(foreach directory, $(SRC_DIR), $(wildcard ../src/$(directory)/*.cpp))

SRC_FILES 	= $(shell find $(SRC_DIR) -name '*.cpp')

# Print things out
#$(info SRC Files are $(SRC_FILES))

OBJ_FILES 	= $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
DEP_FILES 	= $(patsubst $(SRC_DIR)/%.cpp,$(DEP_DIR)/%.d,$(SRC_FILES))


VENDOR_SRC_FILES 	 =  $(shell find $(VENDOR_SRC_DIR) -name '*.cpp')
OBJ_FILES			+= $(patsubst $(VENDOR_SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(VENDOR_SRC_FILES))

###########################################---DEFINE MAIN EXECUTABLE FILE---############################################


EXECUTABLE 		 = bin/start_game_engine


################################################---LINK OBJ FILES---####################################################

# Link
$(EXECUTABLE): $(OBJ_FILES)
		$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

###########################################---COMPILE SOURCE FILES TO OBJ FILES---######################################

#$(dir $(DEP_FILES:$@.o=.d))

# Compile Source Codes
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
		@mkdir -p $(dir $@)
		$(CXX) $(CXXFLAGS) -c $< -o $@


# Compile Vendor Source codes
$(OBJ_DIR)/%.o: $(VENDOR_SRC_DIR)/%.cpp
		@mkdir -p $(dir $@)
		$(CXX) $(CXXFLAGS) -c $< -o $@

###############################---REMOVE ALL THE PRODUCED FILES BY MAKEFILE SCRIPT---###################################

clearAll:
		$(RM) -r $(OBJ_DIR) $(DEP_DIR) $(EXECUTABLE) ; mkdir $(OBJ_DIR) $(DEP_DIR)

######################################---INCLUDE DEPENDENCIES FOR SOURCE FILES---#######################################


# Bring all the dependency files in 'dependencies' directory

#-include $(DEP_FILES)
-include $(OBJ_FILES:.o=.d)


#################################################---RUN THE PROGRAM---##################################################

# run program
run:
		./$(EXECUTABLE)

#############################################---DEFINE OS SPECIFIC COMMANDS---#############################################


$(info CurrentOS: $(OS))

# Platform-specific settings
ifeq ($(OS), Windows_NT)
		MKDIR 	= mkdir
		RM 		= del
else
		MKDIR 	= mkdir -p
		RM 		= rm -rf
endif


