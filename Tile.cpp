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
1) set side1 to a 
2) set side2 to b
Assistance Received: none
********************************************************************* */
Tile::Tile(int a, int b) {
	left_side = a;
	right_side = b;
}

/* *********************************************************************
Function Name: set_side1
Purpose: To set side 1
Parameters:
num - the number to set the side to
Return Value: void
Local Variables:
side1 - the integer on side 1
Algorithm:
1) set side1 to num
Assistance Received: none
********************************************************************* */
inline void Tile::set_side_left(int num) { left_side = num; }

/* *********************************************************************
Function Name: get_side1
Purpose: To return the value of side1
Parameters:
None
Return Value: integer value of side 1
Local Variables:
none
Algorithm:
1) Return side1
Assistance Received: none
********************************************************************* */
int Tile::get_side_left() {	return left_side; }

/* *********************************************************************
Function Name: set_side2
Purpose: To set the value of side2
Parameters:
num - the number to set side2 to
Return Value: void
Local Variables:
side2 - the value of side 2
Algorithm:
1) set side2 to num
Assistance Received: none
********************************************************************* */
inline void Tile::set_side_right(int num) { right_side = num; }

/* *********************************************************************
Function Name: get_side2
Purpose: To return the number in side 2
Parameters:
None
Return Value: side2
Local Variables:
None
Algorithm:
1) Return side2
Assistance Received: none
********************************************************************* */
int Tile::get_side_right() { return right_side; }

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

void Tile::print() { std::cout << "(" << left_side << " - " << right_side << ")"; }

bool Tile::isDouble() {
	if (get_side_left() == get_side_right()) {
		return true;
	}
	return false;
}