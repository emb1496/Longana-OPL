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
Function Name: Human
Purpose: Constructor for Human
Parameters:
none
Return Value: none
Local Variables:
buffer is a string
temp is a Tile
num is an int
side is a char
has_legal_move is a bool
and count is an int
Algorithm:
1) set all private member values
Assistance Received: none
********************************************************************* */
Human::Human() {
	// give all private variables default values
	buffer="";
	temp = new Tile;
	num=0;
	side='\0';
	has_legal_move=false;
	count=0;
}

/* *********************************************************************
Function Name: play
Purpose: play function for human to make a move
Parameters:
int boneyard_size, left_end, right_end, nummoves, tourn_score
--> deck side, left and right most ends, round number, tournament score,
	respectively
	Board* a_board --> the board
	Computer* comp --> computer Player
Return Value: none
Local Variables:
none
Algorithm:
1.  While you cannot play the number and character combos and the count
	is not 29 print the Boardview and offer the player options to move, 
	help, pass, or save based on player input act accordingly
2.	once the player moves make sure the board gets modified to match
Assistance Received: none
********************************************************************* */
void Human::play(int boneyard_size, int left_end, int right_end, Board* a_board, int nummoves, bool last_played, int tourn_score, Computer* comp) {
	if (get_player_move() == false) {
		return;
	}
	num = 1;
	side = 'a';
	count = 0;
	has_legal_move = Computer::has_a_legal_move(!comp->get_passed(),left_end,right_end, get_hand(), is_human());

	while (!play(num, side, left_end, right_end, comp->get_passed()) && count != 29) {
		do{
			num = 0;
			cout << "\nPlease enter number associated with piece you would like to move it (1 - " << get_hand_size(get_hand()) << " or enter 'p' for pass or 'h' for help or 's' for save): ";
			getline(cin, buffer);
			has_legal_move = Computer::has_a_legal_move(!comp->get_passed(), left_end, right_end, get_hand(), is_human());
			if (has_legal_move) {
				count = 0;
				set_passed(false);
				switch (toupper(buffer[0])) {
				case 'H':
					Help::Help(get_hand(), a_board->create_vector_to_print(nummoves), comp->get_passed());
					break;
				case 'S':
					Serialization::print_to_file(tourn_score, nummoves, comp, get_hand(), a_board, get_score(), get_player_move(), get_passed());
					break;
				case 'P':
					cout << "You have a legal move, I would recommend using the help by pressing 'h'\n\n";
					break;
				default:
					if (buffer[0] >= '0' && buffer[0] <= '9') {
						num = stoi(buffer);
					}
					break;
				}
			}
			else {
				switch (toupper(buffer[0])) {
				case 'P':
					if (boneyard_size > 0 && Human::get_passed() == false) {
						cout << "\nDrawing tile\n";
						fill_hand(a_board->get_top_n(1));
						BoardView::print_board(a_board->create_vector_to_print(nummoves));
						BoardView::print_hand(get_hand());
						BoardView::print_boneyard_size(a_board->get_boneyard());
						cout << "\nIf you pass again computer will play\n";
						boneyard_size--;
						count++;
						Human::set_passed(true);
						num = just_passed(comp, left_end, right_end, a_board, nummoves, tourn_score);
						count = 29;
					}
					else if (boneyard_size == 0) {
						cout << "\nBoneyard is empty, cannot draw\n";
						set_passed(true);
						count = 29;
						num = 1;
					}
					else {
						cout << "Computer to play\n";
						count = 29;
					}
					break;
				case 'S':
					Serialization::print_to_file(tourn_score, nummoves, comp, get_hand(), a_board, get_score(), get_player_move(), get_passed());
					break;
				case 'H':
					Help::Help(Human::get_hand(), a_board->create_vector_to_print(nummoves), get_passed());
					break;
				default:
					if (!buffer.empty()) {
						cout << "\nNo legal moves\n";
					}
					break;
				}
			}
		} while (!(num >= 1 && num <= get_hand_size(Human::get_hand())) && count != 29);
		if (!get_passed()) {
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
		if (a_board->add_to_left(*temp)) {
			remove_tile(get_hand()->at(num - 1));
		}
		else {
			cout << "Illegal move, try again" << endl;
		}
		break;
	case 'R':
		if (a_board->add_to_right(*temp)) {
			remove_tile(get_hand()->at(num - 1));
		}
		else {
			cout << "Illegal move, try again" << endl;
		}
		break;
	}
	set_player_move(false);
}

/* *********************************************************************
Function Name: just_passed
Purpose: after human passes this function avoids saving a state we do
	not have any case for
Parameters:
Computer* comp --> computer Player
int left_end, right_end, nummoves, tourn_score 
the left and right most pips, round nummber, and tournament score
respectfully
Return Value: int new num value
Local Variables:
none
Algorithm:
1.  While you cannot play the number and character combos and the count
is not 29 print the Boardview and offer the player options to move,
help or pass based on player input act accordingly
2.	once the player moves return the number to match
Assistance Received: none
********************************************************************* */
int Human::just_passed(Computer* comp, int left_end, int right_end, Board* a_board, int nummoves, int tourn_score) {
	do {
		num = 0;
		cout << "\nPlease enter number associated with piece you would like to move it (1 - " << get_hand_size(get_hand()) << " or enter 'p' for pass or 'h' for help): ";
		getline(cin, buffer);
		has_legal_move = Computer::has_a_legal_move(!comp->get_passed(), left_end, right_end, get_hand(), is_human());
		if (has_legal_move) {
			lcv = false;
			count = 0;
			set_passed(false);
			switch (toupper(buffer[0])) {
			case 'H':
				Help::Help(get_hand(), a_board->create_vector_to_print(nummoves), get_passed());
				break;
			case 'P':
				cout << "You have a legal move, I would recommend using the help by pressing 'h'\n\n";
				break;
			default:
				if (!buffer.empty() && buffer[0] >= '0' && buffer[0] <= '9') {
					num = stoi(buffer);
				}
				break;
			}
		}
		else {
			switch (toupper(buffer[0])) {
			case 'P':
				lcv = false;
				break;
			default:
				lcv = true;
				break;
			}
		}
	} while (lcv || (has_legal_move && !(num > 0 && num <= Player::get_hand()->size())));
	return num;
}

/* *********************************************************************
Function Name: play
Purpose: overloaded play function which gets called from the while loop
	as a continuing condition in play
Parameters:
int num, left_end, right_end --> the tile number and left and right
	most pips
char side --> left or right
bool last_passed --> last player passed
Return Value: bool
Local Variables:
temp a tile used to do comparisons
Algorithm:
1.  set temp to the tile which we want to play
2.	check if it can be played
	if yes return true
	if no return false
Assistance Received: none
********************************************************************* */
bool Human::play(int num, char side, int left_end, int right_end, bool last_passed) {
	if (num == 0) {
		return false;
	}
	*temp = get_hand()->at(num-1);
	switch (toupper(side)) {
	case 'L':
		if (temp->get_side_left() == left_end || temp->get_side_right() == left_end) {
			return true;
		}
		break;
	case 'R':
		if ((temp->get_side_left() == right_end && temp->get_side_right() == right_end) || ((last_passed && temp->get_side_left() == right_end) || last_passed && temp->get_side_right() == right_end)) {
			return true;
		}
		break;
	}
	return false;
}

/* *********************************************************************
Function Name: ~Human
Purpose: Human destructor
Parameters:
none
Return Value: none
Local Variables:
temp
Algorithm:
1) delete temp
Assistance Received: none
********************************************************************* */
Human::~Human() {
	delete temp;
}