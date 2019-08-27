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

void checkLink(cell& c1, cell& c2) {
	if (c1.linked(c2) && c2.linked(c1)) {
		cout << "linked\n";
	} else {
		cout << "not linked\n";
	}
}

void printGrid(Grid g, int i = 0) {
	for (int i = 0; i < g.rows(); ++i) {
		for (int j = 0; j < g.columns(); ++j) {
			printDig(g.connections(i, j));
			// g.at(i,j)->displayNeighbors();
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
			bool atEast = g.at(i, j + 1) == nullptr;
			bool atSouth = g.at(i + 1, j) == nullptr;
			bool shouldClose = atEast || (!atSouth && (randInt(0, 3) == 0));
			if (shouldClose) {
				cell* member = run[randInt(0, run.size() - 1)];
				if (g.at(member->row() + 1, member->column()) != nullptr) {
					member->link(*g.at(member->row() + 1, member->column()));
				}
				run.clear();
			} else if (g.at(cp->row(), cp->column() + 1) != nullptr) {
				cp->link(*g.at(cp->row(), cp->column() + 1));
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
	// sidesinderWalk(g);
	aldousBroder(g);
	printGrid(g);
}

