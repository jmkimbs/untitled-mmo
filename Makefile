.PHONY: clean run copylibs

INCLUDE=src/lib/raylib-4.0.0_linux_amd64/include .
LIB_PATHS=src/lib/raylib-4.0.0_linux_amd64/lib
LIBS=raylib

all: bin/client/Game

bin/client/Game: build/client/Game.o build/client/ui/camera/TopCamera.o build/client/inputhandler/InputHandler.o build/common/characters/Character.o build/common/characters/player/Player.o $(LIB_PATHS) | bin copyclientlibs
	@echo "-- Building the game binary... --"
	g++ -std=c++2a -o bin/client/Game build/client/Game.o build/client/ui/camera/TopCamera.o build/client/inputhandler/InputHandler.o build/common/characters/Character.o build/common/characters/player/Player.o -L src/lib/raylib-4.0.0_linux_amd64/lib -lraylib -L. -Wl,-rpath,"\$$ORIGIN/lib"
	@echo ""

bin:
	mkdir bin
	mkdir bin/client
	mkdir bin/client/lib
	mkdir bin/client/inputhandler
	mkdir bin/client/ui
	mkdir bin/client/ui/camera
	mkdir bin/common
	mkdir bin/common/characters
	mkdir bin/common/characters/player

copyclientlibs:
	cp src/lib/raylib-4.0.0_linux_amd64/lib/libraylib.so.4.0.0 bin/client/lib/libraylib.so.400

copyserverlibs:
	.


build/client/Game.o: src/client/Game.cpp src/client/Game.h | build
	@echo "-- Building the client objects... --"
	g++ -std=c++2a $(INCLUDE:%=-I %) -c -o build/client/Game.o src/client/Game.cpp

build/client/ui/camera/TopCamera.o: src/client/ui/camera/TopCamera.cpp src/client/ui/camera/TopCamera.h | build
	@echo "-- Building the camera files... --"
	g++ -std=c++2a $(INCLUDE:%=-I %) -c -o build/client/ui/camera/TopCamera.o src/client/ui/camera/TopCamera.cpp

build/client/inputhandler/InputHandler.o: src/client/inputhandler/InputHandler.cpp src/client/inputhandler/InputHandler.h | build
	@echo "-- Building the input handler files... --"
	g++ -std=c++2a $(INCLUDE:%=-I %) -c -o build/client/inputhandler/InputHandler.o src/client/inputhandler/InputHandler.cpp

build/common/characters/Character.o: src/common/characters/Character.cpp src/common/characters/Character.h | build
	@echo "-- Building the character files... --"
	g++ -std=c++2a $(INCLUDE:%=-I %) -c -o build/common/characters/Character.o src/common/characters/Character.cpp

build/common/characters/player/Player.o: src/common/characters/player/Player.cpp src/common/characters/player/Player.h | build
	@echo "-- Building the player files... --"
	g++ -std=c++2a $(INCLUDE:%=-I %) -c -o build/common/characters/player/Player.o src/common/characters/player/Player.cpp

build:
	mkdir build
	mkdir build/copyclientlibs
	mkdir build/client
	mkdir build/client/inputhandler
	mkdir build/client/ui
	mkdir build/client/ui/camera
	mkdir build/common
	mkdir build/common/characters
	mkdir build/common/characters/player
	mkdir build/server

clean:
	rm -rf build
	rm -rf bin

run: bin/client/Game
	./bin/client/Game