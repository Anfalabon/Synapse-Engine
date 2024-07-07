

CXX=clang++
CXXVERSION=-std=c++17
CXX_AGGRESSIVE_WARNINGS=-Werror
CXX_WARNING_FLAGS=-Wall -Wextra
CXX_MEMORY_DEBUGGER=-fsanitize=address
CXX_DEBUGGING_FLAGS=-g
CXX_OPTIMIZATION_LEVEL=-O3

#also including the custom include flags allows us to include headers with ' <> ' than just ' "" '
CXX_CUSTOM_INCLUDE_FLAGS=-I../src/core -I../src/window -I../src/physics -I../src/multithreading -I../src/math -I../src/scene -I../src/shader -I../src/renderer -I../src/camera -I../src/debug
CXX_EXTERNAL_INCLUDE_FLAGS=-I../vendor/GLFW/include -I../vendor/glad/include -I../vendor/glm -I../vendor/imageLoader -I../vendor/irrKlang/include
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

SRC_FILES=../src/scene/Entities.cpp ../src/entity/vertexObjects.cpp ../src/shader/Shader.cpp ../src/renderer/Renderer.cpp ../src/window/Window.cpp ../src/camera/Camera.cpp ../src/core/InitializeEngine.cpp ../src/core/main.cpp
EXTERNAL_SRC_FILES=../vendor/glad/src/glad.cpp
OBJ_FILES=$(SRC_FILES:.cpp=.o)
EXE=start_graphics_engine

#-L../external/SFML-2.6.1/lib

LDFLAGS=-L../src/shader -L../vendor/GLFW/lib -lglfw -L../vendor/glad/lib -lGL -L../vendor/irrKlang/bin -L../vendor/irrKlang/lib
#export LD_LIBRARY_PATH=../src/external/SFML-2.6.1/lib


bin/start_game_engine: obj/glad.o obj/stb_image.o obj/LOG.o obj/PhysicsEngine.o obj/Buffer.o obj/VertexArray.o obj/VertexBuffer.o obj/IndexBuffer.o obj/Mesh.o obj/ModelLoader.o obj/Entities.o obj/Transformation.o obj/vertexObjects.o obj/Shader.o obj/Texture.o obj/Scene.o obj/Renderer.o obj/Window.o obj/Audio.o obj/Timer.o obj/Camera.o obj/Engine.o obj/Application.o obj/main.o
		$(CXX) $(CXXFLAGS) -o bin/start_game_engine obj/glad.o obj/stb_image.o obj/LOG.o obj/PhysicsEngine.o obj/Buffer.o obj/VertexArray.o obj/VertexBuffer.o obj/IndexBuffer.o obj/Mesh.o obj/ModelLoader.o obj/Entities.o obj/Transformation.o obj/vertexObjects.o obj/Shader.o obj/Texture.o obj/Scene.o obj/Renderer.o obj/Window.o obj/Audio.o obj/Timer.o obj/Camera.o obj/Engine.o obj/Application.o obj/main.o $(LDFLAGS)




obj/glad.o: ../vendor/glad/src/glad.cpp ../vendor/glad/include/glad/glad.hpp
		$(CXX) $(CXXFLAGS) -c ../vendor/glad/src/glad.cpp -o obj/glad.o

obj/stb_image.o: ../vendor/imageLoader/stb_image.cpp ../vendor/imageLoader/stb_image.h
		$(CXX) $(CXXFLAGS) -c ../vendor/imageLoader/stb_image.cpp -o obj/stb_image.o

obj/LOG.o: ../src/debug/LOG.cpp ../src/debug/LOG.hpp
		$(CXX) $(CXXFLAGS) -D __debug__ -c ../src/debug/LOG.cpp -o obj/LOG.o


obj/PhysicsEngine.o: ../src/physics/PhysicsEngine.cpp ../src/physics/PhysicsEngine.hpp
		$(CXX) $(CXXFLAGS) -c ../src/physics/PhysicsEngine.cpp -o obj/PhysicsEngine.o

obj/Buffer.o: ../src/scene/Buffer.cpp ../src/scene/Buffer.hpp
		$(CXX) $(CXXFLAGS) -c ../src/scene/Buffer.cpp -o obj/Buffer.o

obj/VertexArray.o: ../src/scene/VertexArray.cpp ../src/scene/VertexArray.hpp ../src/scene/VertexBuffer.hpp ../src/scene/IndexBuffer.hpp
		$(CXX) $(CXXFLAGS) -c ../src/scene/VertexArray.cpp -o obj/VertexArray.o


obj/VertexBuffer.o: ../src/scene/VertexBuffer.cpp ../src/scene/VertexBuffer.hpp
		$(CXX) $(CXXFLAGS) -c ../src/scene/VertexBuffer.cpp -o obj/VertexBuffer.o


obj/IndexBuffer.o: ../src/scene/IndexBuffer.cpp ../src/scene/IndexBuffer.hpp
		$(CXX) $(CXXFLAGS) -c ../src/scene/IndexBuffer.cpp -o obj/IndexBuffer.o


obj/Mesh.o: ../src/scene/Mesh.cpp ../src/scene/Mesh.hpp
		$(CXX) $(CXXFLAGS) -c ../src/scene/Mesh.cpp -o obj/Mesh.o

obj/ModelLoader.o: ../src/scene/ModelLoader.cpp ../src/scene/ModelLoader.hpp ../src/scene/Mesh.hpp
		$(CXX) $(CXXFLAGS) -c ../src/scene/ModelLoader.cpp -o obj/ModelLoader.o


obj/Entities.o: ../src/scene/Entities.cpp ../src/scene/Entities.hpp ../src/scene/Transformation.hpp ../src/scene/vertexObjects.hpp ../src/physics/PhysicsEngine.hpp ../src/scene/VertexBuffer.hpp ../src/scene/IndexBuffer.hpp ../src/scene/VertexArray.hpp
		$(CXX) $(CXXFLAGS) -c ../src/scene/Entities.cpp -o obj/Entities.o

obj/Transformation.o: ../src/math/Transformation.cpp ../src/math/Transformation.hpp ../src/scene/Entities.hpp
		$(CXX) $(CXXFLAGS) -c ../src/math/Transformation.cpp -o obj/Transformation.o


obj/vertexObjects.o: ../src/scene/vertexObjects.cpp ../src/scene/vertexObjects.hpp
		$(CXX) $(CXXFLAGS) -c ../src/scene/vertexObjects.cpp -o obj/vertexObjects.o

obj/Shader.o: ../src/renderer/shader/Shader.cpp	../src/renderer/shader/Shader.hpp ../src/debug/LOG.hpp ../src/renderer/shader/GLSL/vertexShader1.vert ../src/renderer/shader/GLSL/fragmentShader1.frag
		$(CXX) $(CXXFLAGS) -c ../src/renderer/shader/Shader.cpp -o obj/Shader.o

obj/Texture.o: ../src/renderer/Texture.cpp ../src/renderer/Texture.hpp ../vendor/imageLoader/stb_image.h
		$(CXX) $(CXXFLAGS) -c ../src/renderer/Texture.cpp -o obj/Texture.o


obj/Scene.o: ../src/scene/Scene.cpp ../src/scene/Scene.hpp ../src/scene/Entities.hpp ../src/scene/ModelsDataVertex.hpp ../src/scene/ModelsData.hpp ../src/window/Window.hpp ../src/utils/RunParallel.hpp ../src/scene/EntityLoader.hpp
		$(CXX) $(CXXFLAGS) -c ../src/scene/Scene.cpp -o obj/Scene.o

obj/Renderer.o: ../src/renderer/Renderer.cpp ../src/renderer/Renderer.hpp ../src/utils/RunParallel.hpp
		$(CXX) $(CXXFLAGS) -c ../src/renderer/Renderer.cpp -o obj/Renderer.o

obj/Window.o: ../src/window/Window.cpp ../src/window/Window.hpp ../src/debug/LOG.hpp
		$(CXX) $(CXXFLAGS) -c ../src/window/Window.cpp -o obj/Window.o

obj/Audio.o: ../src/audio/Audio.cpp ../src/audio/Audio.hpp
		$(CXX) $(CXXFLAGS) -c ../src/audio/Audio.cpp -o obj/Audio.o

obj/Timer.o: ../src/utils/Timer.cpp ../src/utils/Timer.hpp
		$(CXX) $(CXXFLAGS) -c ../src/utils/Timer.cpp -o obj/Timer.o


obj/Camera.o: ../src/camera/Camera.cpp	../src/camera/Camera.hpp ../src/debug/LOG.hpp ../src/debug/RenderingInfoLog.hpp ../src/physics/PhysicsEngine.hpp ../src/camera/Cursor.hpp
		$(CXX) $(CXXFLAGS) -c ../src/camera/Camera.cpp -o obj/Camera.o

obj/Engine.o: ../src/core/Engine.cpp ../src/core/Engine.hpp ../src/debug/LOG.hpp ../src/scene/Scene.hpp ../src/debug/RenderingInfoLog.hpp ../src/renderer/shader/Shader.hpp ../src/renderer/Renderer.hpp ../src/utils/RunParallel.hpp
		$(CXX) $(CXXFLAGS) -c ../src/core/Engine.cpp -o obj/Engine.o

obj/Application.o: ../src/core/Application.cpp ../src/core/Application.hpp ../src/core/Engine.hpp
		$(CXX) $(CXXFLAGS) -c ../src/core/Application.cpp -o obj/Application.o


#
#obj/core.o: ../src/core/core.cpp ../src/shader/Shader.hpp ../src/window/Window.hpp ../src/camera/Camera.hpp ../src/scene/Entities.hpp ../src/scene/CoordinateTransformation.hpp ../src/core/InitializeEngine.hpp ../src/debug/LOG.hpp
#	    $(CXX) $(CXXFLAGS) -c ../src/core/core.cpp -o obj/core.o

obj/main.o: ../src/core/main.cpp ../src/core/Application.hpp
		$(CXX) $(CXXFLAGS) -c ../src/core/main.cpp -o obj/main.o

exp:	
		export LD_LIBRARY_PATH=../vendor/SFML-2.6.1/lib

clear:
		 rm -f obj/glad.o
		 rm -f obj/stb_image.o
		 rm -f obj/LOG.o
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
		 rm -f obj/Engine.o
		 rm -f obj/Application.o
		 rm -f obj/main.o
run:
		./bin/start_game_engine

run_make_only_if_compiles: bin/start_game_engine
		./bin/start_game_engine
		
c:
		rm -f bin/start_game_engine






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
