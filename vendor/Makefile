

VENDOR_DIRS = GLFW glad/include glm imageLoader irrKlang LuaScriptingLibs assimp
CXX_EXTERNAL_INCLUDE_FLAGS = $(foreach directory, $(VENDOR_DIRS), -I../vendor/$(directory))


EXTERNAL_LIBRARY_DIRS = GLFW glad imageLoader irrKlang LuaScriptingLibs
EXTERNAL_LIBRARY_LINKS = -lglfw -lGL -lstbimage -lIrrKlang -llua


# Will also automate this
LDFLAGS=-L../vendor/GLFW/lib -lglfw \
		-L../vendor/glad/lib -lGL \
		-L../vendor/imageLoader/lib -lstbimage -Wl, -rpath ../vendor/imageLoader/lib \
		-L../vendor/irrKlang/bin/linux-gcc-64 -lIrrKlang -Wl, -rpath ../vendor/irrKlang/bin/linux-gcc-64 \
		-L../vendor/irrKlang/lib -lIrrKlang \
		-L../vendor/LuaScriptingLibs -llua \
		-L../vendor/assimp -lassimp

