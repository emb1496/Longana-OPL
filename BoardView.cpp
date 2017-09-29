/************************************************************
* Name:  Elliott Barinberg                                  *
* Project : Project 1 - Longana								*
* Class : CMPS 366 OPL										*
* Date : 9/9/17												*
************************************************************/
#include "BoardView.h"

/* *********************************************************************
Function Name: print_board
Purpose: To output the baord left to right using a vector of tiles
Parameters:
a_vec is a vector of Tiles in left to right order, passed by reference
line1 - queue of Tiles
line2 - vector of Tiles
line3 - queue of Tiles
Return Value: none
Local Variables:
none
Algorithm:
1.	start on a new line
2.	empty line1, line2, and line3
3.	push 'L' into line 2
4.	loop through a_vec and check if it is a double
	if it is a double then push the left and right sides into
	lines 1 & 3 and a " |" into line 2
	otherwise push the tile into line 2 in the form " n-n"
5.	Push the " R" into the end of line 2
6.	Loop through line 2 and check if each spot contains a '|'
	if it doesn't print a space
	if it does print the front of line1 and pop line1
7.	On a new line, loop through line 2 and print every character one
	by one
8.	On another new line, loop thorough line2 and check each for '|'
	if its false print empty space
	if its true print the front of line3 and pop line3 and start a new
	line for the next output stream
Assistance Received: none
********************************************************************* */
void BoardView::print_board(vector<Tile> &a_vec) {
	cout << '\n';
	// used as the top line in output
	static queue<char> line1;

	// middle line in output
	static vector<char> line2;

	// last line in output
	static queue<char> line3;

	// empty lines
	while (!line1.empty()) { line1.pop(); }
	while (!line2.empty()) { line2.pop_back(); }
	while (!line3.empty()) { line3.pop(); }
	line2.push_back('L');

	// create the 3 lines
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

	// print line 1
	for (int i = 0; i < line2.size(); i++) {
		if (line2.at(i) == '|') {
			cout << line1.front();
			line1.pop();
		}
		else {
			cout << " ";
		}
	}
	cout << '\n';

	// print line 2
	for (int i = 0; i < line2.size(); i++) {
		cout << line2.at(i);
	}
	cout << '\n';

	// print line 3
	for (int i = 0; i < line2.size(); i++) {
		if (line2.at(i) == '|') {
			cout << line3.front();
			line3.pop();
		}
		else {
			cout << " ";
		}
	}
	cout << '\n';
}

/* *********************************************************************
Function Name: print_hand
Purpose: To print the user hand and the index of the tileto the user
Parameters:
Hand* a_hand, a pointer to the user hand
Return Value: none
Local Variables:
none
Algorithm:
1.	Add a couple lines of space
2.	loop through the hand and print each tile horizontally one by one
3.	On a new line print the key to the hand, the key should always be
	as centered on the tile as possible which is why \t is used to
	ensure it stays aligned, the key starts at one to abstract the
	user away from the 0th element
4.	Leave the output on the next line for another output stream
Assistance Received: none
********************************************************************* */
void BoardView::print_hand(Hand* a_hand) {
	cout << "\n\n";

	// print each item in the hand
	for (int i = 0; i < a_hand->size(); i++) {
		cout << a_hand->at(i).get_side_left() << " - " << a_hand->at(i).get_side_right() << '\t';
	}
	cout << '\n';
	
	// print key
	for (int i = 1; i < a_hand->size() + 1; i++) { 
		cout << "  " << i << '\t';
	}
	cout << '\n';
}

/* *********************************************************************
Function Name: print_who_won
Purpose: To print who won the round to the screen
Parameters:
Human* p1, Computer* p2, the two players passed by pointer
int score, the tournament score
Return Value: none
Local Variables:
none
Algorithm:
1.	Check if either player emptied their hands
2.	If so the player with no hand wins and I add accordingly and 
	print out the old and new scores to the screen
3.	Else check which player has a lower number and that player wins
	Then the other players sum of pips to that player and print
	out the old and new scores for all the players
Assistance Received: none
********************************************************************* */
void BoardView::print_who_won(Human* p1, Computer* p2, int score) {
	if (p1->get_hand_size(p1->get_hand()) == 0) {
		cout << "\nHuman player wins with " << p1->make_a_num() << " , computer had remaining: " << p2->make_a_num() << "\n\n";
		cout << "Human score was " << p1->get_score(); p1->add_to_score(p2->make_a_num()); cout << " and is now " << p1->get_score() << "\n\n";
		cout << "Computer score was " << p2->get_score() << " and is now " << p2->get_score() << "\n";
	}
	else if (p2->get_hand_size(p2->get_hand()) == 0) {
		cout << "\nComputer player wins with " << p2->make_a_num() << " , human had remaining: " << p1->make_a_num() << "\n\n";
		cout << "Human score was " << p1->get_score() << " and is now " << p1->get_score() << "\n\n";
		cout << "Computer score was " << p2->get_score(); p2->add_to_score(p1->make_a_num()); cout << " and is now " << p2->get_score() << "\n";
	}
	else {
		if (p1->make_a_num() < p2->make_a_num()) {
			cout << "\nHuman player wins with " << p1->make_a_num() << " , computer had remaining: " << p2->make_a_num() << "\n\n";
			cout << "Human score was " << p1->get_score(); p1->add_to_score(p2->make_a_num()); cout << " and is now " << p1->get_score() << "\n\n";
			cout << "Computer score was " << p2->get_score() << " and is now " << p2->get_score() << "\n";
		}
		else if (p2->make_a_num() < p1->make_a_num()) {
			cout << "\nComputer player wins with " << p2->make_a_num() << " , human had remaining: " << p1->make_a_num() << "\n\n";
			cout << "Human score was " << p1->get_score() << " and is now " << p1->get_score() << "\n\n";
			cout << "Computer score was " << p2->get_score(); p2->add_to_score(p1->make_a_num()); cout << " and is now " << p2->get_score() << "\n";
		}
		else {
			cout << "\nIt is a draw neither player score will change" << "\n\n";
			cout << "Human score is now " << p1->get_score() << "\n\n";
			cout << "Computer score is now " << p2->get_score() << "\n";
		}
	}
	cout << '\n';
	system("pause");
	cout << "Reminder the tournament score is " << score << '\n';
	system("pause");
}