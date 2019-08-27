#ifndef RANDOMHELPERS_H
#define RANDOMHELPERS_H
#include <unordered_set>

int randInt(int inclusiveLowerBound, int inclusiveUpperBound);

template <class T>
bool contains(std::unordered_set<T> myset, T i) {
	return myset.find(i) == myset.end();
}
bool coinFlip();

#endif