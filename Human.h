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

	// constructor and destructor
	Human();
	~Human();

	// large play function which gives used options
	void play(int boneyard_size, int left_end, int right_end, Board* a_board, int nummoves, bool last_played, int tourn_score, Computer* comp);
	
	// makes sure its a legal move
	bool play(int num, char let, int left_end, int right_end, bool last_passed);
	
	// allows to know if a player is human
	inline bool is_human() { return true; }

	// sets whether player passed
	inline void set_passed(bool pass) { passed_last_move = pass; }

	// gets whether player passed
	inline bool get_passed() { return passed_last_move; }

	// no serialization if a player just passed
	int just_passed(Computer* comp, int left_end, int right_end, Board* a_board, int nummoves, int tourn_score);
private:
	string buffer;
	Tile* temp;
	int num;
	char side;
	bool has_legal_move;
	int count;
	bool passed_last_move;
	bool lcv;
};

#endif