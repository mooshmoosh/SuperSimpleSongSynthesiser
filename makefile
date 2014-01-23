bin/song.o: src/song.cpp 
	g++ -c src/song.cpp -o bin/song.o

bin/test.o: src/test.cpp 
	g++ -c src/test.cpp -o bin/test.o

logicalc: bin/song.o 
	g++ bin/song.o -o bin/logicalc

check: bin/song.o bin/test.o 
	g++ bin/song.o bin/test.o -o bin/test
	bin/test

check_memory:  src/song.cpp  src/test.cpp 
	g++  src/song.cpp  src/test.cpp -g -o bin/test_VAL
	valgrind --leak-check=yes --tool=memcheck --track-origins=yes ./bin/test_VAL

