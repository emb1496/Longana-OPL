/************************************************************
* Name:  Elliott Barinberg                                  *
* Project : Project 1 - Longana								*
* Class : CMPS 366 OPL										*
* Date : 9/9/17												*
************************************************************/
#include "Round.h"
#include "Serialization.h"

/* *********************************************************************
Function Name: Round
Purpose: constructor for the round class
Parameters:
none
Return Value: none
Local Variables:
ready_to_start bool loop control variable
Algorithm:
set ready_to_start to false
Assistance Received: none
********************************************************************* */
Round::Round() {
	// set ready to start to false 
	ready_to_start = false;
}

/* *********************************************************************
Function Name: players_make_moves
Purpose: to make the players play their moves
Parameters:
Human* p1 - human player
Computer* p3 - computer player
Board* a_board - board object
int nummoves, score - round numer and tournament score
Return Value: none
Local Variables:
none
Algorithm:
call the player play functions and print the boardview and check for the
round to be over
Assistance Received: none
********************************************************************* */
void Round::players_make_moves(Human* p1, Computer* p3, Board* a_board, int nummoves, int score) {
	if (p1->get_player_move()) {
		BoardView::print_board(a_board->create_vector_to_print(nummoves));
		BoardView::print_hand(p1->get_hand());
		BoardView::print_boneyard_size(a_board->get_boneyard());
	}
	p1->play(a_board->get_boneyard().size(), a_board->get_leftmost(), a_board->get_rightmost(), a_board, nummoves, !p3->get_passed(), score, p3);
	if (!round_over(p1, p3, a_board->get_boneyard())) {
		p3->set_player_move(true);
		p3->set_passed(false);
	}
	if (!round_over(p1, p3, a_board->get_boneyard())) {
		a_char = '\0';
		input = "";
		while (toupper(a_char) != 'Y' && toupper(a_char) != 'N') {
			cout << "Would you like to save y/n: ";
			getline(cin, input);
			if (!input.empty()) {
				a_char = input[0];
			}
		}
		if (toupper(a_char) == 'Y') {
			Serialization::print_to_file(score, nummoves, p3, p1->get_hand(), a_board, p1->get_score(), p1->get_player_move(), p1->get_passed());
		}
		p3->play(a_board->get_boneyard().size(), a_board->get_leftmost(), a_board->get_rightmost(), a_board, !p1->get_passed());
		if (!round_over(p1, p3, a_board->get_boneyard())) {
			p1->set_player_move(true);
			p1->set_passed(false);
		}
	}
}

/* *********************************************************************
Function Name: neither_has_center
Purpose: to loop until a player has the center
Parameters:
Human* p1 - human player
Computer* p3 - computer player
Board* a_board - board object
Return Value: none
Local Variables:
none
Algorithm:
while neither player has the center continue to draw tiles from pile
Assistance Received: none
********************************************************************* */
void Round::neither_has_center(Human* p1, Computer* p3, Board* a_board) {
	while (!p1->has_tile(a_board->get_center()) && !p3->has_tile(a_board->get_center())) {
		p1->fill_hand(a_board->get_top_n(1));
		p3->fill_hand(a_board->get_top_n(1));
		cout << "\nNeither player has the engine, you need to draw\n";
		system("pause");
		if (p1->has_tile(a_board->get_center())) {
			cout << "Human has the engine, computer plays first\n";
			p1->set_player_move(false);
			p3->set_player_move(true);
		}
		else if (p3->has_tile(a_board->get_center())) {
			cout << "Computer has the engine, human plays first\n";
			p1->set_player_move(true);
			p3->set_player_move(false);
		}
	}
}

/* *********************************************************************
Function Name: play
Purpose: to play a round
Parameters:
2 players passed by pointer, one human, once computer
Return Value: void
Local Variables:
none
Algorithm:
1) 
Assistance Received: none
********************************************************************* */
void Round::play(Human* p1, Computer * p3, int nummoves, int score, Board* a_board) {
	a_board->set_center(nummoves);
	center = a_board->get_center();
	ready_to_start = false;
	do {
		if (!p1->has_tile(a_board->get_center()) && !p3->has_tile(a_board->get_center()) && ((p1->get_hand()->size(*p1->get_hand()->get_hand()) != 8 || p3->get_hand()->size(*p3->get_hand()->get_hand()) != 8) || (!a_board->get_left_side().empty() || !a_board->get_right_side().empty()))) {
			ready_to_start = true;
			while (!round_over(p1, p3, a_board->get_boneyard())) {
				players_make_moves(p1, p3, a_board, nummoves, score);
			}
		}
		else if (p1->has_tile(a_board->get_center())) {
			ready_to_start = true;
			p1->remove_tile(a_board->get_center());
			p1->set_player_move(false);
			p3->set_player_move(true);

			while (!round_over(p1, p3, a_board->get_boneyard())) {
				players_make_moves(p1, p3, a_board, nummoves, score);
			}
		}
		else if (p3->has_tile(a_board->get_center())) {
			ready_to_start = true;
			p3->remove_tile(a_board->get_center());
			p3->set_player_move(false);
			p1->set_player_move(true);
			while (!round_over(p1, p3, a_board->get_boneyard())) {
				players_make_moves(p1, p3, a_board, nummoves, score);
			}
		}
		else {
			neither_has_center(p1, p3, a_board);
		}
	} while (!ready_to_start);
	BoardView::print_who_won(p1, p3, score);
}


/* *********************************************************************
Function Name: round_over
Purpose: to check if round is over
Parameters:
2 players passed by pointer, one human, once computer
Return Value: boolean whether the round is over
Local Variables:
none
Algorithm:
1)
Assistance Received: none
********************************************************************* */
bool Round::round_over(Human* p1, Computer *p2, stack<Tile> a_pile) {
	if (p1->get_hand_size(p1->get_hand()) == 0) {
		return true;
	}
	if (p2->get_hand_size(p2->get_hand()) == 0) {
		return true;
	}
	if (a_pile.size() == 0 && p1->get_passed() == true && p2->get_passed() == true) {
		return true;
	}
	return false;
}

/* *********************************************************************
Function Name: ~Round
Purpose: destructor for round
Parameters:
none
Return Value: none
Local Variables:
none
Algorithm:
none 
Assistance Received: none
********************************************************************* */
Round::~Round() {

}