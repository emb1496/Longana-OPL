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

	// constructor and destructor
	Hand();
	~Hand();

	// insert pile into hand
	void fill_hand(stack<Tile> pile);

	// get size of thishand
	inline int size(vector<Tile> thishand) { return thishand.size(); }

	// get size of the hand
	inline int size() { return thehand.size(); }

	// return tile in vector using "at"
	inline Tile at(int a) { return thehand[a]; }

	// get a pointer to the hand
	inline vector<Tile>* get_hand() { return &thehand; }

	// check if the hand contains a tile
	bool has_tile(Tile a_tile);
private:

	// the holy grail - the hand
	vector<Tile> thehand;
};

#endif