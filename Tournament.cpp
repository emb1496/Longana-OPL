/************************************************************
* Name:  Elliott Barinberg                                  *
* Project : Project 1 - Longana								*
* Class : CMPS 366 OPL										*
* Date : 9/9/17												*
************************************************************/
#include "Tournament.h"
#include "Serialization.h"

/* *********************************************************************
Function Name: Tournament
Purpose: Default constructor for Tournament class
Parameters:
none
Return Value: Constructor
Local Variables:
none
Algorithm:
none
Assistance Received: none
********************************************************************* */
Tournament::Tournament()
{

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
int Tournament::get_score() { return score; }

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
bool Tournament::game_over(Human *p1, Computer *p2) {
	if (p1->get_score() < score && p2->get_score() < score) {
		return false;
	}
	return true;
}

void Tournament::who_won(Human* p1, Computer* p2) {
	if (p1->get_hand_size(p1->get_hand()) == 0) {
		std::cout << "Human player wins with " << p1->make_a_num() << " , computer had remaining: " << p2->make_a_num() << endl;
		std::cout << "Human score was " << p1->get_score(); p1->add_to_score(p2->make_a_num()); cout << " and is now " << p1->get_score() << endl;
		std::cout << "Computer score was " << p2->get_score() << " and is now " << p2->get_score() << endl;
	}
	else if (p2->get_hand_size(p2->get_hand()) == 0) {
		std::cout << "Computer player wins with " << p2->make_a_num() << " , human had remaining: " << p1->make_a_num() << endl;
		std::cout << "Human score was " << p1->get_score() << " and is now " << p1->get_score() << endl;
		std::cout << "Computer score was " << p2->get_score(); p2->add_to_score(p1->make_a_num()); cout << " and is now " << p2->get_score() << endl;
	}
	else {
		if (p1->make_a_num() < p2->make_a_num()) {
			std::cout << "Human player wins with " << p1->make_a_num() << " , computer had remaining: " << p2->make_a_num() << endl;
			std::cout << "Human score was " << p1->get_score(); p1->add_to_score(p2->make_a_num()); cout << " and is now " << p1->get_score() << endl;
			std::cout << "Computer score was " << p2->get_score() << " and is now " << p2->get_score() << endl;
		}
		else if (p2->make_a_num() < p1->make_a_num()) {
			std::cout << "Computer player wins with " << p2->make_a_num() << " , human had remaining: " << p1->make_a_num() << endl;
			std::cout << "Human score was " << p1->get_score() << " and is now " << p1->get_score() << endl;
			std::cout << "Computer score was " << p2->get_score(); p2->add_to_score(p1->make_a_num()); cout << " and is now " << p2->get_score() << endl;
		}
		else {
			std::cout << "It is a draw neither player score will change" << endl;
			std::cout << "Human score is now " << p1->get_score() << endl;
			std::cout << "Computer score is now " << p2->get_score() << endl;
		}
	}
}

bool Tournament::game_over(Human* p1, Computer* p2, int a_score) {
	if (p1->get_score() < a_score && p2->get_score() < a_score) {
		return false;
	}
	return true;
}

void Tournament::play(Round* a_round, Human* p1, Computer* computer, Board* the_board, int nummoves, int score) {
	while (!game_over(p1, computer, score)) {
		if (p1->get_hand_size(p1->get_hand()) == 0) {
			p1->fill_hand(the_board->get_top_n(8));
		}
		if (computer->get_hand_size(computer->get_hand()) == 0) {
			computer->fill_hand(the_board->get_top_n(8));
			p1->set_player_move(false);
			computer->set_player_move(true);
		}
		the_board->set_center(nummoves);
		if (p1->has_tile(the_board->get_center())) {
			p1->remove_tile(the_board->get_center());
			p1->set_player_move(false);
			computer->set_player_move(true);
		}
		else if (computer->has_tile(the_board->get_center())) {
			computer->remove_tile(the_board->get_center());
		}

		a_round->play(p1, computer, nummoves, score, the_board);
		
		t_vec.push_back(*a_round);
		who_won(p1, computer);
		nummoves++;
		computer->get_hand()->~Hand();
		p1->get_hand()->~Hand();
		delete the_board;
		delete a_round;
		the_board = new Board;
		a_round = new Round;
	}
}

Tournament::Tournament(Human* p1, Computer* computer, Board* the_board, Round* a_round, int nummoves, int score) {
	if (score == 0) {
		score = 'a';
		while (isalpha(score)) {
			cout << "\nWhat is the tournament score: ";
			getline(cin, input);
			if (input.at(0) >= '0' && input.at(0) <= '9') {
				score = stoi(input);
			}
			cout << '\n';
		}
	}
	readytostart = false;
	center.set_engine(nummoves);
	if (p1->get_hand_size(p1->get_hand()) == 0) {
		p1->fill_hand(the_board->get_top_n(8));
	}
	if (computer->get_hand_size(computer->get_hand()) == 0) {
		computer->fill_hand(the_board->get_top_n(8));
	}
	// find who has the tile and draw if neither has it
	if (the_board->get_left_side().size() == 0 && the_board->get_right_side().size() == 0 && p1->get_hand()->size(*p1->get_hand()->get_hand()) == 8 && computer->get_hand()->get_hand()->size() == 8) {
		while (!readytostart) {
			if (p1->has_tile(center)) {
				cout << "\nHuman has the engine: \n\n";
				system("pause");
				readytostart = true;
			}

			else if (computer->has_tile(center)) {
				cout << "\nComputer has the engine: \n\n";
				system("pause");
				readytostart = true;
			}

			else {
				cout << "\nNeither player has the engine, you need to draw\n\n" << endl;
				system("pause");
				p1->fill_hand(the_board->get_top_n(1));
				computer->fill_hand(the_board->get_top_n(1));
			}
		}
	}
	play(a_round, p1, computer, the_board, nummoves, score);
}

inline int Tournament::get_nummoves() { return nummoves; }