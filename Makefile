### Input and Output Files ###
OBJS = src/*/*.c src/test.c glad/src/glad.c
OBJ = bin/game

### Project Settings ###
CurrentVersion = 0.0
CommitID := $(shell git log --format="%H" -n 1)

### Compiler Configuration ###
GLADInc = -Iglad/include
Defines = -DLOGGING_COLOR -DWINDOW_WIDTH=800 -DWINDOW_HEIGHT=600

CFlags = -Wall -lm -lGL -lSDL3 $(GLADInc) -Isrc $(Defines)
RelFlags = -O3
ASANFlags = -fsanitize-recover=address,undefined
DbgFlags = -O0 -ggdb -DDEBUG
Compiler = gcc

RBuildCommand = $(Compiler) $(OBJS) $(RelFlags) $(CFlags) -o $(OBJ)
DBuildCommand = $(Compiler) $(OBJS) $(DbgFlags) $(CFlags) -o $(OBJ)
BuildCommand  = $(Compiler) $(OBJS) $(CFlags) -o $(OBJ)

all : $(OBJS)
	 - make clean
	make build && make run

clean :
	@echo -e "\n\001\033[48;5;008m\002 Cleaning up.. \001\033[0m\002"
	rm -r bin package *.tar.gz

build : $(OBJS)
	@echo -e "\n\001\033[48;5;008m\002 Build Command \001\033[0m\002"
	@if [ ! -d "bin" ]; then\
		mkdir bin;\
	fi

	@echo -e "\n\001\033[48;5;008m\002 Build Command \001\033[0m\002"
	@echo $(BuildCommand)
	@echo -e "\n\001\033[48;5;008m\002 Build Output \001\033[0m\002"
	@$(BuildCommand)

run :
	@echo -e "\n\001\033[48;5;008m\002 Binary Output \001\033[0m\002"
	@$(OBJ)

release : $(OBJS)
	@echo -e "\n\001\033[48;5;008m\002 Build Command \001\033[0m\002"
	@if [ ! -d "bin" ]; then\
		mkdir bin;\
	fi
	@echo -e "\n\001\033[48;5;008m\002 Build Command \001\033[0m\002"
	@echo $(RBuildCommand) 
	@echo -e "\n\001\033[48;5;008m\002 Build Output \001\033[0m\002"
	@$(RBuildCommand)

debug : $(OBJS)
	@echo -e "\n\001\033[48;5;008m\002 Build Command \001\033[0m\002"
	@if [ ! -d "bin" ]; then\
		mkdir bin;\
	fi
	@echo -e "\n\001\033[48;5;008m\002 Build Command \001\033[0m\002"
	@echo $(DBuildCommand)
	@echo -e "\n\001\033[48;5;008m\002 Build Output \001\033[0m\002"
	@$(DBuildCommand)

package : $(OBJS)
	 - make clean

	@if [ ! -d "package" ]; then\
		mkdir package;\
	fi

	@echo -e "\n\001\033[48;5;124m\002 Building.. \001\033[0m\002"

	make release

	@echo -e "\n\001\033[48;5;124m\002 Copying files.. \001\033[0m\002"
	cp -r bin/* assets package

	@echo -e "\n\001\033[48;5;124m\002 Packing everything.. \001\033[0m\002"
	tar -zcvf "package/putik_v$(CurrentVersion).tar.gz" package/

package-nightly : $(OBJS)
	 - make clean

	@if [ ! -d "package" ]; then\
		mkdir package;\
	fi

	@echo -e "\n\001\033[48;5;124m\002 Building.. \001\033[0m\002"

	make release

	@echo -e "\n\001\033[48;5;124m\002 Copying files.. \001\033[0m\002"
	@cp -r bin/* package
	@cp -r assets package

	@echo -e "\n\001\033[48;5;124m\002 Packing everything.. \001\033[0m\002"
	tar -zcvf "package/putik_v$(CurrentVersion)_$(CommitID).tar.gz" package/
