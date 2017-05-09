all: delanau

delanau: main.o delanau.o
	g++ main.o -o delanau

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm -rf *.o delanau
