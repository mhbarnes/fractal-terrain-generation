CC = g++
exe_file = color
$(exe_file): color.o
	$(CC) color.o -o $(exe_file)
main.o: color.cpp
	$(CC) -c color.cpp
clean:
	rm -f *.out *.o $(exe_file)
