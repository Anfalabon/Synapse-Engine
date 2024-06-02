

CXX=clang++
CXXVERSION=-std=c++17
CXX_WARNING_FLAGS=-Wall -Wextra
CXX_DEBUGGING_FLAGS=-g
CXX_OPTIMIZATION_LEVEL=-O3

CXX_CUSTOM_INCLUDE_FLAGS=-I../src/core -I../src/window -I../src/physics -I../src/multithreading -I../src/math -I../src/entity -I../src/shader -I../src/renderer -I../src/camera -I../src/debug
CXX_EXTERNAL_INCLUDE_FLAGS=-I../vendor/GLFW/include -I../vendor/glad/include -I../vendor/glm
CXX_INCLUDE_FLAGS+=$(CXX_CUSTOM_INCLUDE_FLAGS)
CXX_INCLUDE_FLAGS+=$(CXX_EXTERNAL_INCLUDE_FLAGS)

#CXXFLAGS=-std=c++17 -Wall -Wextra -O3

CXXFLAGS+=$(CXXVERSION)
CXXFLAGS+=$(CXX_WARNING_FLAGS)
CXXFLAGS+=$(CXX_DEBUGGING_FLAGS)
CXXFLAGS+=$(CXX_OPTIMIZATION_LEVEL)

CXXLDFLAGS=-fopenmp
CXXFLAGS+=$(CXXLDFLAGS)
CXXFLAGS+=$(CXX_INCLUDE_FLAGS)


#SRC_FILES=../external/glad/src/glad.cpp ../src/Shader.cpp ../src/Window.cpp ../src/Camera.cpp ../src/core.cpp

SRC_FILES=../src/entity/Entities.cpp ../src/entity/vertexObjects.cpp ../src/shader/Shader.cpp ../src/renderer/renderEntity.cpp ../src/window/Window.cpp ../src/camera/Camera.cpp ../src/core/InitializeEngine.cpp ../src/core/main.cpp
EXTERNAL_SRC_FILES=../vendor/glad/src/glad.cpp
OBJ_FILES=$(SRC_FILES:.cpp=.o)
EXE=start_graphics_engine

#-L../external/SFML-2.6.1/lib

LDFLAGS=-L../src/shader -L../vendor/GLFW/lib -lglfw -L../vendor/glad/lib -lGL
#export LD_LIBRARY_PATH=../src/external/SFML-2.6.1/lib



start_game_engine: obj/glad.o obj/PhysicsEngine.o obj/Entities.o obj/vertexObjects.o obj/Shader.o obj/renderEntity.o obj/Window.o obj/Camera.o obj/InitializeEngine.o obj/main.o
		$(CXX) $(CXXFLAGS) -o start_game_engine obj/glad.o obj/PhysicsEngine.o obj/Entities.o obj/vertexObjects.o obj/Shader.o obj/renderEntity.o obj/Window.o obj/Camera.o obj/InitializeEngine.o obj/main.o $(LDFLAGS)



obj/glad.o: ../vendor/glad/src/glad.cpp ../vendor/glad/include/glad/glad.hpp
		$(CXX) $(CXXFLAGS) -c ../vendor/glad/src/glad.cpp -o obj/glad.o


obj/PhysicsEngine.o: ../src/physics/PhysicsEngine.cpp
		$(CXX) $(CXXFLAGS) -c ../src/physics/PhysicsEngine.cpp -o obj/PhysicsEngine.o


obj/Entities.o: ../src/entity/Entities.cpp ../src/entity/Entities.hpp ../src/entity/CoordinateTransformation.hpp ../src/physics/PhysicsEngine.hpp
		$(CXX) $(CXXFLAGS) -c ../src/entity/Entities.cpp -o obj/Entities.o

obj/vertexObjects.o: ../src/entity/vertexObjects.cpp ../src/entity/vertexObjects.hpp
		$(CXX) $(CXXFLAGS) -c ../src/entity/vertexObjects.cpp -o obj/vertexObjects.o

obj/Shader.o: ../src/shader/Shader.cpp	../src/shader/Shader.hpp ../src/debug/LOG.hpp ../src/shader/GLSL/vertexShaderSource1.glslv ../src/shader/GLSL/fragmentShaderSource1.glslf
		$(CXX) $(CXXFLAGS) -c ../src/shader/Shader.cpp -o obj/Shader.o

obj/renderEntity.o: ../src/renderer/renderEntity.cpp ../src/renderer/renderEntity.hpp
		$(CXX) $(CXXFLAGS) -c ../src/renderer/renderEntity.cpp -o obj/renderEntity.o

obj/Window.o: ../src/window/Window.cpp ../src/window/Window.hpp ../src/debug/LOG.hpp
		$(CXX) $(CXXFLAGS) -c ../src/window/Window.cpp -o obj/Window.o

obj/Camera.o: ../src/camera/Camera.cpp	../src/camera/Camera.hpp ../src/debug/LOG.hpp ../src/debug/RenderingInfoLog.hpp ../src/physics/PhysicsEngine.hpp ../src/camera/Cursor.hpp
		$(CXX) $(CXXFLAGS) -c ../src/camera/Camera.cpp -o obj/Camera.o

obj/InitializeEngine.o: ../src/core ../src/core ../src/debug/LOG.hpp ../src/entity/Entities.hpp ../src/debug/RenderingInfoLog.hpp ../src/entity/vertexObjects.hpp ../src/shader/Shader.hpp ../src/renderer/renderEntity.hpp ../src/entity/entitiesAttributesData.hpp ../src/multithreading/runParallel.hpp
		$(CXX) $(CXXFLAGS) -c ../src/core/InitializeEngine.cpp -o obj/InitializeEngine.o


#
#obj/core.o: ../src/core/core.cpp ../src/shader/Shader.hpp ../src/window/Window.hpp ../src/camera/Camera.hpp ../src/entity/Entities.hpp ../src/entity/CoordinateTransformation.hpp ../src/core/InitializeEngine.hpp ../src/debug/LOG.hpp
#	    $(CXX) $(CXXFLAGS) -c ../src/core/core.cpp -o obj/core.o

obj/main.o: ../src/core ../src/core
		$(CXX) $(CXXFLAGS) -c ../src/core/main.cpp -o obj/main.o

exp:	
		export LD_LIBRARY_PATH=../vendor/SFML-2.6.1/lib
 
clear:
		 rm -f obj/glad.o
		 rm -f obj/PhysicsEngine.o
		 rm -f obj/Entities.o
		 rm -f obj/vertexObjects.o
		 rm -f obj/Shader.o
		 rm -f obj/renderEntity.o
		 rm -f obj/Window.o
		 rm -f obj/Camera.o
		 rm -f obj/InitializeEngine.o
		 rm -f obj/main.o
		 
run:
		./start_game_engine

run_make_only_if_compiles: start_game_engine
		./start_game_engine
		
c:
		rm -f start_game_engine






######################################_Not Needed_########################################################

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
