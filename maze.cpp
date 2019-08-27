#include "randomHelpers.h"
#include "cell.h"
#include "grid.h"
// #include <string>
// #include <sstream>
// #include <vector>
// #include <iostream>
#include <unordered_set>
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

void sidewinderWalk(Grid& g) {
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
	unordered_set<cell> unvisited;
	for (int i = 0; i < g.size() - 1; ++i) {
		unvisited.insert(*g.at(i));
	}
	// cout << "before removal: " << unvisited.size() << endl;
	cell* first = g.randomCell();
	unvisited.erase(*first);
	cout << first << endl;
	// cout << "after removal:  " << unvisited.size() << endl;
	std::vector<cell> path;
	while (unvisited.size() > 0) {
		// cout<<"first while\n";
		cell c = randomElement(unvisited);
		path.push_back(c);
		// cout << "number of unvisited: " << unvisited.size() << endl;
		while(contains(unvisited, c)) {
			// cout<<"innerwhile\n";
			c = *c.randomNeighbor();
			int position = findIndex(path, c);
			if (position == -1) {
				path.push_back(c);
			} else if (position > 0) {
				cout<<"path length: " << path.size() << endl;
				cout<<"position:    " << position << endl;
				// path.resize(position - 1);
				path.erase(path.begin() + position, path.end());
				cout<<"final len:   " << path.size() << endl << endl;
			} else if (position == 0) {
				path.clear();
			}
		}
		for (int i = 0; i < path.size() - 2; ++i) {
			path[i].link(path[i + 1]);
			unvisited.erase(path[i]);
		}
		path.clear();
		// printGrid(g);
		// cout << "number of unvisited: " << unvisited.size() << endl;
		// cout << "\n\n\n";
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
	// sidewinderWalk(g);
	// aldousBroder(g);
	// wilson(g); // DOESN'T WORK I NEED TO TAKE A REST FROM THIS ONE!!!!
	
	printGrid(g);
}

