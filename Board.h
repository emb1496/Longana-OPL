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
	// constructor and destructor
	Board();
	~Board();
	
	// return center
	inline Tile get_center() { return *center; }
	
	// return the boneyard
	inline stack<Tile> get_boneyard() { return pile; }

	// return all tiles
	inline vector<Tile> get_tiles() { return tiles; }

	// return the right side of the board
	inline vector<Tile> get_right_side() { return right_side; }

	// return the left side of the board
	inline vector<Tile> get_left_side() { return left_side; }

	/* inline overloaded add to left which skips the chekcs we make in the other add_to_left
	only used when reading from file, not by the user*/
	inline void add_to_left(const Tile t, const int a) { left_side.push_back(t); }

	/* inline overloaded add to right which skips the checks we make in the other add_to_right
	only used when reading from file, not by the user */
	inline void add_to_right(const Tile t, const int a) { right_side.push_back(t); }

	// get a n tiles from the boneyard and the pile will shrink accordingly
	stack<Tile> get_top_n(const int n);

	// add tile to left or right sides
	bool add_to_left(const Tile t);
	bool add_to_right(const Tile t);

	// get the left and right most values on the board
	int get_leftmost();
	int get_rightmost();

	// set the center tile
	void set_center(int moves);

	// create a vector with all the tiles in left to right order
	vector<Tile> create_vector_to_print(const int nummoves);
	
	// create the pile one way called from serialization one way called from a new game
	void create_pile(Hand* p1_hand, Hand* p2_hand);
	void create_pile(const stack<Tile> a_stack);
private:

	// left to right Tile vector container
	vector<Tile> printing_vec;

	// temp tile
	Tile* temp;

	// center for line
	Tile* center;

	// temp stack
	stack<Tile> temp1;

	// all tiles
	vector <Tile> tiles;

	// Boneyard
	stack< Tile> pile;

	//left side not including center
	vector <Tile> left_side;

	//right side not including center
	vector <Tile> right_side;
};

#endif