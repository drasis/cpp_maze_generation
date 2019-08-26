#ifndef GRID_H
#define GRID_H
// #include <cell.h>
#include "cell.h"
#include <vector>

class cell;

class Grid {
public:
	Grid(int rows, int columns);
	void prepareGrid();
	void configureCells();
	cell* at(int r, int c);
	cell* at(int n);
	cell* randomCell();
	short connections(int r, int c);
	int size() const;
	int rows() const;
	int columns() const;
private:
	int _rows, _columns;
	std::vector<std::vector<cell*> > cells;
};

#endif