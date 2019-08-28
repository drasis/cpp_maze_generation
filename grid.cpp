#include "grid.h"
#include "cell.h"
#include "randomHelpers.h"
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
			this->cells[r][c] = new cell(r, c);
		}
	}
}

cell* Grid::at(int r, int c) {
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
	return this->_rows;
}

int Grid::columns() const {
	return this->_columns;
}

cell* Grid::randomCell() {
	return this->at(randInt(0, this->rows() - 1), randInt(0, this->_columns - 1));
}

short Grid::connections(int r, int c) {
	return this->at(r, c)->connections();
}

void Grid::configureCells() {
	for (int r = 0; r < this->_rows; r++) {
		for (int c = 0; c < this->_columns; c++) {
			cell& tc = *this->at(r, c);
			tc.setnorth(*this->at(r - 1, c));
			tc.setsouth(*this->at(r + 1, c));
			tc.seteast(*this->at(r, c + 1));
			tc.setwest(*this->at(r, c - 1));
			// cell* tc = this->at(r, c);
			// tc->setnorth(*this->at(r - 1, c));
			// tc->setsouth(*this->at(r + 1, c));
			// tc->seteast(*this->at(r, c + 1));
			// tc->setwest(*this->at(r, c - 1));
		}
	}
}

int Grid::size() const {
	return this->_rows * this->_columns;
}