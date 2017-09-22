/************************************************************
* Name:  Elliott Barinberg                                  *
* Project : Project 1 - Longana								*
* Class : CMPS 366 OPL										*
* Date : 9/9/17												*
************************************************************/
#ifndef COMPUTER_H
#define COMPUTER_H
#include "Player.h"
class Computer : public Player {

public:
	Computer();
	static vector<Tile> best_tiles_to_play(Hand* a_hand);
	void play(int boneyard_size, int left_most, int right_most, Board* a_board, bool last_played);
	virtual bool is_human();
	bool play_tile(Tile* playthis,int left_end, int right_end, Board* a_board, bool last_played);
	static bool has_a_legal_move(bool last_passed, int left_end, int right_end, Hand* a_hand);
private:
	vector<Tile> best_play_order;
	bool has_legal_move;
	int num;
	char let;
};
#endif