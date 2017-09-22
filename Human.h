/************************************************************
* Name:  Elliott Barinberg                                  *
* Project : Project 1 - Longana								*
* Class : CMPS 366 OPL										*
* Date : 9/9/17												*
************************************************************/
#ifndef HUMAN_H
#define HUMAN_H
#include "Computer.h"
class Human : public Player {
public:
	void play(int boneyard_size, int left_end, int right_end, Board* a_board, int nummoves, bool last_played, int tourn_score, Computer* comp);
	bool play(int num, char let, int left_end, int right_end, bool last_passed);
	virtual bool is_human();
private:
	string buffer;
	Tile temp;
	int num;
	char side;
	bool has_legal_move;
};

#endif