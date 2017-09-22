/************************************************************
* Name:  Elliott Barinberg                                  *
* Project : Project 1 - Longana								*
* Class : CMPS 366 OPL										*
* Date : 9/9/17												*
************************************************************/
#ifndef HAND_H
#define HAND_H
#include "stdafx.h"
#include "Tile.h"
using namespace std;
class Hand
{
public:
	Hand();
	~Hand();
	void fill_hand(stack<Tile> pile);
	static int size(vector<Tile> thishand);
	int size();
	Tile at(int num);
	vector<Tile>* get_hand();
	bool has_tile(Tile a_tile);
private:
	vector<Tile> thehand;
};

#endif