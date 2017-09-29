/************************************************************
* Name:  Elliott Barinberg                                  *
* Project : Project 1 - Longana								*
* Class : CMPS 366 OPL										*
* Date : 9/20/17											*
************************************************************/
#ifndef SERIALIZATION_H
#define SERIALIZATION_H
#include "stdafx.h"
#include "Tournament.h"
using namespace std;
class Serialization
{
private:
	static string filename;
	static string a_string;
	static ofstream out_file;
	ifstream in_file;
	static stringstream a_stream;
	stack<Tile> a_pile;
	vector<Tile> a_vec;
	queue<Tile> left_side;
	stack<Tile> right_side;
	static Tile temp;
	Tile* temp1;
	char a_char;
	bool last_player_passed;
	string my_string;
	bool one_too_far;
public:
	// constructors
	Serialization(Human* p1, Computer* computer, Board* the_board, Round* a_round, int &nummoves, int &score, Tournament* game);
	Serialization();

	// print state to file
	static void print_to_file(int score, int nummoves, Computer* computer, Hand* p1_hand, Board* a_board, int human_score, bool human_move, bool human_passed);
	
	// load state from file
	void read_from_file(Human* p1, Computer* computer, Board* the_board, int &nummoves, int &score);
	
	// print hand to file
	static void print_just_hand(Hand* a_hand);

	// print board to file
	static void print_just_board(vector<Tile> a_vec);

	// print pile to file
	static void print_just_boneyard(stack<Tile> pile);

	// read the score in from the file
	void read_score(int &score);

	// read the round number from the file
	void read_nummoves(int &nummoves);

	// read a player hand from file
	void read_player_hand(Player* p1);

	// read the layout of the board from the file
	void read_layout(Board* a_board);

	// read the boneyard from the file
	void read_boneyard(Board* a_board);

	// read whether last player passed
	void read_last_passed();

	// read who plays next
	char read_next_play(Human* p1, Computer* p2, Board* the_board);

	// get filename
	string get_file_name();

	// parse file into stringstream
	void parse_file();

	// destructor
	inline ~Serialization() { delete temp1; }
};
#endif