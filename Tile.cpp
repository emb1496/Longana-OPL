/************************************************************
* Name:  Elliott Barinberg                                  *
* Project : Project 1 - Longana								*
* Class : CMPS 366 OPL										*
* Date : 9/9/17												*
************************************************************/
#include "Tile.h"

/* *********************************************************************
Function Name: Tile constructor
Purpose: make a blank tile
Parameters:
none
Return Value: Constructor
Local Variables:
side1 and side2 both ints representing the sides of the tiles
Algorithm:
1) Set both sides of the tile out of range
Assistance Received: none
********************************************************************* */
Tile::Tile()
{
	left_side = 7;
	right_side = 7;
}

/* *********************************************************************
Function Name: Tile constructor overloaded
Purpose: To create a tile with both sides already set to values
Parameters:
a - value for side 1, b - value for side 2, both are integers
Return Value: constructor
Local Variables:
side1 and side2 - integer values of the tile
Algorithm:
1) set left_side to a 
2) set right_side to b
Assistance Received: none
********************************************************************* */
Tile::Tile(int a, int b) {
	// set left and right sides of tile
	left_side = a;
	right_side = b;
}

/* *********************************************************************
Function Name: set_engine
Purpose: To modify a tile into the engine for the round
Parameters:
nummoves an integer value of the number of moves that have been made
Return Value: void
Local Variables:
none
Algorithm:
1) add 6 to the number of moves
2) modulate answer from step 1
3) set both sides of the tile to the answer from step 2
Assistance Received: none
********************************************************************* */
void Tile::set_engine(int nummoves) {
	
	nummoves %= 7;
	nummoves = 6 - nummoves;
	set_side_left(nummoves);
	set_side_right(nummoves);
}

/* *********************************************************************
Function Name: isDouble
Purpose: to check if a tile is double
Parameters:
none
Return Value: bool
Local Variables:
none
Algorithm:
1.	Check if both sides are equal
	If they are then return true
	Otherwise return false
Assistance Received: none
********************************************************************* */
bool Tile::isDouble() {
	if (get_side_left() == get_side_right()) {
		return true;
	}
	return false;
}

/* *********************************************************************
Function Name: ~Tile
Purpose: Tile destructor
Parameters:
none
Return Value: none
Local Variables:
none
Algorithm:
1.	None
Assistance Received: none
********************************************************************* */
Tile::~Tile() {

}