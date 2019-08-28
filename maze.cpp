#include "randomHelpers.h"
#include "cell.h"
#include "grid.h"
// #include <string>
// #include <sstream>
// #include <vector>
// #include <iostream>
#include <unordered_set>
#include <ctime>
// using namespace std;

char printDig(short digit) {
	return "0123456789abcdef"[digit];
	// cout << "0123456789abcdef"[digit];
}

void printGrid(Grid g, int i = 0) {
	char printout[g.rows()][g.columns()];
	for (int i = 0; i < g.rows(); ++i) {
		for (int j = 0; j < g.columns(); ++j) {
			printout[i][j] = printDig(g.connections(i, j));
		}
	}
	for (int i = 0; i < g.rows(); ++i) {
		for (int j = 0; j < g.columns(); ++j) {
			std::cout << printout[i][j];
		}
		std::cout << std::endl;
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
	std::vector<cell*> run;
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
	std::unordered_set<cell> unvisited;
	for (int i = 0; i < g.size() - 1; ++i) {
		unvisited.insert(*g.at(i));
	}
	// cout << "before removal: " << unvisited.size() << endl;
	cell* first = g.randomCell();
	unvisited.erase(*first);
	std::cout << first << std::endl;
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
				std::cout<<"path length: " << path.size() << std::endl;
				std::cout<<"position:    " << position << std::endl;
				// path.resize(position - 1);
				path.erase(path.begin() + position, path.end());
				std::cout<<"final len:   " << path.size() << "\n\n";
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

void huntAndKill(Grid& g) {
	int unvisited = g.size() - 1;
	cell* cp = g.randomCell();
	while (unvisited > 0) {
		if (cp->neighborsWithNoLinks().size() == 0) {
			for (int i = 0; i < g.size() - 1; ++i) {
				bool happenedUpon = false;
				cell* testing = g.at(i);
				if (testing->hasNoLinks()) {
					std::vector<cell*> neighbors = testing->neighbors();
					for (int j = 0; j < neighbors.size() - 1; ++j) {
						if (!neighbors[j]->hasNoLinks()) {
							testing->link(*neighbors[j]);
							unvisited--;
							cp = testing;
							happenedUpon = true;
							break;
						}
					}
				}
				if (happenedUpon) {
					break;
				}
			}
		} else {
			std::vector<cell*> linkless = cp->neighborsWithNoLinks();
			cell* newcp = linkless[randInt(0, linkless.size() - 1)];
			cp->link(*newcp);
			unvisited--;
			cp = newcp;
		}
	}
}

void recursiveBacktrack(Grid& g) {
	std::vector<cell*> stack;
	cell* cp = g.randomCell();
	stack.push_back(cp);
	while(stack.size() > 0) {
		if (cp->neighborsWithNoLinks().size() == 0) {
			cp = stack[stack.size() - 1];
			stack.pop_back();
		} else {
			std::vector<cell*> linkless = cp->neighborsWithNoLinks();
			cell* nextcp = linkless[randInt(0, linkless.size() - 1)];
			cp->link(*nextcp);
			cp = nextcp;
			stack.push_back(cp);
		}
	}
}

int main(int argc, char *argv[]) {
	srand(time(nullptr));
	// clock_t begin = clock();
	int r, c;

	if (argc == 3) {
		r = std::stoi(argv[1]);
		c = std::stoi(argv[2]);
	} else if (argc == 1) {
		r = 10;
		c = 15;
	} else {
		exit(1);
	}
	Grid g(r, c);
	// cout << "time to make grid: " << double(clock() - begin) << "\n";
	// begin = clock();
	// randomBinaryWalk(g);
	// sidewinderWalk(g);
	// aldousBroder(g);
	// wilson(g); // DOESN'T WORK I NEED TO TAKE A REST FROM THIS ONE!!!!
	recursiveBacktrack(g);
	// cout << "time to make maze: " << double(clock() - begin) << "\n";
	// begin = clock();
	printGrid(g);
	// cout << "time to print maze: " << double(clock() - begin) << "\n";
}

