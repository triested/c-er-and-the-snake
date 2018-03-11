CXX = g++
CPPFLAGS = -std=c++14 -g -Wall

%.o : %.cpp
	$(CXX) -c $(CPPFLAGS) $< 

test-room.exe: room.o test.o
	$(CXX) -o $@ $^


memcheck: test-game.exe
	valgrind --leak-check=yet --track-origins=yes ./test-game.exe

clean:
	$(RM) test-game.exe $(OBJECTS)
