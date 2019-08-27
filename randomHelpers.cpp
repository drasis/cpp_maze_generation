#include "randomHelpers.h"
#include <random>

int randInt(int inclusiveLowerBound, int inclusiveUpperBound) {
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dis(inclusiveLowerBound, inclusiveUpperBound);
	// std::default_random_engine generator;
	// std::uniform_int_distribution<> dis(inclusiveLowerBound, inclusiveUpperBound);
	// std::mt19937 rng(std::random_device{}());
	return dis(rd);
}
