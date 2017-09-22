/************************************************************
* Name:  Elliott Barinberg                                  *
* Project : Project 1 - Longana								*
* Class : CMPS 366 OPL										*
* Date : 9/9/17												*
************************************************************/
#include "Human.h"
#include "Help.h"
#include "Serialization.h"
#include "BoardView.h"
/* *********************************************************************
Function Name: play
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
void Human::play(int boneyard_size, int left_end, int right_end, Board* a_board, int nummoves, bool last_played, int tourn_score, Computer* comp) {
	if (Player::get_player_move() == false) {
		return;
	}
	num = 1;
	side = 'a';
	has_legal_move = Computer::has_a_legal_move(comp->get_passed(),left_end,right_end, Human::get_hand());
	
	if (has_legal_move) {
		Player::set_passed(false);
		// if legal move
		while (!play(num, side, left_end, right_end, last_played)) {
			do{
				num = 0;
				cout << "\nPlease enter number associated with piece you would like to move it (1 - " << Player::get_hand_size(Player::get_hand()) << " or enter 'p' for pass or 'h' for help or 's' for save): ";
				getline(cin, buffer);
				has_legal_move = Computer::has_a_legal_move(comp->get_passed(), left_end, right_end, Human::get_hand());
				if (has_legal_move) {
					if (toupper(buffer[0]) == 'H') {
						Help::Help(get_hand(), a_board->create_vector_to_print(nummoves), Player::get_passed());
					}
					else if (toupper(buffer[0]) == 'S') {
						Serialization::print_to_file(tourn_score, nummoves, comp, Player::get_hand(), a_board, Player::get_score(), Player::get_player_move(), Player::get_passed());
					}
					else if (buffer[0] >= '0' && buffer[0] <= '9') {
						num = stoi(buffer);
					}
					// should i do set_passed here
					Player::set_passed(false);
				}
				else {
					if (toupper(buffer[0]) == 'P') {
						if (boneyard_size > 0) {
							cout << "\nDrawing tile\n";
							Player::fill_hand(a_board->get_top_n(1));
							Player::set_passed(true);
							BoardView::print_board(a_board->create_vector_to_print(nummoves));
							BoardView::print_hand(Human::get_hand());
						}
						else {
							cout << "\nBoneyard is empty, cannot pass\n";
							Player::set_passed(true);
						}
					}
				}
			} while (!(num >= 1 && num <= Player::get_hand_size(Player::get_hand())));
			if (!Player::get_passed()) {
				do {
					cout << "\nLeft or Right: ";
					getline(cin, buffer);
					if (!buffer.empty()) {
						side = buffer.at(0);
					}
				} while (toupper(side) != 'L' && toupper(side) != 'R');
			}
		}

		switch (toupper(side)) {
		case 'L':
			if (a_board->add_to_left(temp)) {
				Player::remove_tile(Player::get_hand()->at(num - 1));
			}
			else {
				cout << "Illegal move, try again" << endl;
			}
			break;
		case 'R':
			if (a_board->add_to_right(temp)) {
				Player::remove_tile(Player::get_hand()->at(num - 1));
			}
			else {
				cout << "Illegal move, try again" << endl;
			}
			break;
		}

		
	}
	Player::set_player_move(false);
}

bool Human::play(int num, char side, int left_end, int right_end, bool last_passed) {
	temp = Player::get_hand()->at(num-1);
	switch (toupper(side)) {
	case 'L':
		if (temp.get_side_left() == left_end || temp.get_side_right() == left_end) {
			return true;
		}
		break;
	case 'R':
		if ((temp.get_side_left() == right_end && temp.get_side_right() == right_end) || ((last_passed && temp.get_side_left() == right_end) || last_passed && temp.get_side_right() == right_end)) {
			return true;
		}
		break;
	}
	return false;
}

bool Human::is_human() { return true; }