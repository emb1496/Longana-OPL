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
	// constructor and destructor
	Computer();
	~Computer();

	// returns a vector of tiles in the order of which is best to play at 0 and worst at n
	static vector<Tile> best_tiles_to_play(Hand* a_hand);

	// computer play's based on computer hand
	void play(int boneyard_size, int left_most, int right_most, Board* a_board, bool last_played);

	// is the player human
	inline bool is_human() { return false; }

	// plays a tile on the board
	bool play_tile(Tile* playthis, int left_end, int right_end, Board* a_board, bool last_played);

	// returns if the a_hand can play a legal move
	static bool has_a_legal_move(bool last_passed, int left_end, int right_end, Hand* a_hand, bool is_human);

	// inline get and set functions for passed_last_move
	inline void set_passed(bool passed) { passed_last_move = passed; }
	inline bool get_passed() { return passed_last_move; }

private:

	// vector of Tiles representing best tile to play
	vector<Tile> best_play_order;

	// boolean representing whether or not player has a legal move
	bool has_legal_move;

	// number and letter for move
	int num;
	char let;

	// repeat is a loop control variable
	bool repeat;

	// did the player pass last move
	bool passed_last_move;
};
#endif