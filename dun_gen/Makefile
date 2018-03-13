CXX = g++
CPPFLAGS = -std=c++14 -g -Wall -fstack-protector

%.o : %.cpp
	$(CXX) -c $(CPPFLAGS) $< 

test.exe: room.o dungeon.o test.o
	$(CXX) -o $@ $^


memcheck: test-game.exe
	valgrind --leak-check=yet --track-origins=yes ./test-game.exe

clean:
	$(RM) test-game.exe $(OBJECTS)
