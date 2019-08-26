#include "cell.h"
#include "grid.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
using namespace std;

void printDig(short digit) {
	// short digit = a << 3 | b << 2 | c << 1 | d;
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
		}
		cout << endl;
	}
}

void randomBinaryWalk(Grid& g) {
	for (int i = 0; i < g.rows(); ++i) {
		for (int j = 0; j < g.columns(); ++j) {
			int ind = rand() % 2;
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
			bool shouldClose = atEast || (!atSouth && (rand() % 4 == 0));
			if (shouldClose) {
				cell* member = run[rand() % run.size()];
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

int main(int argc, char *argv[]) {
	srand(time(nullptr));
	int r, c;
	// cout<<"random max: " << RAND_MAX;
	// cout << argc << endl;
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
	printGrid(g);
}

