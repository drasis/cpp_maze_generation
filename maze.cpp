#include "randomHelpers.h"
#include "cell.h"
#include "grid.h"
#include "mask.h"
#include <unordered_set>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void debugGrid(Grid& g) {
	for (int r = 0; r < g.rows(); ++r) {
		for (int c = 0; c < g.columns(); ++c) {
			if (g.at(r, c) != nullptr) {
				g.at(r, c)->displayNeighbors();
			}
			
		}
	}
}

void printGrid(Grid& g, int i = 0) {
	for (int i = 0; i < g.rows(); ++i) {
		for (int j = 0; j < g.columns(); ++j) {
			std::cout << "0123456789abcde0"[g.connections(i, j)];
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
				g.at(i, j)->link(cells[ind]);
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
					member->link(member->getsouth());
				}
				run.clear();
			} else if (cp->geteast() != nullptr) {
				cp->link(cp->geteast());
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
			cp->link(neighbor);
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
	cell* first = g.randomCell();
	unvisited.erase(*first);
	std::cout << first << std::endl;
	std::vector<cell> path;
	while (unvisited.size() > 0) {
		cell c = randomElement(unvisited);
		path.push_back(c);
		while(contains(unvisited, c)) {
			c = *c.randomNeighbor();
			int position = findIndex(path, c);
			if (position == -1) {
				path.push_back(c);
			} else if (position > 0) {
				path.erase(path.begin() + position, path.end());
			} else if (position == 0) {
				path.clear();
			}
		}
		for (int i = 0; i < path.size() - 2; ++i) {
			path[i].link(&path[i + 1]);
			unvisited.erase(path[i]);
		}
		path.clear();
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
							testing->link(neighbors[j]);
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
			cp->link(newcp);
			unvisited--;
			cp = newcp;
		}
	}
}

void backtrackingCarver(Grid& g) {
	std::vector<cell*> stack;
	stack.push_back(g.randomCell());
	while(stack.size() > 0) {
		cell* cp = stack.at(stack.size() - 1);
		std::vector<cell*> linklessNeighbors = cp->neighborsWithNoLinks();
		if (linklessNeighbors.size() > 0) {
			cell* nextcp = linklessNeighbors[randInt(0, linklessNeighbors.size() - 1)];
			stack.push_back(nextcp);
			cp->link(nextcp);
		} else {
			stack.pop_back();
		}
	}
}

void backtrackingCarverMasked(Mask& g) {
	std::vector<cell*> stack;
	stack.push_back(g.at(8, 47));
	while(stack.size() > 0) {
		cell* cp = stack.at(stack.size() - 1);
		std::vector<cell*> linklessNeighbors = g.linklessValidNeighbors(cp);
		if (linklessNeighbors.size() > 0) {
			cell* nextcp = linklessNeighbors[randInt(0, linklessNeighbors.size() - 1)];
			stack.push_back(nextcp);
			cp->link(nextcp);
		} else {
			stack.pop_back();
		}
	}
}

int main(int argc, char *argv[]) {
	int r, c;
	std::string filepath;

	if (argc == 3) {
		// two arguments assumed to be in format: row (int), col (int)
		r = std::stoi(argv[1]);
		c = std::stoi(argv[2]);
	} else if (argc == 2) {
		// one argument assumed to be in the format: filepath to mask
		// mask contains 'x' chars and ' ' chars of maze shape
		Mask m(rowsOfText(argv[1]), 
			columnsOfText(argv[1]), 
			argv[1]);
		backtrackingCarverMasked(m);
		printGrid(m);
		exit(0);
	} else if (argc == 1) {
		// no args generates maze of 15x15
		r = 15;
		c = 15;
	} else {
		exit(1);
	}
	Grid g(r, c);
	backtrackingCarver(g);
	printGrid(g);
}
