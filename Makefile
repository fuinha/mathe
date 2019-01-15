all:
	g++ -c src/mathe.cpp -o build/mathe.o
	g++ src/main.cpp -o build/main build/mathe.o 