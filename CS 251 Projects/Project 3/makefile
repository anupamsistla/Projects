##################
# @file makefile
# @author Adam T Koehler, PhD
# @date October 2, 2023
# @brief Basic makefile to create Google Test or Catch v1.x executables
##################

build:
	g++ -Wall -g -std=c++20 main.cpp canvaslist.cpp shape.cpp -o program.exe

test:
	g++ -std=c++20 tests.cpp canvaslist.cpp shape.cpp -o tests.exe

run:
	./program.exe

runtest:
	./tests.exe

clean:
	rm -f program.exe
	rm -f tests.exe
	rm -f solution.exe

solution:
	g++ -Wall -std=c++20 main.cpp canvaslist_solution.o shape_solution.o -o solution.exe

runsolution:
	./solution.exe

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./program.exe
