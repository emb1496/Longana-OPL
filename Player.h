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
	virtual bool is_human()=0;
	int make_a_num();
	bool has_tile(Tile center);
	int get_hand_size(Hand* a_hand);
	void add_to_score(int num);
	int get_score();
	void set_passed(bool passed);
	bool get_passed();
	void fill_hand(stack <Tile> pile);
	Player();
	Hand* get_hand();
	void remove_tile(Tile a_tile);
	void set_player_move(bool move);
	bool get_player_move();
private:
	bool player_move;
	int score;
	bool passed_last_move;
	Hand* a_hand;
	Hand* a_temp;
	Tile temp;
	int total;
};

#endif