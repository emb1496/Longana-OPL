/************************************************************
* Name:  Elliott Barinberg                                  *
* Project : Project 1 - Longana								*
* Class : CMPS 366 OPL										*
* Date : 9/9/17												*
************************************************************/
#ifndef TOURNAMENT_H
#define TOURNAMENT_H
#include "Round.h"
using namespace std;
class Tournament
{
public:
	// inline get score
	inline int get_score() { return score; }

	// inline get nummoves
	inline int get_nummoves() { return nummoves; }

	// play the tournament
	void play(Round* a_round, Human* p1, Computer* computer, Board* the_board, int nummoves, int score);
	
	// check if the game is over
	bool game_over(Human* p1, Computer* p2, int a_score);

	// constructors and destructor
	Tournament();
	Tournament(Human* p1, Computer* computer, Board* the_board, Round* a_round, int nummoves, int score);
	~Tournament();
private:
	char a_char;
	int score;
	Tile* center;
	int nummoves;
	bool readytostart;
	string input;
};

#endif