main.exe: main.o
	g++ -std=c++11 -o main.exe main.o -g

main.o: main.cpp commandLine.h
	g++ -std=c++11 -c main.cpp -g

clean:
	rm *.o main.exe