/************************************************************
* Name:  Elliott Barinberg                                  *
* Project : Project 1 - Longana								*
* Class : CMPS 366 OPL										*
* Date : 9/9/17												*
************************************************************/
#ifndef BOARDVIEW_H
#define BOARDVIEW_H
#include "stdafx.h"
#include "Tile.h"
#include "Hand.h"
using namespace std;
class BoardView
{
public:
	BoardView();
	static void print_board(std::vector<Tile> a_vec);
	static void print_hand(Hand* a_hand);
};

#endif