output: main.o
	g++ main.o -o output -std=c++17
	
main.o: main/main.C
	g++ -c main/main.C
	
clean:
	rm *.o output
