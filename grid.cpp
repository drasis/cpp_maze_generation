#include "grid.h"
#include "cell.h"
#include <vector>
#include <math.h>

Grid::Grid(int rows, int columns) {
	this->_rows = rows;
	this->_columns = columns;
	this->prepareGrid();
	this->configureCells();
}

void Grid::prepareGrid() {
	for (int r = 0; r < this->_rows; r++) {
		std::vector<cell*> v (this->_columns);
		this->cells.push_back(v);
	}
	for (int r = 0; r < this->_rows; r++) {
		for (int c = 0; c < this->_columns; c++) {
			cell* tn = new cell(r, c);
			this->cells[r][c] = tn;
		}
	}
}

cell* Grid::at(int r, int c) {
	// std::cout<< "r: " << r << "  c: " << c << std::endl;
	if (r >= 0 && r < this->_rows && c < this->_columns && c >= 0) {
		return this->cells.at(r).at(c);
	} else {
		return nullptr;
	}
}

cell* Grid::at(int n) {
	if (n < 0 || n > this->size() - 1) {
		return nullptr;
	} else {
		return this->cells.at(floor(n/this->_columns)).at(n % this->_columns);
	}
}

int Grid::rows() const {
	// std::cout<<"rows\n";
	return this->_rows;
}

int Grid::columns() const {
	// std::cout<<"cols\n";
	return this->_columns;
}

cell* Grid::randomCell() {
	return this->at(std::rand() % this->_rows, std::rand() % this->_columns);
}

short Grid::connections(int r, int c) {
	cell cp = *this->at(r, c);
	int v[4] = {true, true, true, true};
	if (!(this->at(r - 1, c) == nullptr)) {
		v[0] = cp.linked(*this->at(r - 1, c));
	}
	if (!(this->at(r, c + 1) == nullptr)) {
		v[1] = cp.linked(*this->at(r, c + 1));
	}
	if (!(this->at(r + 1, c) == nullptr)) {
		v[2] = cp.linked(*this->at(r + 1, c));
	}
	if (!(this->at(r, c - 1) == nullptr)) {
		v[3] = cp.linked(*this->at(r, c - 1));
	}
	return v[3] << 3 | v[2] << 2 | v[1] << 1 | v[0];
}

void Grid::configureCells() {
	for (int r = 0; r < this->_rows; r++) {
		for (int c = 0; c < this->_columns; c++) {
			cell tc = *this->at(r, c);
			tc.setnorth(*this->at(r - 1, c));
			tc.setsouth(*this->at(r + 1, c));
			tc.seteast(*this->at(r, c + 1));
			tc.setwest(*this->at(r, c - 1));
		}
	}
}

int Grid::size() const {
	return this->_rows * this->_columns;
}