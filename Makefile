all: compile link run

compile:
	g++ -I src/include -c main.cpp Collider.cpp
link:
	g++ collider.o main.o -o main -L src/lib -l sfml-graphics -l sfml-window -l sfml-system -l sfml-audio
run:
	./main.exe