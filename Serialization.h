#ifndef SERIALIZATION_H
#define SERIALIZATION_H
#include "stdafx.h"
#include "Tournament.h"
using namespace std;
class Serialization
{
private:
	Player* a_player;
	static std::string filename;
	static std::string a_string;
	static std::ofstream out_file;
	std::ifstream in_file;
	static std::stringstream a_stream;
	std::stack<Tile> a_pile;
	std::vector<Tile> a_vec;
	std::queue<Tile> left_side;
	std::stack<Tile> right_side;
	static Tile temp;
	Tile* temp1;
	char a_char;
	bool last_player_passed;
	string my_string;
	bool one_too_far;
public:
	Serialization();
	Serialization(Human* p1, Computer* computer, Board* the_board, Round* a_round, int &nummoves, int &score, Tournament* game);
	static void print_to_file(int score, int nummoves, Computer* computer, Hand* p1_hand, Board* a_board, int human_score, bool human_move, bool human_passed);
	static void print_to_file(int score, int nummoves, Hand* computer_hand, Human* p1, Board* a_board, int comp_score, bool comp_move, bool comp_passed);
	void read_from_file(Human* p1, Computer* computer, Board* the_board, int &nummoves, int &score);
	static void print_just_hand(Hand* a_hand);
	static void print_just_board(std::vector<Tile> a_vec);
	static void print_just_boneyard(stack<Tile> pile);
	static bool want_to_save(char m_char);
	void read_score(int &score);
	void read_nummoves(int &nummoves);
	void read_player_hand(Player* p1);
	void read_layout(Board* a_board);
	void read_boneyard(Board* a_board);
	void read_last_passed();
	Player* read_next_play(Human* p1, Computer* p2, Board* the_board);
};
#endif