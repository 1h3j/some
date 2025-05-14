OBJS = src/util/logging.c src/math/camera.c src/math/matrix.c src/math/angles.c src/math/transform.c src/math/projection.c src/render/renderer.c src/render/shader.c src/app/resources.c src/event/callback.c src/event/events.c src/test.c glad/src/glad.c
OUT = bin/game

build-and-run: $(OBJS)
	@make build
	@make run

build: $(OBJS)
	gcc $(OBJS) -ggdb -Isrc -Iglad/include -o $(OUT) -lm -lSDL3 -lGL -DLOGGING_COLOR -DWINDOW_WIDTH=800 -DWINDOW_HEIGHT=600

run: $(OUT)
	$(OUT)
