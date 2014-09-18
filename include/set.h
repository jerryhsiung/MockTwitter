#ifndef SET_H
#define SET_H

#include <iostream>
#include <set>

using namespace std;

template <typename T> class Set:public set<T>
{
public:
  Set<T> setIntersection (const Set<T> &other) const;

  Set<T> setUnion (const Set<T> &other) const;

};

template <typename T>
Set<T> Set<T>::setIntersection (const Set<T> &other) const
{
  Set<T> intersection;
  for (typename set<T>::iterator it = this->begin(); it != this->end(); ++it)
  {
    if (other.find(*it) != other.end())
      intersection.insert(*it);
  }
  return intersection;
}

template <typename T> Set<T> Set<T>::setUnion (const Set<T> &other) const
{
  Set<T> uni;

  for (typename set<T>::iterator it = this->begin(); it != this->end(); ++it)
    {
      uni.insert(*it);
    }

  for (typename set<T>::iterator it = other.begin(); it != other.end(); ++it)
    {
      uni.insert(*it);
    }
  return uni;
}

#endif //SET_H