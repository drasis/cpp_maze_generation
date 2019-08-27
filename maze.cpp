#include "randomHelpers.h"
#include "cell.h"
#include "grid.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
using namespace std;

void printDig(short digit) {
	cout << "0123456789abcdef"[digit]; 
}

void printGrid(Grid g, int i = 0) {
	for (int i = 0; i < g.rows(); ++i) {
		for (int j = 0; j < g.columns(); ++j) {
			printDig(g.connections(i, j));
		}
		cout << endl;
	}
}

void randomBinaryWalk(Grid& g) {
	for (int i = 0; i < g.rows(); ++i) {
		for (int j = 0; j < g.columns(); ++j) {
			int ind = randInt(0, 1);
			cell* cells[2] = {g.at(i + 1, j), g.at(i, j + 1)};
			if (cells[ind] == nullptr) {
				ind = (ind + 1) % 2;
			}
			if (!(cells[0] == nullptr && cells[1] == nullptr)) {
				g.at(i, j)->link(*cells[ind]);
			}
		}
	}
}

void sidesinderWalk(Grid& g) {
	vector<cell*> run;
	for (int i = 0; i < g.rows(); ++i) {
		for (int j = 0; j < g.columns(); ++j) {
			cell* cp = g.at(i, j);
			run.push_back(cp);
			bool atEast = cp->geteast() == nullptr;
			bool atSouth = cp->getsouth() == nullptr;
			bool shouldClose = atEast || (!atSouth && (randInt(0, 3) == 0));
			if (shouldClose) {
				cell* member = run[randInt(0, run.size() - 1)];
				if (member->getsouth() != nullptr) {
					member->link(*member->getsouth());
				}
				run.clear();
			} else if (cp->geteast() != nullptr) {
				cp->link(*cp->geteast());
			}
		}
		run.clear();
	}
}

void aldousBroder(Grid& g) {
	cell* cp = g.randomCell();
	int unvisited = g.size() - 1;
	while (unvisited > 0) {
		cell* neighbor = cp->randomNeighbor();
		if (neighbor->hasNoLinks()) {
			cp->link(*neighbor);
			unvisited -= 1;
		}
		cp = neighbor;
	}
}

void wilson(Grid& g) {

}

int main(int argc, char *argv[]) {
	srand(time(nullptr));
	int r, c;

	if (argc == 3) {
		r = stoi(argv[1]);
		c = stoi(argv[2]);
	} else if (argc == 1) {
		r = 10;
		c = 15;
	} else {
		exit(1);
	}
	Grid g(r, c);
	// randomBinaryWalk(g);
	sidesinderWalk(g);
	// aldousBroder(g);
	printGrid(g);
}

