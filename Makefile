OBJS = src/util/logging.c src/math/camera.c src/math/matrix.c src/math/vectors.c src/math/angles.c src/math/transform.c src/render/renderer.c src/render/shader.c src/game.c glad/src/glad.c
OUT = bin/game

all: $(OBJS)
	gcc $(OBJS) -ggdb -Isrc -Iglad/include -o $(OUT) -lm -lSDL3 -lGL -DLOGGING_COLOR
