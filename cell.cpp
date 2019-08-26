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
	this->_row = row;
	this->_column = col;
	this->north = nullptr;
	this->south = nullptr;
	this->east = nullptr;
	this->west = nullptr;
}

int cell::row() const{
	return this->_row;
}

int cell::column() const{
	return this->_column;
}

void cell::setnorth(cell& c) {
	this->north = &c;
	// cout << this->north << endl;
	// cout<< "setting north\n";
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

cell* cell::getnorth() const {
	return this->north;
}

cell* cell::getsouth() const {
	return this->south;
}

cell* cell::geteast() const {
	return this->east;
}

cell* cell::getwest() const {
	return this->west;
}

ostream& operator<<(ostream& os, const cell& thecell) {
	os << "cell(" << thecell._row << " " << thecell._column << ")";
	return os; 
}

bool operator==(const cell &cell1, const cell &cell2) {
	return cell1._row == cell2._row && cell1._column == cell2._column;
}

namespace std {
  size_t hash<cell>::operator()(const cell &c) const {
  	int shiftAmt = int(sizeof(size_t) * 4); // half of size_t
  	size_t colShifted = size_t(c._column) << shiftAmt;
  	return colShifted | size_t(c._row);
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

void cell::displayNeighbors() const {
	cout << *this << " has neighbors:\n    north: ";
	if (this->north == nullptr) {
		cout<< "null\n    east: ";
	} else {
		cout<< *this->north << "\n    east: ";
	}
	if (this->east == nullptr) {
		cout<< "null\n    south: ";
	} else {
		cout<< *this->east << "\n    south: ";
	}
	if (this->south == nullptr) {
		cout<< "null\n    west: ";
	} else {
		cout<< *this->south << "\n    west: ";
	}
	if (this->west == nullptr) {
		cout<< "null\n";
	} else {
		cout<< *this->west << "\n";
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