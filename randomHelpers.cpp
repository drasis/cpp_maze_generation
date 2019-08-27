#include "randomHelpers.h"
#include <unordered_set>
#include <random>

int randInt(int inclusiveLowerBound, int inclusiveUpperBound) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(inclusiveLowerBound, inclusiveUpperBound);
	return dis(rd);
}

bool coinFlip() {
	return randInt(0, 1);
}