#include "cell.h"
#include "mask.h"
#include <fstream>
// #include "randomHelpers.h"
// #include <iostream>
// #include <unordered_set>
// #include <vector>

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
				// if (v[v.size() - 1]) {
				// 	std::cout << "▉▉";
				// } else {
				// 	std::cout << "  ";
				// }
			}
			// std::cout<< "\n";
			this->_mask.push_back(v);
		}
		inp.close();
	} else {
		std::cout << "couldn't read file\n";
		exit(1);
	}
	std::cout<< "valid cells: " << this->valid_cells() << std::endl;
	if (this->_mask.size() != this->_rows || 
		this->_mask[0].size() != this->_columns) {
		std::cout << "mask size does not match input size\n";
		exit(1);
	}
}

int Mask::valid_cells() const {
	return this->_valid_cells;
}