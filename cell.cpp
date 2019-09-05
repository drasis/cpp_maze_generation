#include "cell.h"
#include "randomHelpers.h"
#include <iostream>
#include <unordered_set>
#include <vector>

///////////////////////////////////////////////////////////////////////////////
// CONSTRUCTOR ////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

cell::cell(int row, int col) {
	this->_row = row;
	this->_column = col;
	this->north = nullptr;
	this->south = nullptr;
	this->east = nullptr;
	this->west = nullptr;
}

///////////////////////////////////////////////////////////////////////////////
// GETTING AND SETTING ROWS, COLUMNS, NEIGHBORS ///////////////////////////////
///////////////////////////////////////////////////////////////////////////////

cell* cell::randomNeighbor() {
	std::vector<cell*> validNeighbors;
	if (this->north != nullptr) {
		validNeighbors.push_back(this->north);
	}
	if (this->east != nullptr) {
		validNeighbors.push_back(this->east);
	}
	if (this->south != nullptr) {
		validNeighbors.push_back(this->south);
	}
	if (this->west != nullptr) {
		validNeighbors.push_back(this->west);
	}
	if (validNeighbors.size() == 0) {
		return nullptr;
	}
	return validNeighbors[randInt(0, validNeighbors.size() - 1)];
}

int cell::row() const{
	return this->_row;
}

int cell::column() const{
	return this->_column;
}

void cell::setnorth(cell& c, bool tonull) {
	// std::cout << "call to north\n";
	// std::cout <<"this: " << this << "\nthis->north: " << this->north << std::endl;
	if (!tonull) {
		this->north = &c;
	} else {
		this->north = nullptr;
	}
	// std::cout << "leaving north\n";
}

void cell::setsouth(cell& c, bool tonull) {
	// std::cout << "call to south\n" << std::flush;
	if (!tonull) {
		this->south = &c;
	} else {
		this->south = nullptr;
	}
}

void cell::seteast(cell& c, bool tonull) {
	// std::cout << "call to east\n";
	if (!tonull) {
		this->east = &c;
	} else {
		this->east = nullptr;
	}
}

void cell::setwest(cell& c, bool tonull) {
	// std::cout << "call to west\n";
	if (!tonull) {
		this->west = &c;
	} else {
		this->west = nullptr;
	}
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

///////////////////////////////////////////////////////////////////////////////
// OPERATORS SO CELL CLASS CAN BE USED IN UNORDERED SET AND USED IN OSTREAM ///
///////////////////////////////////////////////////////////////////////////////

std::ostream& operator<<(std::ostream& os, const cell& thecell) {
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

///////////////////////////////////////////////////////////////////////////////
// METHODS TO LINK TO OTHER CELLS /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

bool cell::hasNoLinks() {
	return this->links.size() == 0;
}

void cell::link(cell* c, bool bidi) {
	links.insert(c);
	if (bidi) {
		c->link(this, false);
	}
}

void cell::unlink(cell* c, bool bidi) {
	links.erase(c);
	if (bidi) {
		c->unlink(this, false);
	}
}

bool cell::linked(cell* c) {
	return contains(this->links, c);
}

std::vector<cell*> cell::getLinks() {
	std::vector<cell*> connectedCells;
	std::unordered_set<cell*>::iterator c;
	for (c = this->links.begin(); c != this->links.end(); c++) {
		connectedCells.push_back(*c);
	}
	return connectedCells;
}

short cell::connections() {
	int v[4] = {true, true, true, true};
	if (this->north != nullptr) {
		v[0] = !this->linked(this->north);
	}
	if (this->east != nullptr) {
		v[1] = !this->linked(this->east);
	}
	if (this->south != nullptr) {
		v[2] = !this->linked(this->south);
	}
	if (this->west != nullptr) {
		v[3] = !this->linked(this->west);
	}
	return v[3] << 3 | v[2] << 2 | v[1] << 1 | v[0];
}

std::vector<cell*> cell::neighbors() {
	std::vector<cell*> ret;
	if (this->north != nullptr) {
		ret.push_back(north);
	}
	if (this->east != nullptr) {
		ret.push_back(east);
	}
	if (this->south != nullptr) {
		ret.push_back(south);
	}
	if (this->west != nullptr) {
		ret.push_back(west);
	}
	return ret;
}

std::vector<cell*> cell::neighborsWithNoLinks() {
	std::vector<cell*> ret = *(new std::vector<cell*>);
	if (this->north != nullptr) {
		if(this->north->hasNoLinks()) {
			ret.push_back(north);
		}
	}
	if (this->east != nullptr) {
		if(this->east->hasNoLinks()) {
			ret.push_back(east);
		}
	}
	if (this->south != nullptr) {
		if(this->south->hasNoLinks()) {
			ret.push_back(south);
		}
	}
	if (this->west != nullptr) {
		if(this->west->hasNoLinks()) {
			ret.push_back(west);
		}
	}
	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// DISPLAY METHODS FOR DEBUGGING //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void cell::displayLinks() {
	std::cout << *this << " linked to:\n";
	std::unordered_set<cell*>::iterator c;
	for (c = this->links.begin(); c != this->links.end(); c++) {
		std::cout << "    " << *c << "\n";
	}
}

void cell::displayNeighbors() const {
	std::cout << *this << " has neighbors:\n    north: ";
	if (this->north == nullptr) {
		std::cout<< "null\n    east: ";
	} else {
		std::cout<< *this->north << "\n    east: ";
	}
	if (this->east == nullptr) {
		std::cout<< "null\n    south: ";
	} else {
		std::cout<< *this->east << "\n    south: ";
	}
	if (this->south == nullptr) {
		std::cout<< "null\n    west: ";
	} else {
		std::cout<< *this->south << "\n    west: ";
	}
	if (this->west == nullptr) {
		std::cout<< "null\n";
	} else {
		std::cout<< *this->west << "\n";
	}
}