/*
 * This file contains various types and helper functions used 
 * throughout the project
 * */
#ifndef TOOLS_HPP
#define TOOLS_HPP

#include<utility>
#include<queue>

enum Direction {RIGHT, UP, LEFT, DOWN};
typedef std::pair<int, int> Coords;

template<typename T, typename priority_t>
struct PQ
{
  typedef std::pair<priority_t, T> PQElement;
  std::priority_queue <PQElement, std::vector<PQElement>,
        std::greater<PQElement>> elements;

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
    T top = elements.top().second;
    elements.pop();
    return top;
  }
};
#endif
