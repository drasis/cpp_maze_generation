#include "cell.h"
#include "grid.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
using namespace std;

void printBin(bool a, bool b, bool c, bool d) {
	short digit = a<<3 | b<<2 | c<< 1 | d;
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
			cell cp = *g.at(i, j);
			int v[4];
			v[0] = g.at(i - 1, j) == nullptr;
			v[1] = g.at(i, j + 1) == nullptr;
			v[2] = g.at(i + 1, j) == nullptr;
			v[3] = g.at(i, j - 1) == nullptr;
			if (!v[0]) {
				v[0] = cp.linked(*g.at(i - 1, j));
			}
			if (!v[1]) {
				v[1] = cp.linked(*g.at(i, j + 1));
			}
			if (!v[2]) {
				v[2] = cp.linked(*g.at(i + 1, j));
			}
			if (!v[3]) {
				v[3] = cp.linked(*g.at(i, j - 1));
			}
			// printBin(v[(0 + i) % 4], v[(1 + i) % 4], v[(2 + i) % 4], v[(3 + i) % 4]);
			// printBin(v[3], v[0], v[1], v[2]);
			// printBin(v[0], v[1], v[2], v[3]);
			printBin(v[3], v[2], v[1], v[0]);
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
			// cp->displayNeighbors();
			run.push_back(cp);
			bool atEast = g.at(i, j + 1) == nullptr;
			// if (atEast)
			// {
			// 	cout<<"at east\n";
			// } else { cout<<"not at east\n";}
			bool atSouth = g.at(i + 1, j) == nullptr;
			// if (atSouth)
			// {
			// 	cout<<"at south\n";
			// }else { cout<<"not at south\n";}
			bool shouldClose = atEast || (!atSouth && (rand() % 4 == 0));
			// if (shouldClose)
			// {
			// 	cout<<"..........\n";
			// } else { cout<<"....\n";}
			if (shouldClose) {
				// cout<<"closing\n";
				cell* member = run[rand() % run.size()];
				if (g.at(member->row() + 1, member->column()) != nullptr) {
					member->link(*g.at(member->row() + 1, member->column()));
				}
				run.clear();
			} else if (g.at(cp->row(), cp->column() + 1) != nullptr) {
				// cout<<"not closing\n";
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

