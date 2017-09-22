/************************************************************
* Name:  Elliott Barinberg                                  *
* Project : Project 1 - Longana								*
* Class : CMPS 366 OPL										*
* Date : 9/9/17												*
************************************************************/
#include "Hand.h"

Hand::Hand() {
	while (!thehand.empty()) {
		thehand.pop_back();
	}
}

/* *********************************************************************
Function Name: compute
Purpose: To calculate the average grade in a class
Parameters:
grades[], an array passed by value. It holds individual grades
size, an integer. It refers to the number of students in the class
Return Value: The average grade in the class, a real value
Local Variables:
temp[], an integer array used to sort the grades
Algorithm:
1) Add all the grades
2) Divide the sum by the number of students in class to calculate the average
Assistance Received: none
********************************************************************* */
void Hand::fill_hand(std::stack <Tile> pile) {
	int n = pile.size();
	for (int i = 0; i < n; i++) {
		thehand.push_back(pile.top());
		pile.pop();
	}
}

bool Hand::has_tile(Tile a_tile) {
	for (int i = 0; i < thehand.size(); i++) {
		if (thehand.at(i).get_side_left() == a_tile.get_side_left() && thehand.at(i).get_side_right() == a_tile.get_side_right()) {
			return true;
		}
	}
	return false;
}

std::vector<Tile>* Hand::get_hand() { return &thehand; }
/* *********************************************************************
Function Name: compute
Purpose: To calculate the average grade in a class
Parameters:
grades[], an array passed by value. It holds individual grades
size, an integer. It refers to the number of students in the class
Return Value: The average grade in the class, a real value
Local Variables:
temp[], an integer array used to sort the grades
Algorithm:
1) Add all the grades
2) Divide the sum by the number of students in class to calculate the average
Assistance Received: none
********************************************************************* */
Tile Hand::at(int a) { return thehand[a]; }

/* *********************************************************************
Function Name: compute
Purpose: To calculate the average grade in a class
Parameters:
grades[], an array passed by value. It holds individual grades
size, an integer. It refers to the number of students in the class
Return Value: The average grade in the class, a real value
Local Variables:
temp[], an integer array used to sort the grades
Algorithm:
1) Add all the grades
2) Divide the sum by the number of students in class to calculate the average
Assistance Received: none
********************************************************************* */
int Hand::size(vector<Tile> thishand) { return thishand.size(); }

int Hand::size() {
	return thehand.size();
}

/* *********************************************************************
Function Name: compute
Purpose: To calculate the average grade in a class
Parameters:
grades[], an array passed by value. It holds individual grades
size, an integer. It refers to the number of students in the class
Return Value: The average grade in the class, a real value
Local Variables:
temp[], an integer array used to sort the grades
Algorithm:
1) Add all the grades
2) Divide the sum by the number of students in class to calculate the average
Assistance Received: none
********************************************************************* */
Hand::~Hand()
{
	while (!thehand.empty()) {
		thehand.pop_back();
	}
}