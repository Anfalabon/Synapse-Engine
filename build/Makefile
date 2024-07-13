

#############################################---ALL PRIMARY FLAGS---####################################################

CXX=clang++
CXXVERSION=-std=c++17
CXX_AGGRESSIVE_WARNINGS=-Werror
CXX_WARNING_FLAGS=-Wall -Wextra
CXX_MEMORY_DEBUGGER=-fsanitize=address
CXX_DEBUGGING_FLAGS=-g
CXX_OPTIMIZATION_LEVEL=-Ofast
CXX_DEPENDENCIES_FLAGS=-MMD -MP


#############################################---INCLUDE FLAGS---########################################################


#also including the custom include flags allows us to include headers with ' <> ' than just ' "" '
CXX_CUSTOM_INCLUDE_FLAGS=-I../src
#CXX_CUSTOM_INCLUDE_FLAGS+=-I../src/core -I../src/window -I../src/physics -I../src/utils -I../src/math -I../src/scene -I../src/renderer -I../src/camera -I../src/debug -I../src/scripting -I../src/events -I../src/audio
CXX_EXTERNAL_INCLUDE_FLAGS=-I../vendor/GLFW/include -I../vendor/glad/include -I../vendor/glm -I../vendor/imageLoader -I../vendor/irrKlang/include -I../vendor/include/LuaScriptingLibs
CXX_INCLUDE_FLAGS+=$(CXX_CUSTOM_INCLUDE_FLAGS)
CXX_INCLUDE_FLAGS+=$(CXX_EXTERNAL_INCLUDE_FLAGS)


#############################################---MERGE ALL CXX FLAGS---##################################################

CXXFLAGS+=$(CXXVERSION)
CXXFLAGS+=$(CXX_WARNING_FLAGS)
CXXFLAGS+=$(CXX_DEBUGGING_FLAGS)
CXXFLAGS+=$(CXX_OPTIMIZATION_LEVEL)

CXXLDFLAGS=-fopenmp
CXXFLAGS+=$(CXX_DEPENDENCIES_FLAGS)
CXXFLAGS+=$(CXXLDFLAGS)
CXXFLAGS+=$(CXX_INCLUDE_FLAGS)

#####################################---GENERATE OBJ AND DEP FILES FROM SRC FILES---####################################

#include Makefile.srcfiles

SRC_FILES=glad.cpp \
		LOG.cpp \
		FrameBuffer.cpp \
		PhysicsEngine.cpp \
		Buffer.cpp \
		Filesystem.cpp \
		VertexArray.cpp \
		VertexBuffer.cpp \
		IndexBuffer.cpp \
		Mesh.cpp \
		ModelLoader.cpp \
		Entities.cpp \
		Transformation.cpp \
		vertexObjects.cpp \
		Shader.cpp \
		Texture.cpp \
		Scene.cpp \
		Renderer.cpp \
		Window.cpp \
		Audio.cpp \
		Timer.cpp \
		Camera.cpp \
		ScriptingEngine.cpp \
		Engine.cpp \
		Application.cpp \
		main.cpp






OBJ_DIR=obj
DEP_DIR=dependencies


OBJ_FILES=$(SRC_FILES:%.cpp=$(OBJ_DIR)/%.o)
#DEP_FILES=$(SRC_FILES:%.cpp=$(DEP_DIR)/%.d)
#DEP_FILES=$(OBJ_FILES)


###########################################---DEFINE MAIN EXECUTABLE FILE---############################################


EXECUTABLE=bin/start_game_engine


#################################################---LINKING FLAGS---####################################################


LDFLAGS=-L../vendor/GLFW/lib -lglfw \
		-L../vendor/glad/lib -lGL \
		-L../vendor/imageLoader/lib -lstbimage -Wl, -rpath ../vendor/imageLoader/lib \
		-L../vendor/irrKlang/bin/linux-gcc-64 -lIrrKlang -Wl, -rpath ../vendor/irrKlang/bin/linux-gcc-64 \
		-L../vendor/irrKlang/lib -lIrrKlang \
		-L../vendor/LuaScriptingLibs -llua \


################################################---LINK OBJ FILES---####################################################
$(EXECUTABLE): $(OBJ_FILES)
		$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
########################################################################################################################


#$(OBJ_FILES)/%.o: $(SRC_FILES)/%.cpp
#		$(CXX) $(CXXFLAGS) -c $< -o $@

###########################################---COMPILE SOURCE FILES TO OBJ FILES---######################################




include ../src/Makefile



######################################---INCLUDE DEPENDENCIES FOR SOURCE FILES---#######################################

-include $(DEP_FILES)

###########################---MANUALLY SET THE ENVIROMENTAL VARIABLE FOR SHADRED LIBS---################################

exp:	
		export LD_LIBRARY_PATH=../vendor/SFML-2.6.1/lib


###############################---REMOVE ALL THE PRODUCED FILES BY MAKEFILE SCRIPT---###################################


clear:
		 rm -f obj/glad.o
		 rm -f obj/stb_image.o
		 rm -f obj/LOG.o
		 rm -f obj/FrameBuffer.o
		 rm -f obj/PhysicsEngine.o
		 rm -f obj/Buffer.o
		 rm -f obj/VertexArray.o
		 rm -f obj/VertexBuffer.o
		 rm -f obj/IndexBuffer.o
		 rm -f obj/Mesh.o
		 rm -f obj/ModelLoader.o
		 rm -f obj/Entities.o
		 rm -f obj/Transformation.o
		 rm -f obj/vertexObjects.o
		 rm -f obj/Shader.o
		 rm -f obj/Texture.o
		 rm -f obj/Scene.o
		 rm -f obj/Renderer.o
		 rm -f obj/Window.o
		 rm -f obj/Audio.o
		 rm -f obj/Timer.o
		 rm -f obj/Camera.o
		 rm -f obj/ScriptingEngine.o
		 rm -f obj/Engine.o
		 rm -f obj/Application.o
		 rm -f obj/main.o


clearAll:
		rm -rf $(POBJ_FILES) $(DEP_FILES)

run:
		./$(EXECUTABLE)

run_make_only_if_compiles: $(EXECUTABLE)
		./$(EXECUTABLE)
		
c:
		rm -f $(EXECUTABLE)






















###################################################_Not Needed_#########################################################

#CXXFLAGS=-std=c++17 -Wall -O3 -I../include -I../../../../../usr/include -I../../../../../Downloads/glad/include

#LDFLAGS=-L../../../../../usr/lib -lglfw -L../../../../../Downloads/glad/lib -lglfw


# start_graphics_engine: glad.o Shader.o Window.o Camera.o core.o
		# $(CXX) $(CXXFLAGS) -o start_graphics_engine glad.o Shader.o Window.o Camera.o core.o $(LDFLAGS)
# 


# %.o: %.cpp
		 # $(CXX) $(CXXFLAGS) -c -o $@ $<
# 


# Rule to run make only if it compiles
#run_make_only_if_compiles: $(TARGET)
#	./$(TARGET)


#
#obj/core.o: ../src/core/core.cpp ../src/shader/Shader.hpp ../src/window/Window.hpp ../src/camera/Camera.hpp ../src/scene/Entities.hpp ../src/scene/CoordinateTransformation.hpp ../src/core/InitializeEngine.hpp ../src/debug/LOG.hpp
#	    $(CXX) $(CXXFLAGS) -c ../src/core/core.cpp -o obj/core.o




#Will make it automatic instead of adding object file every time here
#bin/start_game_engine: obj/glad.o obj/stb_image.o obj/LOG.o obj/PhysicsEngine.o obj/Buffer.o obj/VertexArray.o obj/VertexBuffer.o obj/IndexBuffer.o obj/Mesh.o obj/ModelLoader.o obj/Entities.o obj/Transformation.o obj/vertexObjects.o obj/Shader.o obj/Texture.o obj/Scene.o obj/Renderer.o obj/Window.o obj/Audio.o obj/Timer.o obj/Camera.o obj/ScriptingEngine.o obj/Engine.o obj/Application.o obj/main.o
#		$(CXX) $(CXXFLAGS) -o bin/start_game_engine obj/glad.o obj/stb_image.o obj/LOG.o obj/PhysicsEngine.o obj/Buffer.o obj/VertexArray.o obj/VertexBuffer.o obj/IndexBuffer.o obj/Mesh.o obj/ModelLoader.o obj/Entities.o obj/Transformation.o obj/vertexObjects.o obj/Shader.o obj/Texture.o obj/Scene.o obj/Renderer.o obj/Window.o obj/Audio.o obj/Timer.o obj/Camera.o obj/ScriptingEngine.o obj/Engine.o obj/Application.o obj/main.o $(LDFLAGS)









#export LD_LIBRARY_PATH=../src/external/SFML-2.6.1/lib












#SRC_FILES=../external/glad/src/glad.cpp ../src/Shader.cpp ../src/Window.cpp ../src/Camera.cpp ../src/core.cpp
#SRC_FILES=../src/scene/Entities.cpp ../src/entity/vertexObjects.cpp ../src/shader/Shader.cpp ../src/renderer/Renderer.cpp ../src/window/Window.cpp ../src/camera/Camera.cpp ../src/core/InitializeEngine.cpp ../src/core/main.cpp
#EXTERNAL_SRC_FILES=../vendor/glad/src/glad.cpp
#OBJ_FILES=$(SRC_FILES:.cpp=.o)






#CXXFLAGS=-std=c++17 -Wall -Wextra -O3






#-L../external/SFML-2.6.1/lib