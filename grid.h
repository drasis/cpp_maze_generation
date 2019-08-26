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
	int size() const;
	int rows();
	int columns();
private:
	int _rows, _columns;
	std::vector<std::vector<cell*> > cells;
};

#endif