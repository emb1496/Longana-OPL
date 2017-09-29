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

	// constructor and destructor
	Round();
	~Round();

	// check if the round is over
	bool round_over(Human *p1, Computer *p2, stack<Tile> a_pile);

	// play the round
	void play(Human* p1, Computer* p3, int nummoves, int score, Board* a_board);

	// the players make the moves
	void players_make_moves(Human* p1, Computer* p3, Board* a_board, int nummoves, int score);

	// the players draw until they have the center
	void neither_has_center(Human* p1, Computer* p3, Board* a_board);
private:
	Tile center;
	bool ready_to_start;
	char a_char;
	string input;
};

#endif