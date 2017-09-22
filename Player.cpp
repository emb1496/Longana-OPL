/************************************************************
* Name:  Elliott Barinberg                                  *
* Project : Project 1 - Longana								*
* Class : CMPS 366 OPL										*
* Date : 9/9/17												*
************************************************************/
#include "Player.h"

/* *********************************************************************
Function Name: Player
Purpose: Constructor for player
Parameters:
none
Return Value: Constructor
Local Variables:
score, the int player score,  passed_last_move, a boolean, and setting
the first item in the map to temp
Algorithm:
1) set score to 0
2) set passed_last_move to false
3) set a_hand first item to temp
Assistance Received: none
********************************************************************* */
Player::Player()
{
	score = 0;
	a_hand = new Hand;
	passed_last_move = false;
}

/************************************************************************
Function Name: get_hand
Purpose: To return the hand
Parameters: none
Return Value: players hand
Algorithm: 
1) Return hand
Assistance Received: none
**********************************************************************/
Hand* Player::get_hand() { return a_hand; }

/* *********************************************************************
Function Name: add_to_score
Purpose: To add to player score
Parameters:
num, an int to add onto it
Return Value: void
Local Variables:
score, the player score
Algorithm:
1) Add num to score
Assistance Received: none
********************************************************************* */
void Player::add_to_score(int num) { score += num; }

/* *********************************************************************
Function Name: get_hand_size
Purpose: to return the size of the hand
Parameters:
none
Return Value: the int size of the hand
Local Variables:
none
Algorithm:
1) Return the size of the hand
Assistance Received: none
********************************************************************* */
int Player::get_hand_size(Hand* the_hand) { return the_hand->size(*the_hand->get_hand()); }

/* *********************************************************************
Function Name: get_score
Purpose: To return the score
Parameters:
none
Return Value: The player score as an int
Local Variables:
score an int representing player score
Algorithm:
1) Return score
Assistance Received: none
********************************************************************* */
int Player::get_score() { return score; }

/* *********************************************************************
Function Name: set_passed
Purpose: To set passed_last_move
Parameters:
pass, the boolean to set passed_last_move to
Return Value: Void
Local Variables:
passed_last_move
Algorithm:
1) Set passed_last_move to pass
Assistance Received: none
********************************************************************* */
void Player::set_passed(bool pass) { passed_last_move = pass; }

/* *********************************************************************
Function Name: get_passed
Purpose: To return passed_last_move
Parameters:
none
Return Value: bool, passed_last_move
Local Variables:
none
Algorithm:
1) Return passed_last_move
Assistance Received: none
********************************************************************* */
bool Player::get_passed() { return passed_last_move; }

/* *********************************************************************
Function Name: fill_hand
Purpose: To call a_hand function fill hand
Parameters:
stack of tiles named pile
Return Value: void
Local Variables:
a_hand
Algorithm:
1) call the hand's fill hand and pass it the pile
Assistance Received: none
********************************************************************* */
void Player::fill_hand(stack<Tile> pile) { a_hand->fill_hand(pile); }

void Player::set_player_move(bool move) { player_move = move; }

bool Player::get_player_move() { return player_move; }

/* *********************************************************************
Function Name: has_tile
Purpose: To return whether a player has a tile
Parameters:
Tile named center
Return Value: boolean whether the player has the tile
Local Variables:
a_hand a hand
Algorithm:
1) loop through a_hand
2) check each tile in the hand if its the center
3) return whether the tile was there or not
Assistance Received: none
********************************************************************* */
bool Player::has_tile(Tile center) {
	for (int i = 0; i < a_hand->size(*a_hand->get_hand()); i++) {
		if (a_hand->at(i).get_side_left() == center.get_side_left() && a_hand->at(i).get_side_right() == center.get_side_right()) {
			return true;
		}
	}
	return false;
}

void Player::remove_tile(Tile a_tile) {
	a_temp = new Hand;
	while (a_hand->size(*a_hand->get_hand()) != 0) {
		a_temp->get_hand()->push_back(a_hand->get_hand()->back());
		a_hand->get_hand()->pop_back();
	}

	for (int i = 0; i < a_temp->size(*a_temp->get_hand()); i++) {
		if (a_temp->at(i).get_side_left() == a_tile.get_side_left() && a_temp->at(i).get_side_right() == a_tile.get_side_right()) {
			for (int j = i; j < a_temp->size(*a_temp->get_hand()) - 1; j++){
				a_hand->get_hand()->push_back(a_temp->at(j + 1));
			}
			break;
		}
		a_hand->get_hand()->push_back(a_temp->at(i));
	}
	
	a_temp->~Hand();
	delete a_temp;
}

int Player::make_a_num() {
	total = 0;
	for (int i = 0; i < get_hand_size(a_hand); i++) {
		total += a_hand->at(i).get_side_left() + a_hand->at(i).get_side_right();
	}
	return total;
}