/************************************************************
* Name:  Elliott Barinberg                                  *
* Project : Project 1 - Longana								*
* Class : CMPS 366 OPL										*
* Date : 9/9/17												*
************************************************************/
#ifndef ROUND_H
#define ROUND_H
#include "Computer.h"
#include "Human.h"
#include "BoardView.h"
class Round
{
public:
	Round();
	bool round_over(Human *p1, Computer *p2, stack<Tile> a_pile);
	void play(Human* p1, Computer* p3, int nummoves, int score, Board* a_board);
	Tile center;
private:
	bool ready_to_start;
};

#endif