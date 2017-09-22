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
	void who_won(Human* p1, Computer* computer);
	inline int get_score();
	inline int get_nummoves();
	void play(Round* a_round, Human* p1, Computer* computer, Board* the_board, int nummoves, int score);
	bool game_over(Human* p1, Computer* p2);
	bool game_over(Human* p1, Computer* p2, int score);
	Tournament();
	Tournament(Human* p1, Computer* computer, Board* the_board, Round* a_round, int nummoves, int score);
private:
	int score;
	std::vector<Round> t_vec;
	Tile center;
	int nummoves;
	bool readytostart;
	string input;
};

#endif