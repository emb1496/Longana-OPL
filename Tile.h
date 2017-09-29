/************************************************************
* Name:  Elliott Barinberg                                  *
* Project : Project 1 - Longana								*
* Class : CMPS 366 OPL										*
* Date : 9/9/17												*
************************************************************/
#ifndef TILE_H
#define TILE_H
#include "stdafx.h"
class Tile
{
public:
	// is the tile a double
	bool isDouble();

	// print the tile
	inline void print() { std::cout << "(" << left_side << " - " << right_side << ")"; }

	// get and set for left side
	inline void set_side_left(int num) { left_side = num; }
	inline int get_side_left() { return left_side; }
	
	// get and set for right side
	inline void set_side_right(int num) { right_side = num; }
	inline int get_side_right() { return right_side; }

	// constructors and destructors
	Tile();
	Tile(int s1, int s2);
	~Tile();

	// set the tile to the engine
	void set_engine(int nummoves);
private:
	int left_side;
	int right_side;
};

#endif