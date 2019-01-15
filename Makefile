all:
	@test -d build | mkdir -p build
	g++ -c src/mathe.cpp -o build/mathe.o
	g++ -c src/bank.cpp -o build/bank.o
	g++ src/main.cpp -o build/main build/mathe.o build/bank.o

clean:
	@rm -rf build/*
