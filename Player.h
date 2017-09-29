/************************************************************
* Name:  Elliott Barinberg                                  *
* Project : Project 1 - Longana								*
* Class : CMPS 366 OPL										*
* Date : 9/9/17												*
************************************************************/
#ifndef PLAYER_H
#define PLAYER_H
#include "Board.h"
#include "stdafx.h"
using namespace std;
class Player
{
public:

	// pure virtual function is human
	virtual bool is_human() =0;

	// adds up the pips
	int make_a_num();

	// does the player have the tile
	bool has_tile(Tile center);

	// get the size of the hand
	inline int get_hand_size(Hand* the_hand) { return the_hand->size(*the_hand->get_hand()); }

	// add to player score
	inline void add_to_score(int num) { score += num; }

	// return player score
	inline int get_score() { return score; }

	// fill hand with a stack of tiles
	inline void fill_hand(stack<Tile> pile) { a_hand->fill_hand(pile); }

	// constructor and destructor
	Player();
	~Player();

	// return Hand*
	inline Hand* get_hand() { return a_hand; }

	// remove the tile a_tile from the hand
	void remove_tile(Tile a_tile);

	// set and get player move
	inline void set_player_move(bool move) { player_move = move; }
	inline bool get_player_move() { return player_move; }
private:
	bool player_move;
	int score;
	Hand* a_hand;
	Hand* a_temp;
	int total;
};
#endif