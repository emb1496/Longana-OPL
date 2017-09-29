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
	// set private variables to default values
	player_move = false;
	score = 0;
	a_hand = new Hand;
	a_temp = new Hand;
	total = 0;
}

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

/* *********************************************************************
Function Name: remove_tile
Purpose: to remove a tile from the players hand
Parameters:
Tile named a_tile
Return Value: none
Local Variables:
a_temp and a_hand which are both hands
Algorithm:
1.	loop thorugh the hand until we get to the tile
2.	then push in the next one tiles until we have a full hand without
	the original Tile
Assistance Received: none
********************************************************************* */
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
	while (!a_temp->get_hand()->empty()) { a_temp->get_hand()->pop_back(); }
	while (a_hand->get_hand()->size() != 0) {
		a_temp->get_hand()->push_back(a_hand->get_hand()->back());
		a_hand->get_hand()->pop_back();
	}
	for (int i = 0; i < a_temp->get_hand()->size(); i++) {
		a_hand->get_hand()->push_back(a_temp->at(i));
	}
	while (!a_temp->get_hand()->empty()) { a_temp->get_hand()->pop_back(); }
	a_temp->~Hand();
	delete a_temp;
}

/* *********************************************************************
Function Name: make_a_num
Purpose: to add the total pips in the players hand
Parameters:
none
Return Value: int
Local Variables:
total, an int
and a_hand a hand
Algorithm:
1.	loop thorugh the hand totalling up the pips
2.	return the total
Assistance Received: none
********************************************************************* */
int Player::make_a_num() {
	total = 0;
	for (int i = 0; i < get_hand_size(a_hand); i++) {
		total += a_hand->at(i).get_side_left() + a_hand->at(i).get_side_right();
	}
	return total;
}

/* *********************************************************************
Function Name: ~Player
Purpose: destructor for the Player class
Parameters:
none
Return Value: none
Local Variables:
a_temp and a_hand which are both hands
Algorithm:
call the hand destructor for both variables and delete them both
Assistance Received: none
********************************************************************* */
Player::~Player() {
	a_hand->~Hand();
	a_temp->~Hand();
	delete a_hand;
	delete a_temp;
}