CXX = g++
CPPFLAGS = -std=c++14 -Wall -fstack-protector -O2

%.o : %.cpp
	$(CXX) -c $(CPPFLAGS) $< 

test.exe: room.o dungeon.o test.o
	$(CXX) -o $@ $^

memcheck: test.exe
	valgrind --leak-check=yes --track-origins=yes ./test.exe

clean:
	$(RM) test-game.exe $(OBJECTS)
