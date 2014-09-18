#ifndef HSORT_H
#define HSORT_H

#include <iostream>
#include <vector>
#include <algorithm> 

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
void heapify(std::vector<T>& myArray, int count, Comparator comp)
{
	int start = (count - 2) / 2;
	while (start >= 0)
	{
		trickleDown(myArray, start, count-1, comp);
		start--;
	}
}

template <class T, class Comparator>
void trickleDown(std::vector<T>& myArray, int start, int end, Comparator comp)
{
	int root = start;
	while (root*2+1 <= end)
	{
		int child = root * 2 + 1;
		if (child+1 <= end && comp(myArray[child], myArray[child+1]))
		{
			child++;
		}
		if (comp(myArray[root], myArray[child]))
		{
			std::swap(myArray[root], myArray[child]);
			root = child;
		}
		else
			return;
	}
}

template <class T, class Comparator>
void heapSort (std::vector<T>& myArray, Comparator comp)
{
	int count = myArray.size();
	heapify(myArray, count, comp);
	int end = count-1;
	while (end > 0)
	{
		std::swap(myArray[end], myArray[0]);
		end--;
		trickleDown(myArray, 0, end, comp);
	}
}

#endif