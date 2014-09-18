#ifndef MSORT_H
#define MSORT_H

#include <iostream>
#include <vector>
#include <cmath>

struct SizeVecComp 
{
  template <class T>
  bool operator()(const std::vector<T>& lhs, const std::vector<T>& rhs)
  {
    return lhs.size() < rhs.size();
  }
};

struct ValVecComp
{
  template <class T>
  bool operator()(const T& lhs, const T& rhs)
  {
    return lhs < rhs;
  }
};

template <class T, class Comparator>
void DoCompare(const std::vector<T>& s1, const std::vector<T>& s2, Comparator comp)
{
  std::cout << comp(s1, s2) << std::endl;
}

template <class T, class Comparator>
void mergeSort (std::vector<T>& mylist, Comparator comp)
{
  mergeSort_helper(mylist, 0, mylist.size() - 1, comp);
}

template <class T, class Comparator>
void mergeSort_helper(std::vector<T>& mylist, int start, int end, Comparator comp)
{
  if (start >= end) return;
  int mid = (start+end)/2;
  mergeSort_helper(mylist, start, mid, comp);
  mergeSort_helper(mylist, mid + 1, end, comp);
  merge (mylist, start, end, mid, comp);
}

template <class T, class Comparator>
void merge(std::vector<T>& list, int start, int end, int m, Comparator comp)
{
  std::vector <T> temp;
  int mid = floor((start + end) / 2);
  int s = start;
  int e = end;
  int x = m + 1;

  while (s <= mid && x <= end)
  {
    //merge in sorted form the 2 std::vectors
    if (comp(list[s], list[x]))
    {
      temp.push_back(list[s]);
      s++;
    }
    else {
      temp.push_back(list[x]);
      x++;
    }
  }
  //merge remaining elements in right std::vector
  while (x <= e){
    temp.push_back(list[x]);
    x++;
  }
  // merge remaining elements in left std::vector
  while (s <= mid) {
    temp.push_back(list[s]);
    s++;
  }

  for (int i = start; i <= end; i++)
  {
    list[i] = temp[i-start];
  }
}

#endif