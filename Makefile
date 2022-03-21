.PHONY: clean run copylibs

INCLUDE=src/lib/raylib-4.0.0_linux_amd64/include
LIB_PATHS=src/lib/raylib-4.0.0_linux_amd64/lib
LIBS=raylib

all: bin/client/game

bin/client/game: build/client/game.o $(LIB_PATHS) | bin copyclientlibs
	@echo "-- Building the game binary... --"
	g++ -o bin/client/game build/client/game.o -L src/lib/raylib-4.0.0_linux_amd64/lib -lraylib -L. -Wl,-rpath,"\$$ORIGIN/lib"
	@echo ""

bin:
	mkdir bin
	mkdir bin/client
	mkdir bin/client/lib

copyclientlibs:
	cp src/lib/raylib-4.0.0_linux_amd64/lib/libraylib.so.4.0.0 bin/client/lib/libraylib.so.400

copyserverlibs:
	.


build/client/game.o: src/client/game.cpp $(INCLUDE) | build
	@echo "-- Building the client objects... --"
	g++ $(INCLUDE:%=-I %) -c -o build/client/game.o src/client/game.cpp

build:
	mkdir build
	mkdir build/client
	mkdir build/server

clean:
	rm -rf build
	rm -rf bin

run: bin/client/game
	./bin/client/game