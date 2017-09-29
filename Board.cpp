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
	temp = new Tile;
	center = new Tile;
	// create all the tiles and push them into "tiles"
	for (int i = 0; i <= 6; i++) {
		for (int j = 6; j >= i; j--) {
			*temp = Tile(i, j);
			tiles.push_back(*temp);
		}
	}

	// seed the random number generator and shuffle the vector using random shuffle
	srand(unsigned(time(0)));
	random_shuffle(tiles.begin(), tiles.end());

	// push the tiles into the stack representing the boneyard
	for (int i = 0; i < 28; i++) {
		pile.push(tiles.at(i));
	}
}

/* *********************************************************************
Function Name: create_vector_to_print
Purpose: To create a crector of Tiles that can then be parsed by
the BoardView function print_board
Parameters:
nummoves, integer representing the number of rounds that have been
played
Return Value: vector of Tiles
Local Variables:
Tile* center
Algorithm:
1.	Empty printing_vec
2.	Set the board center using nummoves
3.	go through the left_side of the board starting at the end of the
	vector and going to the beginning and each tile into printing_vec
	without making any changes to left_side
4.	Push the center of the board into printing_vec
5.	Starting at the first tile of right side push each tile into 
	printing_vec
6.	Return printing_vec
Assistance Received: none
********************************************************************* */
vector<Tile> Board::create_vector_to_print(int nummoves) {
	while (!printing_vec.empty()) { printing_vec.pop_back(); }
	center->set_engine(nummoves);
	for (int i = 1; i <= left_side.size(); i++) {
		printing_vec.push_back(left_side.at(left_side.size() - i));
	}
	printing_vec.push_back(*center);
	for (int i = 0; i < right_side.size(); i++) {
		printing_vec.push_back(right_side[i]);
	}
	return printing_vec;
}

/* *********************************************************************
Function Name: create_pile
Purpose: create the pile aka deck aka boneyard
Parameters:
Hand* p1_hand & Hand* p2_hand, pointers to the two player hands
Return Value: none
Local Variables:
none
Algorithm:
set private member variables to default values
Assistance Received: none
********************************************************************* */
void Board::create_pile(Hand* p1_hand, Hand* p2_hand) {
	for (int i = 0; i < get_tiles().size(); i++) {
		if (!(p1_hand->has_tile(get_tiles().at(i)) || p2_hand->has_tile(get_tiles().at(i)))) {
			pile.push(get_tiles().at(i));
		}
	}
}

/* *********************************************************************
Function Name: create_pile
Purpose: Create a pile given a stack, called when loading from text file
Parameters:
stack of Tiles a_stack
Return Value: none
Local Variables:
Pile, the stack of Tiles representing the boneyard
Algorithm:
1.	Empty Pile
2.	Push the top Tile in a_stack to the bottom of Pile and pop a_stack
	until a_stack is empty
Assistance Received: none
********************************************************************* */
void Board::create_pile(stack<Tile> a_stack) {
	while (pile.empty() == false) {
		pile.pop();
	}
	while (a_stack.empty() == false){
		pile.push(a_stack.top());
		a_stack.pop();
	}
}

/* *********************************************************************
Function Name: get_top_n
Purpose: To get any number of tiles from the boneyard
Parameters:
int n, number of tiles to return
Return Value: stack of Tiles
Local Variables:
temp1 a stack of tiles which will be returned and pile a stack of Tiles
which is the boneyard
Algorithm:
1.	Make sure temp1 is empty
2.	Check that n is not out of bounds and if it is return the empty temp1
3.	Loop through n time, each loop push the top tile from pile into temp1
	and pop the original pile
4.	Return temp1
Assistance Received: none
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
Function Name: get_leftmost
Purpose: return leftmost integer value
Parameters:
none
Return Value: int, the leftmost integer on the board
Local Variables:
center, a Tile pointing to the center
left_side vector of tiles representing the left side of the board not
	not including the center
Algorithm:
1.	If left_side is empty then return either of the integers in center
2.	Otherwise return the left side of the last tile in left_side
Assistance Received: none
********************************************************************* */
int Board::get_leftmost() {
	if (left_side.empty()) {
		return center->get_side_left();
	}
	else {
		return left_side.back().get_side_left();
	}
}

/* *********************************************************************
Function Name: get_rightmost
Purpose: return rightmost integer value
Parameters:
none
Return Value: int, the rightmost integer on the board
Local Variables:
center, a Tile pointing to the center
right_side vector of tiles representing the right side of the board not
not including the center
Algorithm:
1.	If right_side is empty then return either of the integers in center
2.	Otherwise return the right side of the last tile in right_side
Assistance Received: none
********************************************************************* */
int Board::get_rightmost() {
	if (right_side.empty()) {
		return center->get_side_right();
	}
	else {
		return right_side.back().get_side_right();
	}
}

/* *********************************************************************
Function Name: add_to_left
Purpose: add a tile to the left side of the board
Parameters:
Tile t, the tile to add
Return Value: bool, whether is was successful
Local Variables:
left_side vector of tiles representing the left side of the board not
not including the center
Algorithm:
1.	Check if either side of the tile equals the left most number
	on the board (if not we will return false because we cannot
	place a tile)
2.	Check if the tile sides line up with the board, if they do then 
	we are okay to push the tile and return true
3.	Otherwise turn the tile around push it into left_side and return
	true
Assistance Received: none
********************************************************************* */
bool Board::add_to_left(Tile t) { 
	if (t.get_side_left() == get_leftmost() || t.get_side_right() == get_leftmost()) {
		if (t.get_side_right() == get_leftmost()) {
			left_side.push_back(t);
		}
		else {
			temp->set_side_left(t.get_side_right());
			temp->set_side_right(t.get_side_left());
			t = *temp;
			left_side.push_back(t);
		}

		return true;
	}
	return false;
}

/* *********************************************************************
Function Name: add_to_right
Purpose: add a tile to the right side of the board
Parameters:
Tile t, the tile to add
Return Value: bool, whether is was successful
Local Variables:
right_side vector of tiles representing the right side of the board not
not including the center
Algorithm:
1.	Check if either side of the tile equals the right most number
on the board (if not we will return false because we cannot
place a tile)
2.	Check if the tile sides line up with the board, if they do then
we are okay to push the tile and return true
3.	Otherwise turn the tile around push it into right_side and return
true
Assistance Received: none
********************************************************************* */
bool Board::add_to_right(Tile t) { 
	if (t.get_side_left() == get_rightmost() || t.get_side_right() == get_rightmost()) {
		if (t.get_side_left() == get_rightmost()) {
			right_side.push_back(t);
		}
		else {
			temp->set_side_left(t.get_side_right());
			temp->set_side_right(t.get_side_left());
			t = *temp;
			right_side.push_back(t);
		}
		return true;
	}
	return false;
}

/* *********************************************************************
Function Name: set_center
Purpose: set the center tile to the engine for the round using nummoves
Parameters:
int num, represents which number round it is
Return Value: none
Local Variables:
center Tile representing the center
Algorithm:
1.	Modulate num by 7
2.	Make num equal itself substracted from 6
3.	Set the center Tile to have both sides be the new value of num
Assistance Received: none
********************************************************************* */
void Board::set_center(int num) {
	// calculate what the center would be if num was the round number and store it in center using overloaded Tile constructor
	num %= 7;
	num = 6 - num;
	*center = Tile(num, num);
}

/* *********************************************************************
Function Name: ~Board
Purpose: Board destructor
Parameters:
none
Return Value: none
Local Variables:
center & temp Tiles
Algorithm:
1. delete center and temp
Assistance Received: none
********************************************************************* */
Board::~Board() {
	delete center;
	delete temp;
}