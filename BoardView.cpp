/************************************************************
* Name:  Elliott Barinberg                                  *
* Project : Project 1 - Longana								*
* Class : CMPS 366 OPL										*
* Date : 9/9/17												*
************************************************************/
#include "BoardView.h"
std::queue<char> line1;
std::vector<char> line2;
std::queue<char> line3;
BoardView::BoardView() {

}

/* *********************************************************************

********************************************************************* */
void BoardView::print_board(std::vector<Tile> a_vec) {
	cout << "\n";
	while (!line1.empty()) { line1.pop(); }
	while (!line2.empty()) { line2.pop_back(); }
	while (!line3.empty()) { line3.pop(); }
	line2.push_back('L');
	for (int i = 0; i < a_vec.size(); i++) {
		if (a_vec.at(i).get_side_left() == a_vec.at(i).get_side_right()) {
			line2.push_back(' ');
			line2.push_back('|');
			line1.push(char(a_vec.at(i).get_side_left()) + 48);
			line3.push(char(a_vec.at(i).get_side_left()) + 48);
		}
		else {
			line2.push_back(' ');
			line2.push_back(char((a_vec.at(i).get_side_left())) + 48);
			line2.push_back('-');
			line2.push_back(char((a_vec.at(i).get_side_right())) + 48);
		}
	}
	line2.push_back(' ');
	line2.push_back('R');

	for (int i = 0; i < line2.size(); i++) {
		if (line2.at(i) == '|') {
			cout << line1.front();
			line1.pop();
		}
		else {
			cout << " ";
		}
	}
	cout << endl;
	for (int i = 0; i < line2.size(); i++) {
		cout << line2.at(i);
	}
	cout << endl;
	for (int i = 0; i < line2.size(); i++) {
		if (line2.at(i) == '|') {
			cout << line3.front();
			line3.pop();
		}
		else {
			cout << " ";
		}
	}
	cout << endl;
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
void BoardView::print_hand(Hand* a_hand) {
	cout << "\n\n";
	for (int i = 0; i < a_hand->size(); i++) {
		cout << a_hand->at(i).get_side_left() << " - " << a_hand->at(i).get_side_right() << '\t';
	}
	cout << '\n';
	for (int i = 1; i < a_hand->size() + 1; i++) { 
		cout << "  " << i << '\t';
	}
	cout << '\n';
}

