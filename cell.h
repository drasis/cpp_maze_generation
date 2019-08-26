#ifndef CELL_H
#define CELL_H
// This use of #ifndef, #define and #endif is called "an include 
// guard".  It avoids problems with people including header files
// more than once and then having symbols defined more than once.
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
	void setnorth(cell& c); 
	void setsouth(cell& c);
	void seteast(cell& c);
	void setwest(cell& c);
	void link(cell& c, bool bidi = true);
	void unlink(cell& c, bool bidi = true);
	bool linked(cell c);
	void displayLinks();
	void display() const;
	std::vector<cell> getLinks();
	// void neighborFlags(bool(&c)[4]) const;
private:
	int row, column;
	cell* north; cell* south; cell* east; cell* west;
	std::unordered_set<cell> links;
};

#endif