main.exe: main.o
	g++ -o main.exe main.o

main.o: main.cpp commandLine.h
	g++ -c main.cpp



clean:
	rm *.o main.exe