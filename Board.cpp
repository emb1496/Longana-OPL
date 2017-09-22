/************************************************************
* Name:  Elliott Barinberg                                  *
* Project : Project 1 - Longana								*
* Class : CMPS 366 OPL										*
* Date : 9/9/17												*
************************************************************/
#include "board.h"
using namespace std;

/* *********************************************************************
Name: Board

Return Type: Constructor

Input: None

Local variables used:
	int count 
********************************************************************* */
Board::Board()
{
	for (int i = 0; i <= 6; i++) {
		for (int j = 6; j >= i; j--) {
			temp = Tile(i, j);
			tiles.push_back(temp);
		}
	}

	srand(unsigned(time(0)));
	random_shuffle(tiles.begin(), tiles.end());

	for (int i = 0; i < 28; i++) {
		pile.push(tiles.at(i));
	}
}

vector<Tile> Board::create_vector_to_print(int nummoves) {
	while (!printing_vec.empty()) { printing_vec.pop_back(); }
	center.set_engine(nummoves);
	for (int i = 1; i <= left_side.size(); i++) {
		printing_vec.push_back(left_side.at(left_side.size() - i));
	}
	printing_vec.push_back(center);
	for (int i = 0; i < right_side.size(); i++) {
		printing_vec.push_back(right_side[i]);
	}
	return printing_vec;
}

void Board::create_pile(Hand* p1_hand, Hand* p2_hand) {
	for (int i = 0; i < get_tiles().size(); i++) {
		if (!(p1_hand->has_tile(get_tiles().at(i)) || p2_hand->has_tile(get_tiles().at(i)))) {
			pile.push(get_tiles().at(i));
		}
	}
}

void Board::create_pile(std::stack<Tile> a_q) {
	while (pile.empty() == false) {
		pile.pop();
	}
	while (a_q.empty() == false){
		pile.push(a_q.top());
		a_q.pop();
	}
}

/* *********************************************************************

********************************************************************* */
stack<Tile> Board::get_stack() { return pile; }

/* *********************************************************************

********************************************************************* */
stack<Tile> Board::get_top_n(int n) {
	while (!temp1.empty()) {
		temp1.pop();
	}
	if (n > pile.size()) {
		return temp1;
	}
	for (int i = 0; i < n; i++) {
		temp1.push(pile.top());
		pile.pop();
	}
	return temp1;
}

/* *********************************************************************
Function Name: get_center
Purpose: To return center tile
Parameters:
none
Return Value: center tile
Local Variables:
center
Algorithm:
1) return center
Assistance Received: none
********************************************************************* */
Tile Board::get_center() { return center;}

int Board::get_leftmost() {
	if (left_side.empty()) {
		return center.get_side_left();
	}
	else {
		return left_side.back().get_side_left();
	}
}

int Board::get_rightmost() {
	if (right_side.empty()) {
		return center.get_side_right();
	}
	else {
		return right_side.back().get_side_right();
	}
}

/* *********************************************************************

********************************************************************* */
Tile Board::get_top() {
	temp = pile.top();
	pile.pop();
	return temp;
}

/* *********************************************************************


********************************************************************* */
bool Board::add_to_left(Tile t) { 
	if (t.get_side_left() == get_leftmost() || t.get_side_right() == get_leftmost()) {
		if (t.get_side_right() == get_leftmost()) {
			left_side.push_back(t);
		}
		else {
			temp.set_side_left(t.get_side_right());
			temp.set_side_right(t.get_side_left());
			t = temp;
			left_side.push_back(t);
		}

		return true;
	}
	return false;
}

/* *********************************************************************

********************************************************************* */
bool Board::add_to_right(Tile t) { 
	if (t.get_side_left() == get_rightmost() || t.get_side_right() == get_rightmost()) {
		if (t.get_side_left() == get_rightmost()) {
			right_side.push_back(t);
		}
		else {
			temp.set_side_left(t.get_side_right());
			temp.set_side_right(t.get_side_left());
			t = temp;
			right_side.push_back(t);
		}
		return true;
	}
	return false;
}

void Board::add_to_left(Tile t, int a) {
	left_side.push_back(t);
}

void Board::add_to_right(Tile t, int a) {
	right_side.push_back(t);
}

/* *********************************************************************

********************************************************************* */
vector<Tile> Board::get_tiles() { return tiles; }

/* *********************************************************************

********************************************************************* */
vector<Tile> Board::get_left_side() { return left_side; }

/* *********************************************************************

********************************************************************* */
vector<Tile> Board::get_right_side() { return right_side; }

/* *********************************************************************

********************************************************************* */
void Board::set_center(int num) {
	num %= 7;
	num = 6 - num;
	center = Tile(num, num);
}