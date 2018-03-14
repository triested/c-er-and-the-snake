/*
 * This class outlines the games mobs: may serve as base class for others
 * later
 * */

#include <utility>
#include <functional>
#include <queue>
#include "grid.hpp"

using namespace std;

template<typename T, typename priority_t>
struct PQ
{
  typedef pair<priority_t, T> PQElement;
  priority_queue <PQElement, vector<PQElement>,
        greater<PQElement>> elements;

  inline bool empty() const
  {
     return elements.empty();
  }

  inline void push(T el, priority_t priority)
  {
    elements.emplace(priority, el);
  }

  T pop()
  {
    T best = elements.top().second;
    elements.pop();
    return best;
  }
};

class Mob
{
    // Constructor
    Mob(int x_coord, int y_coord, char repr);
    // Destructor
    ~Mob();

    private:
        int     x;
        int     y;
        char    display;
        Grid    *grid;
    public:
        void move();
};
