all:
	@test -d build | mkdir -p build
	g++ -c src/mathe.cpp -o build/mathe.o
	g++ src/main.cpp -o build/main build/mathe.o

clean:
	@rm -rf build/*
