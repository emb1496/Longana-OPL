/************************************************************
* Name:  Elliott Barinberg                                  *
* Project : Project 1 - Longana								*
* Class : CMPS 366 OPL										*
* Date : 9/9/17												*
************************************************************/
#ifndef BOARDVIEW_H
#define BOARDVIEW_H

// include files for BoardView
#include "stdafx.h"
#include "Tile.h"
#include "Hand.h"
#include "Human.h"
#include "Computer.h"
using namespace std;

static class BoardView
{
public:
	// print the board
	static void print_board(vector<Tile> &a_vec);

	// print the player hand
	static void print_hand(Hand* a_hand);

	// print the number of tiles in the deck
	inline static void print_boneyard_size(const stack<Tile> &a_pile) {	cout << "\n\nBoneyard has " << a_pile.size() << " tiles remaining\n"; }

	// print who won and then allow the user to continue onto the next round
	static void print_who_won(Human* p1, Computer* p2, int score);

private:
};

#endif