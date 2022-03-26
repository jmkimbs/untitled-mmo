.PHONY: clean run copylibs

INCLUDE=src/lib/raylib-4.0.0_linux_amd64/include .
LIB_PATHS=src/lib/raylib-4.0.0_linux_amd64/lib
LIBS=raylib

all: bin/client/Game

bin/client/Game: build/client/Game.o build/client/ui/camera/TopCamera.o build/client/ui/controls/Controls.o build/client/inputhandler/InputHandler.o $(LIB_PATHS) | bin copyclientlibs
	@echo "-- Building the game binary... --"
	g++ -o bin/client/Game build/client/Game.o build/client/ui/camera/TopCamera.o build/client/ui/controls/Controls.o build/client/inputhandler/InputHandler.o -L src/lib/raylib-4.0.0_linux_amd64/lib -lraylib -L. -Wl,-rpath,"\$$ORIGIN/lib"
	@echo ""

bin:
	mkdir bin
	mkdir bin/client
	mkdir bin/client/lib
	mkdir bin/client/inputhandler
	mkdir bin/client/ui
	mkdir bin/client/ui/camera
	mkdir bin/client/ui/controls

copyclientlibs:
	cp src/lib/raylib-4.0.0_linux_amd64/lib/libraylib.so.4.0.0 bin/client/lib/libraylib.so.400

copyserverlibs:
	.


build/client/Game.o: src/client/Game.cpp src/client/Game.h | build
	@echo "-- Building the client objects... --"
	g++ $(INCLUDE:%=-I %) -c -o build/client/Game.o src/client/Game.cpp

build/client/ui/camera/TopCamera.o: src/client/ui/camera/TopCamera.cpp src/client/ui/camera/TopCamera.h | build
	@echo "-- Building the camera files... --"
	g++ $(INCLUDE:%=-I %) -c -o build/client/ui/camera/TopCamera.o src/client/ui/camera/TopCamera.cpp

build/client/ui/controls/Controls.o: src/client/ui/controls/Controls.cpp src/client/ui/controls/Controls.h | build
	@echo "-- Building the control files... --"
	g++ $(INCLUDE:%=-I %) -c -o build/client/ui/controls/Controls.o src/client/ui/controls/Controls.cpp

build/client/inputhandler/InputHandler.o: src/client/inputhandler/InputHandler.cpp src/client/inputhandler/InputHandler.h | build
	@echo "-- Building the input handler files... --"
	g++ $(INCLUDE:%=-I %) -c -o build/client/inputhandler/InputHandler.o src/client/inputhandler/InputHandler.cpp

build:
	mkdir build
	mkdir build/copyclientlibs
	mkdir build/client
	mkdir build/client/inputhandler
	mkdir build/client/ui
	mkdir build/client/ui/camera
	mkdir build/client/ui/controls
	mkdir build/server

clean:
	rm -rf build
	rm -rf bin

run: bin/client/Game
	./bin/client/Game