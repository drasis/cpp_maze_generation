#ifndef RANDOMHELPERS_H
#define RANDOMHELPERS_H
#include <unordered_set>

int randInt(int inclusiveLowerBound, int inclusiveUpperBound);

template <class T>
bool contains(std::unordered_set<T> myset, T i) {
	return myset.find(i) != myset.end();
}

template <class D>
D randomElement(std::unordered_set<D> myset) {
	int nthElement = randInt(0, myset.size() - 1);
	typename std::unordered_set<D>::iterator c;
	c = myset.begin();
	for (int i = 0; i < nthElement; ++i) {
		c++;
	}
	return *c;
}

bool coinFlip();

#endif