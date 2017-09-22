/************************************************************
* Name:  Elliott Barinberg                                  *
* Project : Project 1 - Longana								*
* Class : CMPS 366 OPL										*
* Date : 9/9/17												*
************************************************************/
#include "Round.h"
#include "Serialization.h"

Round::Round() {

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
			while (!round_over(p1, p3, a_board->get_stack())) {
				if (p1->get_player_move()) {
					BoardView::print_board(a_board->create_vector_to_print(nummoves));
					BoardView::print_hand(p1->get_hand());
				}
				p1->play(a_board->get_stack().size(), a_board->get_leftmost(), a_board->get_rightmost(), a_board, nummoves, p3->get_passed(), score, p3);
				p3->set_player_move(true);
				if (!round_over(p1, p3, a_board->get_stack())) {
					p3->play(a_board->get_stack().size(), a_board->get_leftmost(), a_board->get_rightmost(), a_board, p1->get_passed());
					p1->set_player_move(true);
				}
			}
		}
		else if (p1->has_tile(a_board->get_center())) {
			ready_to_start = true;
			p1->remove_tile(a_board->get_center());
			p1->set_player_move(false);
			p3->set_player_move(true);

			while (!round_over(p1, p3, a_board->get_stack())) {
				p3->play(a_board->get_stack().size(), a_board->get_leftmost(), a_board->get_rightmost(), a_board, p1->get_passed());
				p1->set_player_move(true);
				p3->set_player_move(false);
				if (!round_over(p1, p3, a_board->get_stack())) {
					BoardView::print_board(a_board->create_vector_to_print(nummoves));
					BoardView::print_hand(p1->get_hand());
					p1->play(a_board->get_stack().size(), a_board->get_leftmost(), a_board->get_rightmost(), a_board, nummoves, p3->get_passed(), score, p3);
					p1->set_player_move(false);
					p3->set_player_move(true);
				}
			}
		}
		else if (p3->has_tile(a_board->get_center())) {
			ready_to_start = true;
			p3->remove_tile(a_board->get_center());
			p3->set_player_move(false);
			p1->set_player_move(true);
			while (!round_over(p1, p3, a_board->get_stack())) {
				BoardView::print_board(a_board->create_vector_to_print(nummoves));
				BoardView::print_hand(p1->get_hand());
				p1->play(a_board->get_stack().size(), a_board->get_leftmost(), a_board->get_rightmost(), a_board, nummoves, p3->get_passed(), score, p3);
				p1->set_player_move(false);
				p3->set_player_move(true);

				if (!round_over(p1, p3, a_board->get_stack())) {
					p3->play(a_board->get_stack().size(), a_board->get_leftmost(), a_board->get_rightmost(), a_board, p1->get_passed());
					p3->set_player_move(false);
					p1->set_player_move(true);
				}
			}
		}
		else {
			while (!p1->has_tile(center) && !p3->has_tile(center)) {
				p1->fill_hand(a_board->get_top_n(1));
				p3->fill_hand(a_board->get_top_n(1));
				cout << "\nNeither player has the engine, you need to draw\n";
			}
		}
	} while (!ready_to_start);
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