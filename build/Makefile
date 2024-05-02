

CXX=clang++
CXX_CUSTOM_INCLUDE_FLAGS=-I../src/main -I../src/window -I../src/entity -I../src/shader -I../src/camera -I../src/debug
CXX_EXTERNAL_INCLUDE_FLAGS=-I../src/external/GLFW/include -I../src/external/glad/include -I../src/external/glm
CXX_INCLUDE_FLAGS+=$(CXX_CUSTOM_INCLUDE_FLAGS)
CXX_INCLUDE_FLAGS+=$(CXX_EXTERNAL_INCLUDE_FLAGS)
CXXFLAGS=-std=c++17 -Wall -Wextra -O3
CXXFLAGS+=$(CXX_INCLUDE_FLAGS)


#SRC_FILES=../external/glad/src/glad.cpp ../src/Shader.cpp ../src/Window.cpp ../src/Camera.cpp ../src/main.cpp

SRC_FILES=../src/entity/Entities.cpp ../src/entity/vertexObjects.cpp ../src/shader/Shader.cpp ../src/window/Window.cpp ../src/camera/Camera.cpp ../src/main/InitializeEngine.cpp ../src/main/main.cpp
EXTERNAL_SRC_FILES=../src/external/glad/src/glad.cpp
OBJ_FILES=$(SRC_FILES:.cpp=.o)
EXE=start_graphics_engine

#-L../external/SFML-2.6.1/lib

LDFLAGS=-L../src/shader -L../src/external/GLFW/lib -lglfw -L../src/external/glad/lib -lGL
#export LD_LIBRARY_PATH=../src/external/SFML-2.6.1/lib



start_graphics_engine: obj/glad.o obj/Entities.o obj/vertexObjects.o obj/Shader.o obj/Window.o obj/Camera.o obj/InitializeEngine.o obj/main.o
		$(CXX) $(CXXFLAGS) -o start_graphics_engine obj/glad.o obj/Entities.o obj/vertexObjects.o obj/Shader.o obj/Window.o obj/Camera.o obj/InitializeEngine.o obj/main.o $(LDFLAGS)



obj/glad.o: ../src/external/glad/src/glad.cpp ../src/external/glad/include/glad/glad.hpp
		$(CXX) $(CXXFLAGS) -c ../src/external/glad/src/glad.cpp -o obj/glad.o

obj/Entities.o: ../src/entity/Entities.cpp ../src/entity/Entities.hpp ../src/entity/CoordinateTransformation.hpp
		$(CXX) $(CXXFLAGS) -c ../src/entity/Entities.cpp -o obj/Entities.o

obj/vertexObjects.o: ../src/entity/vertexObjects.cpp ../src/entity/vertexObjects.hpp
		$(CXX) $(CXXFLAGS) -c ../src/entity/vertexObjects.cpp -o obj/vertexObjects.o

obj/Shader.o: ../src/shader/Shader.cpp	../src/shader/Shader.hpp ../src/debug/LOG.hpp
		$(CXX) $(CXXFLAGS) -c ../src/shader/Shader.cpp -o obj/Shader.o

obj/Window.o: ../src/window/Window.cpp ../src/window/Window.hpp ../src/debug/LOG.hpp
		$(CXX) $(CXXFLAGS) -c ../src/window/Window.cpp -o obj/Window.o

obj/Camera.o: ../src/camera/Camera.cpp	../src/camera/Camera.hpp ../src/debug/LOG.hpp ../src/debug/RenderingInfoLog.hpp
		$(CXX) $(CXXFLAGS) -c ../src/camera/Camera.cpp -o obj/Camera.o

obj/InitializeEngine.o: ../src/main/InitializeEngine.cpp ../src/main/InitializeEngine.hpp ../src/debug/LOG.hpp ../src/entity/Entities.hpp ../src/debug/RenderingInfoLog.hpp ../src/entity/vertexObjects.hpp ../src/shader/Shader.hpp
		$(CXX) $(CXXFLAGS) -c ../src/main/InitializeEngine.cpp -o obj/InitializeEngine.o


#
#obj/main.o: ../src/main/main.cpp ../src/shader/Shader.hpp ../src/window/Window.hpp ../src/camera/Camera.hpp ../src/entity/Entities.hpp ../src/entity/CoordinateTransformation.hpp ../src/main/InitializeEngine.hpp ../src/debug/LOG.hpp
#	    $(CXX) $(CXXFLAGS) -c ../src/main/main.cpp -o obj/main.o

obj/main.o: ../src/main/main.cpp ../src/main/InitializeEngine.hpp
		$(CXX) $(CXXFLAGS) -c ../src/main/main.cpp -o obj/main.o

exp:	
		export LD_LIBRARY_PATH=../src/external/SFML-2.6.1/lib
 
clear:
		 rm -f obj/glad.o
		 rm -f obj/Entities.o
		 rm -f obj/vertexObjects.o
		 rm -f obj/Shader.o
		 rm -f obj/Window.o
		 rm -f obj/Camera.o
		 rm -f obj/InitializeEngine.o
		 rm -f obj/main.o
		 
run:
		./start_graphics_engine

run_make_only_if_compiles: start_graphics_engine
		./start_graphics_engine
		
c:
		rm -f start_graphics_engine






######################################_Not Needed_########################################################

#CXXFLAGS=-std=c++17 -Wall -O3 -I../include -I../../../../../usr/include -I../../../../../Downloads/glad/include

#LDFLAGS=-L../../../../../usr/lib -lglfw -L../../../../../Downloads/glad/lib -lglfw


# start_graphics_engine: glad.o Shader.o Window.o Camera.o main.o
		# $(CXX) $(CXXFLAGS) -o start_graphics_engine glad.o Shader.o Window.o Camera.o main.o $(LDFLAGS)
# 


# %.o: %.cpp
		 # $(CXX) $(CXXFLAGS) -c -o $@ $<
# 


# Rule to run make only if it compiles
#run_make_only_if_compiles: $(TARGET)
#	./$(TARGET)
