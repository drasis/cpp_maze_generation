#ifndef CELL_H
#define CELL_H
#include <string>
#include <iostream>
#include <unordered_set>

class cell;

namespace std {
  template<>
  struct hash<cell> {
  public:
    size_t operator()(const cell &c) const; // don't define yet
  };
}

class cell {
	friend std::ostream& operator<<(std::ostream& os, const cell& thecell);
	friend bool operator==(const cell &cell1, const cell &cell2);
	friend size_t std::hash<cell>::operator ()(const cell& c) const;
public:
	cell(int row, int col);
	int row() const;
	int column() const;
	void setnorth(cell& c, bool tonull = false); 
	cell* getnorth() const;
	void setsouth(cell& c, bool tonull = false);
	cell* getsouth() const;
	void seteast(cell& c, bool tonull = false);
	cell* geteast() const;
	void setwest(cell& c, bool tonull = false);
	cell* getwest() const;
	void link(cell* c, bool bidi = true);
	void unlink(cell* c, bool bidi = true);
	bool linked(cell* c);
	void displayLinks();
	void displayNeighbors() const;
	std::vector<cell*> getLinks();
	cell* randomNeighbor();
	bool hasNoLinks();
	short connections();
	std::vector<cell*> neighbors();
	std::vector<cell*> neighborsWithNoLinks();
private:
	int _row, _column;
	cell* north; cell* south; cell* east; cell* west;
	std::unordered_set<cell*> links;
};

#endif
