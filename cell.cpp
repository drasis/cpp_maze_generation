#include "cell.h"
#include <iostream>
#include <unordered_set>
#include <vector>

// When we're not in a header file, it is ok to
// have "using namespace std"
using namespace std;

template <class T>
bool contains(unordered_set<T> myset, T i) {
	return myset.find(i) == myset.end();
}

cell::cell(int row, int col) {
	this->row = row;
	this->column = col;
	this->north = nullptr;
	this->south = nullptr;
	this->east = nullptr;
	this->west = nullptr;
}

void cell::setnorth(cell& c) {
	this->north = &c;
}

void cell::setsouth(cell& c) {
	this->south = &c;
}

void cell::seteast(cell& c) {
	this->east = &c;
}

void cell::setwest(cell& c) {
	this->west = &c;
}

ostream& operator<<(ostream& os, const cell& thecell) {
	os << "cell(" << thecell.row << " " << thecell.column << ")";
	return os; 
}

bool operator==(const cell &cell1, const cell &cell2) {
	return cell1.row == cell2.row && cell1.column == cell2.column;
}

namespace std {
  size_t hash<cell>::operator()(const cell &c) const {
  	int shiftAmt = int(sizeof(size_t) * 4); // half of size_t
  	size_t colShifted = size_t(c.column) << shiftAmt;
  	return colShifted | size_t(c.row);
  }
}

void cell::link(cell& c, bool bidi) {
	links.insert(c);
	if (bidi) {
		c.link(*this, false);
	}
}

void cell::unlink(cell& c, bool bidi) {
	links.erase(c);
	if (bidi) {
		c.unlink(*this, false);
	}
}

bool cell::linked(cell c) {
	return contains(this->links, c);
}

void cell::displayLinks() {
	cout << *this << " linked to:\n";
	unordered_set<cell>::iterator c;
	for (c = this->links.begin(); c != this->links.end(); c++) {
		cout << "    " << *c << "\n";
	}
}

vector<cell> cell::getLinks() {
	vector<cell> connectedCells;
	unordered_set<cell>::iterator c;
	for (c = this->links.begin(); c != this->links.end(); c++) {
		connectedCells.push_back(*c);
	}
	return connectedCells;
};