#include "cell.h"
#include "grid.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

void printBin(bool a, bool b, bool c, bool d) {
	if (!a && !b && !c && !d) {
		cout << 0;
	} else if (!a && !b && !c && d) {
		cout << 1;
	} else if (!a && !b && c && !d) {
		cout << 2;
	} else if (!a && !b && c && d) {
		cout << 3;
	} else if (!a && b && !c && !d) {
		cout << 4;
	} else if (!a && b && !c && d) {
		cout << 5;
	} else if (!a && b && c && !d) {
		cout << 6;
	} else if (!a && b && c && d) {
		cout << 7;
	} else if (a && !b && !c && !d) {
		cout << 8;
	} else if (a && !b && !c && d) {
		cout << 9;
	} else if (a && !b && c && !d) {
		cout << 'a';
	} else if (a && !b && c && d) {
		cout << 'b';
	} else if (a && b && !c && !d) {
		cout << 'c';
	} else if (a && b && !c && d) {
		cout << 'd';
	} else if (a && b && c && !d) {
		cout << 'e';
	} else if (a && b && c && d) {
		cout << 'f';
	} 
}

void checkLink(cell& c1, cell& c2) {
	if (c1.linked(c2) && c2.linked(c1)) {
		cout << "linked\n";
	} else {
		cout << "not linked\n";
	}
}

int main() {
	cell c = cell(1, 2);
	cell c2 = cell(2, 2);
	c2.link(c);
	c.link(c2);
	c2.displayLinks();
	c.displayLinks();
	c.unlink(c2);
	c.unlink(c2);
	c.displayLinks();
	c2.displayLinks();
	Grid g(20,20);
	for (int i = 0; i < g.rows(); ++i) {
		for (int j = 0; j < g.columns(); ++j) {
			cell cp = *g.at(i, j);
			int v[4];
			v[0] = g.at(i - 1, j) != nullptr;
			v[1] = g.at(i, j + 1) != nullptr;
			v[2] = g.at(i + 1, j) != nullptr;
			v[3] = g.at(i, j - 1) != nullptr;
			if (v[0]) {
				v[0] = cp.linked(*g.at(i - 1, j));
			}
			if (v[1]) {
				v[1] = cp.linked(*g.at(i, j + 1));
			}
			if (v[2]) {
				v[2] = cp.linked(*g.at(i + 1, j));
			}
			if (v[3]) {
				v[3] = cp.linked(*g.at(i, j - 1));
			}
			// cout<<cp;
			printBin(v[0], v[1], v[2], v[3]);
		}
		cout << endl;
	}
}

