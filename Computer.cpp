/************************************************************
* Name:  Elliott Barinberg                                  *
* Project : Project 1 - Longana								*
* Class : CMPS 366 OPL										*
* Date : 9/9/17												*
************************************************************/
#include "Computer.h"

/* *********************************************************************
Function Name: Computer
Purpose: Constructor for the Computer class
Parameters:
none
Return Value: none
Local Variables:
best_play_order a vector of Tiles to score the player's best plays
has_legal_move a boolean representing whether a player has a move
num an int to map to a tile
let is a char to map to the side of the board
Algorithm:
1.	Make sure best_play_order is empty
2.	set has_legal_move to false
3.	set num to 0
4.	set let to null character
Assistance Received: none
********************************************************************* */
Computer::Computer() {
	// give values to private member variables
	while (!best_play_order.empty()) {
		best_play_order.pop_back();
	}
	has_legal_move = false;
	num = 0;
	let = '\0';
}

/* *********************************************************************
Function Name: best_tiles_to_play
Purpose: to return a sorted vector of the Tiles in strategic order
Parameters:
Hand* a_hand, a pointer to a Hand to sort
Return Value: a vector of Tiles
Local Variables:
right_tiles a vector of int
left_side a vector of int
a_vec_to_return a vector of Tiles
Algorithm:
1.	Make sure all the vectors are empty
2.	push back left tiles with 0's
3.	Loop through hand and weight each tile 
4.	Reorder the vectors based on the weights
5.	Return the vector
Assistance Received: none
********************************************************************* */
vector<Tile> Computer::best_tiles_to_play(Hand* a_hand) {
	vector<Tile> a_vec_to_return;
	vector<int> left_tiles;
	vector<int> right_tiles;
	while (!right_tiles.empty()) {
		right_tiles.pop_back();
	}
	while (!left_tiles.empty()) {
		left_tiles.pop_back();
	}
	while (!a_vec_to_return.empty()) {
		a_vec_to_return.pop_back();
	}
	for (int i = 0; i < 7; i++) {
		left_tiles.push_back(0);
	}
	for (int i = 0; i < a_hand->size(); i++) {
		a_vec_to_return.push_back(a_hand->get_hand()->at(i));
		switch (a_vec_to_return[i].get_side_right()) {
		case 0: 
			left_tiles[0]++;
			break;
		case 1:
			left_tiles[1]++;
			break;
		case 2:
			left_tiles[2]++;
			break;
		case 3:
			left_tiles[3]++;
			break;
		case 4:
			left_tiles[4]++;
			break;
		case 5:
			left_tiles[5]++;
			break;
		case 6:
			left_tiles[6]++;
			break;
		}
		switch (a_vec_to_return[i].get_side_left()) {
		case 0:
			left_tiles[0]++;
			break;
		case 1:
			left_tiles[1]++;
			break;
		case 2:
			left_tiles[2]++;
			break;
		case 3:
			left_tiles[3]++;
			break;
		case 4:
			left_tiles[4]++;
			break;
		case 5:
			left_tiles[5]++;
			break;
		case 6:
			left_tiles[6]++;
			break;
		}
	}

	// order based on left side weight
	for (int i = 0; i < a_hand->size(); i++) {
		right_tiles.push_back(left_tiles[a_vec_to_return[i].get_side_left()] + left_tiles[a_vec_to_return[i].get_side_right()]);
	}

	// order then based on right side weight to largest number in right side is left most and order a_vec_to_return the same way
	for (int i = 0; i < a_hand->size()-1; i++) {
		for (int j = 0; j < a_hand->size() - i - 1; i++) {
			if (right_tiles[j] < right_tiles[j + 1]) {
				swap(right_tiles.at(j), right_tiles.at(j + 1));
				swap(a_vec_to_return[j], a_vec_to_return[j + 1]);
			}
		}
	}
	
	return a_vec_to_return;
}

/* *********************************************************************
Function Name: play_tile
Purpose: to try to play a tile
Parameters:
Tile* play_tile, a tile pointer to try to play
int left_end the leftmost number
int right_end the rightmost number
Board* a_board, a board pointer to play on
bool last_played whether the last player played
Return Value: bool whether the tile was played or not
Local Variables:
none
Algorithm:
1.	Check if the tile can be played
2.	If it can print out where the tile is being added
3.	add it to the side of the board
4.	remove the tile
5.	return whether the function was successful or not
Assistance Received: none
********************************************************************* */
bool Computer::play_tile(Tile* play_tile, int left_end, int right_end, Board* a_board, bool last_played) {
	if (play_tile->get_side_left() == play_tile->get_side_right()) {
		if (play_tile->get_side_left() == left_end) {
			cout << "\nComputer moves tile ";	play_tile->print();	cout << " to the left side" << '\n';
			cout << "\nThe computer chose this move because this was the best tile he could legally play" << '\n';
			a_board->add_to_left(*play_tile);
			Player::remove_tile(*play_tile);
			return true;
		}
	}
	else if (!last_played && ((play_tile->get_side_left() == left_end) || (play_tile->get_side_right()==left_end))) {
		Player::remove_tile(*play_tile);
		a_board->add_to_left(*play_tile);
		cout << "\nComputer moves tile "; play_tile->print(); cout << " to the left side" << '\n';
		cout << "\nThe computer chose this move because this was the best tile he could legally play" << '\n';
		return true;
	}
	else if (play_tile->get_side_right() == right_end || play_tile->get_side_left() == right_end) {
		Player::remove_tile(*play_tile);
		a_board->add_to_right(*play_tile);
		cout << "\nComputer moves tile ";	play_tile->print();	cout << " to the right side" << '\n';
		cout << "\nThe computer chose this move because this was the best tile he could legally play" << '\n';
		return true;
	}
	if (play_tile->get_side_left() == play_tile->get_side_right()) {
		if (play_tile->get_side_left() == right_end) {
			cout << "\nComputer moves tile ";	play_tile->print();	cout << "to the right side" << '\n';
			cout << "\nThe computer chose this move because this was the best tile he could legally play" << '\n';
			a_board->add_to_right(*play_tile);
			Player::remove_tile(*play_tile);
			return true;
		}
	}
	return false;
}

/* *********************************************************************
Function Name: has_a_legal_move
Purpose: To see if the player has a legal move
Parameters:
bool last_player_passed whether the last player passed
int left_end the integer representing left most pip
int right_end the integer representing right most pip
Hand* a_hand a pointer the the hand the player is playing
bool is_human whether the player is a human or not
Return Value: bool
Local Variables:
none
Algorithm:
1.	loop through the hand and check if the player has a move
	if they do return true, if you reach the end of the hand return 
	false
Assistance Received: none
********************************************************************* */
bool Computer::has_a_legal_move(bool last_player_passed, int left_end, int right_end, Hand* a_hand, bool is_human) {
	for (int i = 0; i < a_hand->size(); i++) {
		if (!last_player_passed) {
			if (left_end == a_hand->at(i).get_side_left() || left_end == a_hand->at(i).get_side_right() || right_end == a_hand->at(i).get_side_left() || right_end == a_hand->at(i).get_side_right()) {
				return true;
			}
		}
		if (a_hand->at(i).get_side_left() == a_hand->at(i).get_side_right()) {
			// tile same number both sides
			if (left_end == a_hand->at(i).get_side_left() || right_end == a_hand->at(i).get_side_left()) {
				return true;
			}
		}
		if (is_human) {
			if (a_hand->at(i).get_side_left() == left_end || a_hand->at(i).get_side_right() == left_end) {
				return true;
			}
		}
		else {
			if (right_end == a_hand->at(i).get_side_left() || right_end == a_hand->at(i).get_side_right()) {
				return true;
			}

		}
	}
	return false;
}

/* *********************************************************************
Function Name: play
Purpose: the computer play function
Parameters:
int boneyard_size, left_end, right_end, size of pile, left and right
	most numbers, respectively
Return Value: none
Local Variables:
	bool repeat, loop control
	int num, map to which tile
	char let, left or right char
	bool has_legal_move, can the computer play
	vector<Tile> best_play_order, his best tiles to play
Algorithm:
1.	Reset all local variable values
2.	using legal moves and best play order computer makes the optimal 
	move and then releases its turn, computer will make only legal moves
	and outputs each move it make
Assistance Received: none
********************************************************************* */
void Computer::play(int boneyard_size, int left_end, int right_end, Board* a_board, bool last_moved) {
	if (get_player_move() == false) {
		return;
	}
	repeat = false;
	num = 1;
	let = 'a';
	do {
		has_legal_move = has_a_legal_move(last_moved, left_end, right_end, get_hand(), is_human());
		if (has_legal_move) {
			repeat = false;
			set_passed(false);
			while (!best_play_order.empty()) {
				best_play_order.pop_back();
			}
			// gets list of tiles with best ones to move at 0 and worst at the end
			best_play_order = best_tiles_to_play(Computer::get_hand());
			for (int i = 0; i < best_play_order.size(); i++) {
				if (play_tile(&best_play_order[i], left_end, right_end, a_board, last_moved)) {
					break;
				}
			}
		}
		else {
			if (boneyard_size > 0) {
				cout << "\nNo legal moves, computer must draw a tile\n" << endl;
				Player::fill_hand(a_board->get_top_n(1));
				set_passed(true);
				has_legal_move = has_a_legal_move(last_moved, left_end, right_end, Player::get_hand(), Computer::is_human());
				if (has_legal_move) {
					repeat = true;
				}
				else {
					cout << "\nAfter drawing you computer still has no moves, human will play\n";
				}
			}
			else {
				cout << "\nNo legal moves, stock is empty, human's turn to play\n" << endl;
				set_passed(true);
				repeat = false;
			}
		}
	} while (repeat == true);
	Player::set_player_move(false);
}

/* *********************************************************************
Function Name: ~Computer
Purpose: Destructor for Computer
Parameters:
none
Return Value: none
Local Variables:
vector<Tile> best_play_order, his best tiles to play
Algorithm:
1.	Reset all local variable values
Assistance Received: none
********************************************************************* */
Computer::~Computer() {
	while (!best_play_order.empty()) {
		best_play_order.pop_back();
	}
}