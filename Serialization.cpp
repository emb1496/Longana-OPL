/************************************************************
* Name:  Elliott Barinberg                                  *
* Project : Project 1 - Longana								*
* Class : CMPS 366 OPL										*
* Date : 9/20/17											*
************************************************************/
#include "Serialization.h"
// variables used staticly
string Serialization::filename = "";
string Serialization::a_string = "";
ofstream Serialization::out_file;
stringstream Serialization::a_stream;
Tile Serialization::temp;

/* *********************************************************************
Function Name: Serialization
Purpose: Default constructor for serialization
Parameters:
none
Return Value: none
Local Variables:
none
Algorithm:
set private member variables to default values
Assistance Received: none
********************************************************************* */
Serialization::Serialization() {
	in_file.clear();
	while (!a_pile.empty()) {
		a_pile.pop();
	}
	while (!a_vec.empty()) {
		a_vec.pop_back();
	}
	while (!left_side.empty()) {
		left_side.pop();
	}
	while (!right_side.empty()) {
		right_side.pop();
	}
	temp1 = new Tile;
	a_char ='\0';
	last_player_passed = false;
	my_string = "";
	one_too_far = false;
}

/* *********************************************************************
Function Name: Serialization
Purpose: Overloaded constructor
Parameters:
Human* p1 a human player, Computer* computer a computer player, Board*
the_board is the board, BoardView* b is what allows the board to be
printed to the console, Round* a_round is the round functionality,
int nummoves is the moves that have been made, int score is
the score to the tournament, and Tournament game is a tournament
Return Value: none
Local Variables:
a_char and my_string to do input
Algorithm:
1) check whether player wants to load a game
2) if yes call read_from_file and make a tournament out of the values that get changed
3) if not make a new blank tournament
Assistance Received: none
********************************************************************* */
Serialization::Serialization(Human* p1, Computer* computer, Board* the_board, Round* a_round, int &nummoves, int &score, Tournament* game) {
	// initialize a_char
	a_char = 'f';

	// would the player like to load a game which has been saved
	while (toupper(a_char) != 'Y' && toupper(a_char) != 'N') {
		cout << "Would you like to load a game(y/n): ";
		getline(cin, my_string);
		if (!my_string.empty()) {
			a_char = my_string.at(0);
		}
	}

	// load game
	if (toupper(a_char) == 'Y') {
		read_from_file(p1, computer, the_board, nummoves, score);
		game = new Tournament(p1, computer, the_board, a_round, nummoves, score);
	}

	// new game
	else {
		game = new Tournament(p1, computer, the_board, a_round, nummoves, score);
	}
}

/* *********************************************************************
Function Name: read_score
Purpose: to read the score from a serialized file
Parameters:
int score passed by reference
Return Value: void
Local Variables:
stringstream a_stream and string a_string used to parse the text file
Algorithm:
parse a_stream for the score, if there save it to score
Assistance Received: none
********************************************************************* */
void Serialization::read_score(int &score) {\

	// parse a _stream until we find "Score:" then go one more parse
	a_string = "a";
	while(a_string.compare("Score:")!=0) {
		a_stream >> a_string;
	}
	a_stream >> a_string;

	// if it iss a number then store it in score
	if (a_string.at(0) >= '0'&&a_string.at(0) <= '9') {
		score = atoi(a_string.c_str());
		one_too_far = false;
	}

	// if it is empty or not numberic get tournament score from the user
	else {
		one_too_far = true;
		while (!(a_string.at(0) >= '0'&&a_string.at(0) <= '9')) {
			cout << "Error reading score, enter a score: ";
			cin.ignore();
			getline(cin, a_string);
		}
		score = atoi(a_string.c_str());
	}
}

/* *********************************************************************
Function Name: read_nummoves
Purpose: to read the round number from the saved text file
Parameters:
int nummoves representing number of moves, passed by reference
Return Value: void
Local Variables:
stringstream a_stream and string a_string used to parse the text file
one_to_far boolean value which moderates cin.ignore();
Algorithm:
parse a_stream for the number of moves and save it, with error checking
Assistance Received: none
********************************************************************* */
void Serialization::read_nummoves(int &nummoves) {
	a_string = " ";
	
	// parse until we get to where round number is supposed to be
	while(a_string.compare("No.:")!=0) {
		a_stream >> a_string;
	}
	a_stream >> a_string;

	// make sure round number is numeric and store it
	if (a_string.at(0) >= '0' && a_string.at(0) <= '9') {
		nummoves = atoi(a_string.c_str());
		one_too_far = false;
	}

	// round is not numeric get the input from the user
	else {
		while (!(a_string.at(0) >= '0' && a_string.at(0) <= '9')) {
			cout << "Error reading Round No, enter Round No: ";
			if (!one_too_far) {
				cin.ignore();
			}
			getline(cin, a_string);
		}
		one_too_far = true;
		
		nummoves = atoi(a_string.c_str());
	}
}

/* *********************************************************************
Function Name: read_player_hand
Purpose: to read a player hand and score from serialized file and store
them in an object
Parameters:
Player pointer, that way either a human or a computer can be passed to
the function and modified from within the function
Return Value: void
Local Variables:
stringstream a_stream and string a_string used to parse the text file
one_to_far boolean value which moderates cin.ignore();
a_pile stack to store the tiles
Algorithm:
parse a_stream for the hand and save it
parse a_stream for the player score and save it
Assistance Received: none
********************************************************************* */
void Serialization::read_player_hand(Player* a_player) {
	a_string = " ";
	// parse a_stream until we get to the hand
	while(a_string.compare("Hand:") != 0) {
		a_stream >> a_string;
	}
	a_stream >> a_string;
	while (a_pile.empty() == false) {
		a_pile.pop();
	}

	// until we get to player score parse each tile and store it in temp1 then push temp1 to a_pile
	while (toupper(a_string.at(0))!='S') {
		temp1 = new Tile;
		temp1->set_side_left(a_string.at(0) - 48);
		temp1->set_side_right(a_string.at(2) - 48);
		a_pile.push(*temp1);
		a_stream >> a_string;
		delete temp1;
	}

	// fill the player hand with the contents in a_pile
	a_player->fill_hand(a_pile);

	// parse for the player score and verify input
	a_stream >> a_string;
	while (!(a_string.at(0) >= '0' && a_string.at(0) <= '9')) {
		if (a_player->is_human()) {
			cout << "Error reading score, please enter human player score: ";
		}
		else {
			cout << "Error reading score, please enter computer player score: ";
		}
		if (!one_too_far) {
			cin.ignore();
		}
		getline(cin, a_string);
		one_too_far = true;
	}

	// add serialized score to player score
	a_player->add_to_score(atoi(a_string.c_str()));
}

/* *********************************************************************
Function Name: read_layout
Purpose: to read the board layout and store it in an object
Parameters:
Board pointer representing the board to be modified
Return Value: void
Local Variables:
stringstream a_stream and string a_string used to parse the text file
one_to_far boolean value which moderates cin.ignore();
a_vec vector of tiles for storage
right_side stack of tiles to represent right side of center tile
left_side queue of tiles to represent left side of center tile
Algorithm:
parse a_stream for the tiles storing them to a_vec
push the back tile in a_vec into right_side until the back is the center
pop the center
push the back tile into left_side until a_vec is empty
use add_to_left() and add_to_right() to store the left and right sides
of the board
Assistance Received: none
********************************************************************* */
void Serialization::read_layout(Board* a_board) {

	// make sure board is empty
	while (a_vec.empty() == false) {
		a_vec.pop_back();
	}
	while (right_side.empty() == false) {
		right_side.pop();
	}
	while (left_side.empty() == false) {
		left_side.pop();
	}

	// parse until we get to left side
	while(a_string.compare("L")!=0) {
		a_stream >> a_string;
	}
	a_stream >> a_string;

	// read tiles into a_vec until we get to right side
	while (toupper(a_string.at(0)) != 'R') {
		temp1 = new Tile;
		temp1->set_side_left(a_string.at(0) - 48);
		temp1->set_side_right(a_string.at(2) - 48);
		a_vec.push_back(*temp1);
		a_stream >> a_string;
		delete temp1;
	}

	if (!a_vec.empty()) {
		// while we do not get to the center tile push tiles from the back of a_vec into right side and pop a_vec
		while ((a_vec.at(a_vec.size() - 1).get_side_left() != a_board->get_center().get_side_left()) || (a_vec.at(a_vec.size() - 1).get_side_right() != a_board->get_center().get_side_right())) {
			right_side.push(a_vec.at(a_vec.size() - 1));
			a_vec.pop_back();
		}

		// pop the center
		a_vec.pop_back();

		// until a_vec is empty push the tiles into left side
		while (a_vec.empty() == false) {
			left_side.push(a_vec.at(a_vec.size() - 1));
			a_vec.pop_back();
		}

		// until the local stack right_side is empty add the top tile into the right side of the board
		while (right_side.empty() == false) {
			a_board->add_to_right(right_side.top(), 0);
			right_side.pop();
		}

		// until the local queue left_side is empty add the front tile to the left side of the board
		while (left_side.empty() == false) {
			a_board->add_to_left(left_side.front(), 0);
			left_side.pop();
		}
	}
}

/* *********************************************************************
Function Name: read_boneyard
Purpose: to read the boneyard and save it to the board in order
Parameters:
Board pointer representing the board to be modified
Return Value: void
Local Variables:
stringstream a_stream and string a_string used to parse the text file
one_to_far boolean value which moderates cin.ignore();
right_side a queue of tiles
Algorithm:
parse the boneyard for tiles and save them in order to the FIFO queue
use create_pile() to modify the boneyard in the board with the queue
Assistance Received: none
********************************************************************* */
void Serialization::read_boneyard(Board* a_board) {
	
	// create the pile using the boneyard provided
	while(a_string.compare("Boneyard:")!=0) {
		a_stream >> a_string;
	}
	a_stream >> a_string;
	while (a_pile.empty() == false) {
		a_pile.pop();
	}
	while (right_side.empty() == false) {
		right_side.pop();
	}

	// parse until we get to word beginning in P
	while (toupper(a_string.at(0)) != 'P') {
		temp1 = new Tile;
		temp1->set_side_left(a_string.at(0) - 48);
		temp1->set_side_right(a_string.at(2) - 48);
		right_side.push(*temp1);
		a_stream >> a_string;
		delete temp1;
	}

	// push the stack we created into a_board's pile member variable
	a_board->create_pile(right_side);
}

/* *********************************************************************
Function Name: read_last_passed
Purpose: read if the last player passed
Parameters:
none
Return Value: void
Local Variables:
stringstream a_stream and string a_string used to parse the text file
last_player_passed boolean value to be modified based on whether or not 
player passed
Algorithm:
parse until you are at yes or no
if no set last_player_passed to false
else set last_player_passed to true
Assistance Received: none
********************************************************************* */
void Serialization::read_last_passed() {

	// parse for whether last player passed or not
	while(a_string.compare("Passed:") != 0) {
		a_stream >> a_string;
	}
	a_stream >> a_string;
	if (toupper(a_string.at(0)) == 'N') {
		last_player_passed = false;
	}
	else {
		last_player_passed = true;
	}
}

/* *********************************************************************
Function Name: read_next_play
Purpose: to read the next player from the saved text file
Parameters:
Human pointer p1 the human player
Computer pointer p2 the computer player
Board pointer the_board which is the board
Return Value: char either 'h' or 'c'
Local Variables:
stringstream a_stream and string a_string used to parse the text file
Algorithm:
parse a_stream for the next player
if it is computer set whether or not the human passed and return 'c'
if it is human set whether or not the computer passed and return 'h'
if there is nothing stored ask the user and act accordingly based on
previous two steps
Assistance Received: none
********************************************************************* */
char Serialization::read_next_play(Human* p1, Computer* p2, Board* the_board) {
	
	// parse for next player
	while(a_string.compare("Player:") != 0) {
		a_stream >> a_string;
	}
	if (a_stream >> a_string) {

		// return 'c' for computer or 'h' for human
		if (toupper(a_string.at(0)) == 'C') {
			p1->set_passed(last_player_passed);
			return 'c';
		}
		else {
			p2->set_passed(last_player_passed);
			return 'h';
			// human should play
		}
	}

	// verify in case its empty and read in from the user
	else {
		return '\0';
	}
}

/* *********************************************************************
Function Name: get_file_name
Purpose: return name of serialized text file
Parameters:
none
Return Value: string
Local Variables:
filename a string to return the name of the file
Algorithm:
Ask user for filename and check for the .txt extension
add .txt if missing
return filename
Assistance Received: none
********************************************************************* */
string Serialization::get_file_name() {
	filename.clear();
	while (filename.empty())
	{
		cout << "Enter filename(for test.txt simply enter \"test\"): ";
		getline(cin, filename);
	}

	// check if the file ends in ".txt"
	if (!(filename.at(filename.size() - 4 == '.') && filename.at(filename.size() - 3 == 't') && filename.at(filename.size() - 2 == 'x') && filename.at(filename.size() - 1 == 't'))) {
		filename.append(".txt");
	}
	return filename;
}

/* *********************************************************************
Function Name: parse_file
Purpose: to parse the file into a_stream
Parameters:
none
Return Value: void
Local Variables:
stringstream a_stream and string a_string used to parse the text file
in_file is fstream used to open the text file
Algorithm:
while not at end of file store line into a_string and add a_string to
the stream a_stream
Assistance Received: none
********************************************************************* */
void Serialization::parse_file() {
	// parse the text file into a string stream
	while (!in_file.eof()) {
		getline(in_file, a_string);
		a_stream << a_string;
		a_stream << " ";
	}
}

/* *********************************************************************
Function Name: read_from_file
Purpose: to read serialized data
Parameters:
Human* p1 - human player
Computer* computer - computer player
Board* the_board - the board object
int nummoves and int score passed by reference
Return Value: void
Local Variables:
stringstream a_stream and string a_string used to parse the text file
in_file is fstream used to open the text file
one_to_far boolean value which moderates cin.ignore();
a_char used to recieve return value from read_next_play()
Algorithm:
Ask user for filename and try to open the file
Once open parse each line into a_stream

Assistance Received: none
********************************************************************* */
void Serialization::read_from_file(Human* p1, Computer* computer, Board* the_board, int &nummoves, int &score) {
	filename = get_file_name();
	if (filename.substr(filename.size() - 4, filename.size() - 1).compare(".txt") != 0) {
		filename.append(".txt");
	}
	in_file.open(filename);
	while (in_file.is_open() == false) {
		filename = get_file_name();
		if (filename.substr(filename.size() - 4, filename.size() - 1).compare(".txt") != 0) {
			filename.append(".txt");
		}
		in_file.open(filename);
	}

	parse_file();
	
	// one too far checks for blank input and provides a measuring stick in case we parse too far
	one_too_far = false;

	// read the tournament score into the variable  score
	read_score(score);

	// read the round number into nummoves and set the center based on the round number
	read_nummoves(nummoves);
	the_board->set_center(nummoves);

	// read the computer and human hands and scores into the objects passed
	read_player_hand(computer);
	read_player_hand(p1);

	// read the board layout and the boneyard and store them in the board
	read_layout(the_board);
	read_boneyard(the_board);

	// read if last player passed
	read_last_passed();

	// read which player plays next
	a_char = read_next_play(p1,computer, the_board);

	// human plays next
	if (toupper(a_char) == 'H') {
		p1->set_player_move(true);
		p1->set_passed(false);
		computer->set_player_move(false);
		computer->set_passed(last_player_passed);
	}

	// computer plays next
	else if(toupper(a_char) == 'C'){
		computer->set_player_move(true);
		computer->set_passed(false);
		p1->set_player_move(false);
		p1->set_passed(last_player_passed);
	}
	else {
		do {
			if (p1->has_tile(the_board->get_center())) {
				p1->set_player_move(true);
				p1->set_passed(false);
				computer->set_player_move(false);
				computer->set_passed(last_player_passed);
			}
			else if (computer->has_tile(the_board->get_center())) {
				computer->set_player_move(true);
				computer->set_passed(false);
				p1->set_player_move(false);
				p1->set_passed(last_player_passed);
			}
			else {
				cout << "\nNeither player has the engine, you have to draw\n";
				system("pause");
				p1->fill_hand(the_board->get_top_n(1));
				computer->fill_hand(the_board->get_top_n(1));
			}
		} while (!(p1->has_tile(the_board->get_center()) || computer->has_tile(the_board->get_center())));
	}
}

/* *********************************************************************
Function Name: print_just_hand
Purpose: to print tiles from hand into a_stream
Parameters:
Hand* a_hand - hand to print
Return Value: void
Local Variables:
stringstream a_stream a stream to print to the file
temp a tile used to parse the hand
Algorithm:
parse through the hand and construct each printed tile in a_stream
Assistance Received: none
********************************************************************* */
void Serialization::print_just_hand(Hand* a_hand) {
	// create a blank stream
	a_stream.str("");

	// go through the hand and print each tile to the stream
	for (int i = 0; i < a_hand->size(*a_hand->get_hand()); i++) {
		temp = a_hand->at(i);
		out_file << temp.get_side_left();
		out_file << "-";
		out_file << temp.get_side_right();
		out_file << " ";
	}
}

/* *********************************************************************
Function Name: print_just_baord
Purpose: to print tiles from vector into a_stream
Parameters:
vector<Tile> a_vec vector to parse through
Return Value: void
Local Variables:
stringstream a_stream a stream to print to the file
Algorithm:
parse through the vector and construct each printed tile in a_stream as
well as 'L' and 'R' representing left and right ends of the board
Assistance Received: none
********************************************************************* */
void Serialization::print_just_board(vector<Tile> a_vec) {
	// create a stream for the tiles in the board and print those tiles to the stream
	out_file << "L ";
	for (int i = 0; i < a_vec.size(); i++) {
		out_file << a_vec.at(i).get_side_left();
		out_file << "-";
		out_file << a_vec.at(i).get_side_right();
		out_file << " ";
	}
	out_file << "R";
}

/* *********************************************************************
Function Name: print_just_boneyard
Purpose: to print tiles from stack into a_stream
Parameters:
stack<Tile> pile a stack of tiles to print
Return Value: void
Local Variables:
stringstream a_stream a stream to print to the file
Algorithm:
parse through the stack and construct each printed tile in a_stream
until the stack is empty
Assistance Received: none
********************************************************************* */
void Serialization::print_just_boneyard(stack<Tile> pile) {
	// create a stream for the tiles in the boneyard and keep pushing into there until there is nothing left in the boneyard
	while (pile.empty() == false) {
		out_file << pile.top().get_side_left();
		out_file << "-";
		out_file << pile.top().get_side_right();
		out_file << " ";
		pile.pop();
	}
}

/* *********************************************************************
Function Name: print_to_file
Purpose: to serialize the board
Parameters:
int score - tournament score, int nummmoves - round number, int
human_score - human player score
bool human_move - whether its the human's move
bool human_passed - whether last player passed
Return Value: void
Local Variables:
filename - string for the filename
out_file fstream - file to print to
Algorithm:
Open user specified file
print score to file
print round number to file
use print_just_hand to print the computer and then player hand to file
use print_just_board to print the layout to the file
use print_just_boneyard to print the boneyard to the file in order
use human_move, human_passed, and the get_passed() function to build
last 2 lines in the file
inform the user the file was saved and using global exit exit successfully
Assistance Received: none
********************************************************************* */
void Serialization::print_to_file(int score, int nummoves, Computer* computer, Hand* p1_hand, Board* a_board, int human_score, bool human_move, bool human_passed) {
	// create file to print to
	cout << "Enter name of text file (ex. \"test\" for \"test.txt\"): ";
	cin >> filename;
	if (filename.substr(filename.size() - 4, filename.size() - 1).compare(".txt") != 0) {
		filename.append(".txt");
	}
	out_file.open(filename);

	// print score to file
	out_file << "Tournament Score: " << score << '\n';

	// print round number to file
	out_file << "Round No.: " << nummoves << '\n' << '\n';
	a_stream.flush();
	// print computer hand and score to file
	out_file << "Computer: \n";
	
	out_file << "   Hand: "; print_just_hand(computer->get_hand()); out_file << '\n';
	out_file << "   Score: " << computer->get_score() << '\n' << '\n';

	// print human hand and score to file
	out_file << "Human: \n";
	out_file << "   Hand: "; print_just_hand(p1_hand); out_file << '\n';
	out_file << "   Score: " << human_score << '\n' << '\n';

	// print layout to file
	out_file << "Layout: \n";
	out_file << "  "; print_just_board(a_board->create_vector_to_print(nummoves)); out_file << '\n' << '\n';

	// print boneyard to file
	out_file << "Boneyard: \n";
	print_just_boneyard(a_board->get_boneyard());
	out_file << '\n' << '\n';

	//print previous player passed and next player to play
	out_file << "Previous Player Passed: ";
	if (human_move) {
		if (computer->get_passed()) {
			out_file << "Yes";
		}
		else {
			out_file << "No";
		}
		out_file << "\n\nNext Player: Human";
	}
	else {
		if (human_passed) {
			out_file << "Yes";
		}
		else {
			out_file << "No";
		}
		out_file << "\n\nNext Player: Computer";
	}

	// tell user it worked
	cout << "File saved to " << filename << ", till later\n";
	system("pause");

	// global scope exit with EXIT_SUCCESS
	::exit(EXIT_SUCCESS);
}