CXX = g++
CXXFLAGS = -std=c++14 -g -Wall
OBJECTS = grid.o mob.o player.o test-main.o game.o projectile.o

%.o : %.cpp
	$(CXX) -c $(CXXFLAGS) $< 

test-main: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ -lncurses

clean:
	$(RM) test-game.exe $(OBJECTS)
