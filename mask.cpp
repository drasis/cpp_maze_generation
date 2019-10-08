#include "randomHelpers.h"
#include "cell.h"
#include "mask.h"
#include <fstream>

Mask::Mask(int rows, int columns, std::string path) : Grid(rows, columns) {
	this->_valid_cells = 0;
	std::string line;
	std::ifstream inp(path);
	if (inp.is_open()) {
		while(getline(inp, line)) {
			std::vector<bool> v;
			for (int i = 0; i < line.length(); ++i) {
				v.push_back(line[i] == 'x');
				if (line[i] == 'x') {
					this->_valid_cells += 1;
				}
			}
			this->_mask.push_back(v);
		}
		inp.close();
	} else {
		std::cout << "couldn't read file\n";
		exit(1);
	}
	if (this->_mask.size() != this->_rows || 
		this->_mask[0].size() != this->_columns) {
		std::cout << "mask size does not match input size\n";
		exit(1);
	}
}

int Mask::valid_cells() const {
	return this->_valid_cells;
}

void Mask::eraseGrid() {
	for (int r = 0; r < this->_rows; r++) {
		for (int c = 0; c < this->_columns; c++) {
			if (!this->validAt(r, c)) {
				// delete this->cells.at(r).at(c);
				this->cells.at(r).at(c) = nullptr;
			}
		}
	}
}

std::vector<cell*> Mask::linklessValidNeighbors(cell* cp) {
	std::vector<cell*> linklessNeighbors = cp->neighborsWithNoLinks();
	std::vector<cell*> ret;
	for (int i = 0; i < linklessNeighbors.size(); ++i) {
		if (this->validAt(linklessNeighbors[i]->row(), linklessNeighbors[i]->column())) {
			ret.push_back(linklessNeighbors[i]);
		}
	}
	return ret;
}

void Mask::reconfigureCells() {
	// std::cout<< "this->_rows is " << this->_rows << "\n";
	// std::cout<< "this->_columns is " << this->_columns << "\n";
	cell* cellnullptr = nullptr;
	for (int r = 0; r < this->_rows; r++) {
		for (int c = 0; c < this->_columns; c++) {
			// std::cout<< "r: " << r << "\nc: " << c << "\n";
			cell& tc = *this->at(r, c);
			if (this->validAt(r, c)) {
				tc.setnorth(*this->at(r - 1, c), this->validAt(r - 1, c));
				tc.setsouth(*this->at(r + 1, c), this->validAt(r + 1, c));
				tc.seteast(*this->at(r, c + 1), this->validAt(r, c + 1));
				tc.setwest(*this->at(r, c - 1), this->validAt(r, c - 1));
			}
			
		}
	}
}

bool Mask::validAt(int r, int c) {
	if (r < 0 || r >= this->_rows || c < 0 || c >= this->_columns) {
		return false;
	}
	return this->_mask.at(r).at(c);
}

cell* Mask::randomCell() {
	int* r; int* c;
	randomLocation(r, c);
	return this->at(*r, *c);
}

void Mask::randomLocation(int* r, int* c) {
	(*r) = randInt(0, this->_rows - 1);
	(*c) = randInt(0, this->_columns - 1);
	while(!this->validAt(*r, *c)) {
		(*r) = randInt(0, this->_rows - 1);
		(*c) = randInt(0, this->_columns - 1);
	}
}