.PHONY: clean run copylibs

INCLUDE=src/lib/raylib-4.0.0_linux_amd64/include src/client/camera
LIB_PATHS=src/lib/raylib-4.0.0_linux_amd64/lib
LIBS=raylib

all: bin/client/Game

bin/client/Game: build/client/Game.o build/client/camera/TopCamera.o $(LIB_PATHS) | bin copyclientlibs
	@echo "-- Building the game binary... --"
	g++ -o bin/client/Game build/client/Game.o build/client/camera/TopCamera.o -L src/lib/raylib-4.0.0_linux_amd64/lib -lraylib -L. -Wl,-rpath,"\$$ORIGIN/lib"
	@echo ""

bin:
	mkdir bin
	mkdir bin/client
	mkdir bin/client/lib
	mkdir bin/client/camera

copyclientlibs:
	cp src/lib/raylib-4.0.0_linux_amd64/lib/libraylib.so.4.0.0 bin/client/lib/libraylib.so.400

copyserverlibs:
	.


build/client/Game.o: src/client/Game.cpp src/client/Game.h | build
	@echo "-- Building the client objects... --"
	g++ $(INCLUDE:%=-I %) -c -o build/client/Game.o src/client/Game.cpp

build/client/camera/TopCamera.o: src/client/camera/TopCamera.cpp src/client/camera/TopCamera.h | build
	@echo "-- Building the camera files... --"
	g++ $(INCLUDE:%=-I %) -c -o build/client/camera/TopCamera.o src/client/camera/TopCamera.cpp

build:
	mkdir build
	mkdir build/client
	mkdir build/client/camera
	mkdir build/server

clean:
	rm -rf build
	rm -rf bin

run: bin/client/Game
	./bin/client/Game