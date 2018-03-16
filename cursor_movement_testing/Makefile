CXX = g++
CPPFLAGS = -std=c++14 -g -Wall

%.o : %.cpp
	$(CXX) -c $(CPPFLAGS) $<

main.exe: main.o screens.o
	$(CXX) -o $@ $^ -lncurses


memcheck: main.exe
	valgrind --leak-check=yet --track-origins=yes ./main.exe

clean:
	$(RM) curse-test.exe $(OBJECTS)
