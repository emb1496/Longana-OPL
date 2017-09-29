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
	//set default values for private variables
	score=0;
	center = new Tile;
	center->set_engine(0);
	nummoves=0;
	readytostart=false;
	input="";
}

/* *********************************************************************
Function Name: game_over
Purpose: to check if the game is over
Parameters:
Human* p1, pointer to human player
Computer* p2, pointer to computer player
a_score int for tournament score
Return Value: bool if the game is over
Local Variables:
none
Algorithm:
1.	check if the game is not over and then return false
2.	if the game is over output who won
Assistance Received: none
********************************************************************* */
bool Tournament::game_over(Human* p1, Computer* p2, int a_score) {
	if (p1->get_score() < a_score && p2->get_score() < a_score) {
		return false;
	}
	else {
		cout << "Tournament score was " << a_score << '\n';
		if (p1->get_score() > p2->get_score()) {
			cout << "Human wins the tournament with " << p1->get_score() << " points\n";
		}
		else {
			cout << "Computer wins the tournament with " << p2->get_score() << " points\n";
		}
		system("pause");
		return true;
	}
}

/* *********************************************************************
Function Name: play
Purpose: to play the tournament
Parameters:
Human* p1, pointer to human player
Computer* p2, pointer to computer player
a_score int for tournament score
Round* a_round, pointer to round object
Board* the_board, pointer to board object
nummoves, round number
Return Value: none
Local Variables:
none
Algorithm:
1.	check if the game is over 
2.	fill hands and set center
3.	offer a save
4.	call the round play function
5.	"delete" and "new" memory
Assistance Received: none
********************************************************************* */
void Tournament::play(Round* a_round, Human* p1, Computer* computer, Board* the_board, int nummoves, int a_score) {
	while (!game_over(p1, computer, a_score)) {
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
			computer->set_player_move(false);
			p1->set_player_move(true);
		}
		a_char = '\0';
		while (toupper(a_char) != 'Y' && toupper(a_char) != 'N') {
			cout << "\nBefore we begin would you like to save: ";
			getline(cin, input);
			if (!input.empty()) {
				a_char = input.at(0);
			}
		}
		if (toupper(a_char) == 'Y') {
			Serialization::print_to_file(a_score, nummoves, computer, p1->get_hand(), the_board, p1->get_score(), p1->get_player_move(), p1->get_passed());
		}
		a_round->play(p1, computer, nummoves, a_score, the_board);
		nummoves++;
		computer->get_hand()->~Hand();
		p1->get_hand()->~Hand();
		delete the_board;
		delete a_round;
		the_board = new Board;
		a_round = new Round;
		p1->set_passed(false);
		computer->set_passed(false);
	}
}

/* *********************************************************************
Function Name: Tournament
Purpose: constructor for Tournament
Parameters:
Human* p1, pointer to human player
Computer* p2, pointer to computer player
score int for tournament score
Round* a_round, pointer to round object
Board* the_board, pointer to board object
nummoves, round number
Return Value: none
Local Variables:
center, the center tile
Algorithm:
1.	set the center tile
2.	fill the hands
3.	call the play function and pass it the parameters it needs
Assistance Received: none
********************************************************************* */
Tournament::Tournament(Human* p1, Computer* computer, Board* the_board, Round* a_round, int nummoves, int score) {
	center = new Tile;
	center->set_engine(nummoves);
	while (score == 0) {
		cout << "\nWhat is the tournament score: ";
		getline(cin, input);
		if (!input.empty() && input.at(0) >= '0' && input.at(0) <= '9') {
			score = stoi(input);
		}
	}
	readytostart = false;
	center->set_engine(nummoves);
	if (p1->get_hand_size(p1->get_hand()) == 0) {
		p1->fill_hand(the_board->get_top_n(8));
	}
	if (computer->get_hand_size(computer->get_hand()) == 0) {
		computer->fill_hand(the_board->get_top_n(8));
	}
	play(a_round, p1, computer, the_board, nummoves, score);
	delete center;
}

/* *********************************************************************
Function Name: ~Tournament
Purpose: destructor for Tournament
Parameters:
none
Return Value: none
Local Variables:
center, the center tile
Algorithm:
1.	delete center
Assistance Received: none
********************************************************************* */
Tournament::~Tournament() {
	delete center;
}