#include "randomHelpers.h"
#include <fstream>
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

int rowsOfText(std::string path) {
	int ret = 0;
	std::string line;
	std::ifstream myfile(path);
	while (std::getline(myfile, line)) {
		ret++;
	}
	myfile.close();
	return ret;
}

int columnsOfText(std::string path) {
	std::string line;
	std::ifstream myfile(path);
	std::getline(myfile, line);
	myfile.close();
	return line.length();
}