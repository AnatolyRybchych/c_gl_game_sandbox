objects 				= main.o glad.o shader_program.o shaders.o texture2d.o gl_camera.o vec_types.o window.o scenes.o game_scene.o game_textures.o tile.o tiles.o slime.o handle_queue.o


CC 						= gcc
out 					= ./build/out/run.exe
linkArgs 				= -ggdb -Wall -Wpedantic -mconsole
compileArgs 			= -c -ggdb $(aditional_include) -D _DEBUG
OBJ_DIR 				= ./build/objects/

#additional include dirs
externInclude 			= extern/GLFW/include/ extern/glad/include/

externLibs 				= $(GLFW_LIB) -lgdi32 -lopengl32

#extern objects
GLFW_LIB				= extern/GLFW/lib-mingw-w64/libglfw3.a
GLAD_SRC				= extern/glad/src/glad.c


EXTERN_INCLUDE := $(patsubst %,-I%,$(externInclude))
OBJ_FILES := $(patsubst %,$(OBJ_DIR)%,$(objects))


#link all objects together
build: $(OBJ_FILES)
	@mkdir -p $(dir $(out))
	@$(CC) $(linkArgs) -o $(out) $+ $(externLibs)
	@echo $@ : $+


#compile all objects

$(OBJ_DIR)main.o:./src/main.c
	@echo $@ : $+
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(EXTERN_INCLUDE)  $(compileArgs) -o $@ $+

$(OBJ_DIR)glad.o: $(GLAD_SRC)
	@echo $@ : $+
	@$(CC) -c $(EXTERN_INCLUDE)  -o $@ $+

$(OBJ_DIR)%.o:./src/%.c
	@echo $@ : $+
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(EXTERN_INCLUDE) $(compileArgs) -o $@ $+

$(OBJ_DIR)%.o:./src/scenes/game_scene/%.c
	@echo $@ : $+
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(EXTERN_INCLUDE) $(compileArgs) -o $@ $+


#make args
gdb: build
	@echo gdb
	gdb $(out)

run: build
	@echo run
	$(out)
