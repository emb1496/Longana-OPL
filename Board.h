/************************************************************
* Name:  Elliott Barinberg                                  *
* Project : Project 1 - Longana								*
* Class : CMPS 366 OPL										*
* Date : 9/9/17												*
************************************************************/
#ifndef BOARD_H
#define BOARD_H
#include "Hand.h"
class Board : public Tile {

public:
	Board();
	Tile get_top();
	Tile get_center();
	std::stack<Tile> get_stack();
	std::stack<Tile> get_top_n(int n);
	bool add_to_left(Tile t);
	bool add_to_right(Tile t);
	std::vector<Tile> get_tiles();
	std::vector<Tile> get_right_side();
	std::vector<Tile> get_left_side();
	int get_leftmost();
	int get_rightmost();
	void set_center(int moves);
	std::vector<Tile> create_vector_to_print(int nummoves);
	void add_to_left(Tile t, int a);
	void add_to_right(Tile t, int a);
	void create_pile(Hand* p1_hand, Hand* p2_hand);
	void create_pile(std::stack<Tile> a_stack);
private:

	std::vector<Tile> printing_vec;

	//right end integer container
	int rend; 

	// left end integer container
	int lend; 

	Tile temp;

	// center for line
	Tile center;


	std::stack<Tile> temp1;

	// all tiles
	std::vector <Tile> tiles;

	// remaining tiles
	std::stack< Tile> pile;

	//left side not including center
	std::vector <Tile> left_side;

	//right side not including center
	std::vector <Tile> right_side;
};

#endif