#ifndef RANDOMHELPERS_H
#define RANDOMHELPERS_H
#include <unordered_set>
#include <iostream>

int randInt(int inclusiveLowerBound, int inclusiveUpperBound);

template <class T>
bool contains(std::unordered_set<T>& myset, T i) {
	return myset.find(i) != myset.end();
}

template <class T>
T randomElement(std::unordered_set<T>& myset) {
	int nthElement = randInt(0, myset.size() - 1);
	typename std::unordered_set<T>::iterator c;
	c = myset.begin();
	for (int i = 0; i < nthElement; ++i) {
		c++;
	}
	return *c;
}

template <class T>
int findIndex(std::vector<T>& v, T obj) {
	for (int i = 0; i < v.size(); ++i) {
		std::cout<<"checking index: " << i << std::endl;
		if (v[i] == obj) {
			return i;
		}
	}
	return -1;
}

bool coinFlip();

#endif