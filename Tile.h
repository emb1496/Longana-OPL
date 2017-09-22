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
	bool isDouble();
	void print();
	void set_side_left(int num);
	int get_side_left();
	void set_side_right(int num);
	int get_side_right();
	Tile();
	Tile(int s1, int s2);
	void set_engine(int nummoves);
private:
	int left_side;
	int right_side;
};

#endif