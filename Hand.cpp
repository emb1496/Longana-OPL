/************************************************************
* Name:  Elliott Barinberg                                  *
* Project : Project 1 - Longana								*
* Class : CMPS 366 OPL										*
* Date : 9/9/17												*
************************************************************/
#include "Hand.h"

/* *********************************************************************
Function Name: Hand
Purpose: Hand constructor
Parameters:
none
Return Value: none
Local Variables:
thehand a vector of Tiles
Algorithm:
1.	Empty the hand
Assistance Received: none
********************************************************************* */
Hand::Hand() {
	while (!thehand.empty()) {
		thehand.pop_back();
	}
}

/* *********************************************************************
Function Name: fill_hand
Purpose: to fill the hand
Parameters:
stack of Tiles called pile to feed into the hand
Return Value: none
Local Variables:
thehand
Algorithm:
1.	loop through the pile and push each tile into thehand
Assistance Received: none
********************************************************************* */
void Hand::fill_hand(stack <Tile> pile) {
	while (!pile.empty()) {
		thehand.push_back(pile.top());
		pile.pop();
	}
}

/* *********************************************************************
Function Name: has_tile
Purpose: to check if the hand has a tile
Parameters:
Tile a_tile
Return Value: bool
Local Variables:
thehand
Algorithm:
1.	loop through the hand and compare each tile to the Tile passed in
	if they are equal return true, otherwise return false
Assistance Received: none
********************************************************************* */
bool Hand::has_tile(Tile a_tile) {
	for (int i = 0; i < thehand.size(); i++) {
		if (thehand.at(i).get_side_left() == a_tile.get_side_left() && thehand.at(i).get_side_right() == a_tile.get_side_right()) {
			return true;
		}
	}
	return false;
}

/* *********************************************************************
Function Name: ~Hand
Purpose: Destructor for hand
Parameters:
none
Return Value: none
Local Variables:
thehand
Algorithm:
1.	Empty thehand
Assistance Received: none
********************************************************************* */
Hand::~Hand()
{
	while (!thehand.empty()) {
		thehand.pop_back();
	}
}