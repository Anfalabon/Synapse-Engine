# '$<' means the first dependency of current target
# '$@' means the target or targets



obj/glad.o: ../vendor/glad/src/glad.cpp ../vendor/glad/include/glad/glad.hpp
		$(CXX) $(CXXFLAGS) -c $< -o $@


#created a shadred library for this because of it's slow compilation
#obj/stb_image.o: ../vendor/imageLoader/stb_image.cpp ../vendor/imageLoader/stb_image.h
#		$(CXX) $(CXXFLAGS) -c $< -o $@



obj/LOG.o: ../src/debug/LOG.cpp ../src/debug/LOG.hpp
		$(CXX) $(CXXFLAGS) -D __DEBUG__ -c $< -o $@


obj/FrameBuffer.o: ../src/renderer/FrameBuffer.cpp ../src/renderer/FrameBuffer.hpp
		$(CXX) $(CXXFLAGS) -c $< -o $@


obj/PhysicsEngine.o: ../src/physics/PhysicsEngine.cpp ../src/physics/PhysicsEngine.hpp
		$(CXX) $(CXXFLAGS) -c $< -o $@


obj/Buffer.o: ../src/scene/Buffer.cpp ../src/scene/Buffer.hpp
		$(CXX) $(CXXFLAGS) -c $< -o $@


obj/Filesystem.o: ../src/core/Filesystem.cpp ../src/core/Filesystem.hpp
		$(CXX) $(CXXFLAGS) -c $< -o $@


obj/VertexArray.o: ../src/renderer/VertexArray.cpp ../src/renderer/VertexArray.hpp ../src/scene/VertexBuffer.hpp ../src/scene/IndexBuffer.hpp
		$(CXX) $(CXXFLAGS) -c $< -o $@


obj/VertexBuffer.o: ../src/scene/VertexBuffer.cpp ../src/scene/VertexBuffer.hpp
		$(CXX) $(CXXFLAGS) -c $< -o $@


obj/IndexBuffer.o: ../src/scene/IndexBuffer.cpp ../src/scene/IndexBuffer.hpp
		$(CXX) $(CXXFLAGS) -c $< -o $@


obj/Mesh.o: ../src/scene/Mesh.cpp ../src/scene/Mesh.hpp
		$(CXX) $(CXXFLAGS) -c $< -o $@


obj/ModelLoader.o: ../src/scene/ModelLoader.cpp ../src/scene/ModelLoader.hpp ../src/scene/Mesh.hpp
		$(CXX) $(CXXFLAGS) -c $< -o $@


obj/Entities.o: ../src/scene/Entities.cpp ../src/scene/Entities.hpp ../src/scene/Transformation.hpp ../src/scene/vertexObjects.hpp ../src/physics/PhysicsEngine.hpp ../src/scene/VertexBuffer.hpp ../src/scene/IndexBuffer.hpp ../src/renderer/VertexArray.hpp
		$(CXX) $(CXXFLAGS) -c $< -o $@


obj/Transformation.o: ../src/math/Transformation.cpp ../src/math/Transformation.hpp ../src/scene/Entities.hpp
		$(CXX) $(CXXFLAGS) -c $< -o $@


obj/vertexObjects.o: ../src/scene/vertexObjects.cpp ../src/scene/vertexObjects.hpp
		$(CXX) $(CXXFLAGS) -c $< -o $@


obj/Shader.o: ../src/renderer/shader/Shader.cpp	../src/renderer/shader/Shader.hpp ../src/debug/LOG.hpp ../src/renderer/shader/GLSL/vertexShader1.vert ../src/renderer/shader/GLSL/fragmentShader1.frag
		$(CXX) $(CXXFLAGS) -c $< -o $@


obj/Texture.o: ../src/renderer/Texture.cpp ../src/renderer/Texture.hpp ../vendor/imageLoader/stb_image.h
		$(CXX) $(CXXFLAGS) -c $< -o $@


obj/Scene.o: ../src/scene/Scene.cpp ../src/scene/Scene.hpp ../src/scene/Entities.hpp ../src/scene/ModelsDataVertex.hpp ../src/scene/ModelsData.hpp ../src/scene/ModelsDataVector.hpp ../src/window/Window.hpp ../src/core/RunParallel.hpp
		$(CXX) $(CXXFLAGS) -c $< -o $@


obj/Renderer.o: ../src/renderer/Renderer.cpp ../src/renderer/Renderer.hpp ../src/core/RunParallel.hpp
		$(CXX) $(CXXFLAGS) -c $< -o $@


obj/Window.o: ../src/window/Window.cpp ../src/window/Window.hpp ../src/debug/LOG.hpp
		$(CXX) $(CXXFLAGS) -c $< -o $@


obj/Audio.o: ../src/audio/Audio.cpp ../src/audio/Audio.hpp
		$(CXX) $(CXXFLAGS) -c $< -o $@


obj/Timer.o: ../src/core/Timer.cpp ../src/core/Timer.hpp
		$(CXX) $(CXXFLAGS) -c $< -o $@


obj/Camera.o: ../src/camera/Camera.cpp	../src/camera/Camera.hpp ../src/debug/LOG.hpp ../src/debug/RenderingInfoLog.hpp ../src/physics/PhysicsEngine.hpp ../src/camera/Cursor.hpp
		$(CXX) $(CXXFLAGS) -c $< -o $@


obj/ScriptingEngine.o: ../src/scripting/ScriptingEngine.cpp ../src/scripting/ScriptingEngine.hpp
		$(CXX) $(CXXFLAGS) -c $< -o $@


obj/Engine.o: ../src/core/Engine.cpp ../src/core/Engine.hpp ../src/debug/LOG.hpp ../src/scene/Scene.hpp ../src/debug/RenderingInfoLog.hpp ../src/renderer/shader/Shader.hpp ../src/renderer/Renderer.hpp ../src/core/RunParallel.hpp ../src/audio/Audio.hpp ../src/scripting/ScriptingEngine.hpp
		$(CXX) $(CXXFLAGS) -c $< -o $@


obj/Application.o: ../src/core/Application.cpp ../src/core/Application.hpp ../src/core/Engine.hpp
		$(CXX) $(CXXFLAGS) -c $< -o $@


obj/main.o: ../src/core/main.cpp ../src/core/Application.hpp
		$(CXX) $(CXXFLAGS) -c $< -o $@
