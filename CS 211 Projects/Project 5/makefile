buildmain:
	rm -f hi.exe
	gcc main.c -o hi.exe

run:
	./hi.exe

valgrind:
	valgrind -s --tool=memcheck --leak-check=yes --track-origins=yes ./hi.exe

built_test:
	rm -f test.exe
	gcc test.c -o test.exe

runtest:
	./test.exe


