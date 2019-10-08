#ifndef MASK_H
#define MASK_H
#include <vector>
#include "grid.h"

class Mask : public Grid {
public:
	Mask(int rows, int columns, std::string path);
	cell* randomCell();
	bool validAt(int r, int c);
	int valid_cells() const;
	int size() const;
	int rows() const;
	int columns() const;
	std::vector<cell*> linklessValidNeighbors(cell* cp);
private:
	void eraseGrid();
	void reconfigureCells();
	void randomLocation(int* X, int* Y);
	int _valid_cells;
	std::vector<std::vector<bool> > _mask;
	std::unordered_set<cell> links;
};

#endif
