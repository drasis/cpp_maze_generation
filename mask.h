#ifndef MASK_H
#define MASK_H
// This use of #ifndef, #define and #endif is called "an include 
// guard".  It avoids problems with people including header files
// more than once and then having symbols defined more than once.
// #include <string>
#include <vector>
// #include <iostream>
// #include <unordered_set>
#include "grid.h"

class Mask : public Grid {
public:
	Mask(int rows, int columns, std::string path);
	cell* at(int r, int c);
	cell* at(int n);
	cell* randomCell();
	short connections(int r, int c);
	int valid_cells() const;
	int size() const;
	int rows() const;
	int columns() const;
private:
	int _valid_cells;
	std::vector<std::vector<bool> > _mask;
	std::unordered_set<cell> links;
};

#endif
