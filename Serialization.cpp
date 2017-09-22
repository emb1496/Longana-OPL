#include "Serialization.h"
// variables used staticly
std::string Serialization::filename = "";
std::string Serialization::a_string = "";
std::ofstream Serialization::out_file;
std::stringstream Serialization::a_stream;
Tile Serialization::temp;

/* *********************************************************************
Function Name: SErialization
Purpose: Default constructor for serialization
Parameters:
none
Return Value: none
Local Variables:
none
Algorithm:
none
Assistance Received: none
********************************************************************* */
Serialization::Serialization() {

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
	a_char = 'f';
	while (toupper(a_char) != 'Y' && toupper(a_char) != 'N') {
		cout << "Would you like to load a game(y/n): ";
		getline(cin, my_string);
		a_char = my_string.at(0);
	}
	if (toupper(a_char) == 'Y') {
		read_from_file(p1, computer, the_board, nummoves, score);
		game = new Tournament(p1, computer, the_board, a_round, nummoves, score);
	}
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
void Serialization::read_score(int &score) {
	a_string = "a";
	while(a_string.compare("Score:")!=0) {
		a_stream >> a_string;
	}
	a_stream >> a_string;
	if (a_string.at(0) >= '0'&&a_string.at(0) <= '9') {
		score = atoi(a_string.c_str());
		one_too_far = false;
	}
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
	while(a_string.compare("No.:")!=0) {
		a_stream >> a_string;
	}
	a_stream >> a_string;
	if (a_string.at(0) >= '0' && a_string.at(0) <= '9') {
		nummoves = atoi(a_string.c_str());
		one_too_far = false;
	}
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

void Serialization::read_player_hand(Player* a_player) {
	a_string = " ";
	while(a_string.compare("Hand:") != 0) {
		a_stream >> a_string;
	}
	a_stream >> a_string;
	while (a_pile.empty() == false) {
		a_pile.pop();
	}
	while (toupper(a_string.at(0))!='S') {
		temp1 = new Tile;
		temp1->set_side_left(a_string.at(0) - 48);
		temp1->set_side_right(a_string.at(2) - 48);
		a_pile.push(*temp1);
		a_stream >> a_string;
		delete temp1;
	}
	a_player->fill_hand(a_pile);
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
	a_player->add_to_score(atoi(a_string.c_str()));
}

void Serialization::read_layout(Board* a_board) {
	while (a_vec.empty() == false) {
		a_vec.pop_back();
	}
	while (right_side.empty() == false) {
		right_side.pop();
	}
	while (left_side.empty() == false) {
		left_side.pop();
	}
	while(a_string.compare("L")!=0) {
		a_stream >> a_string;
	}
	a_stream >> a_string;
	while (toupper(a_string.at(0)) != 'R') {
		temp1 = new Tile;
		temp1->set_side_left(a_string.at(0) - 48);
		temp1->set_side_right(a_string.at(2) - 48);
		a_vec.push_back(*temp1);
		a_stream >> a_string;
		delete temp1;
	}
	while ((a_vec.at(a_vec.size()-1).get_side_left() != a_board->get_center().get_side_left()) || (a_vec.at(a_vec.size() - 1).get_side_right() != a_board->get_center().get_side_right())) {
		right_side.push(a_vec.at(a_vec.size() - 1));
		a_vec.pop_back();
	}
	a_vec.pop_back();
	while (a_vec.empty() ==false) {
		left_side.push(a_vec.at(a_vec.size() - 1));
		a_vec.pop_back();
	}
	while (right_side.empty() == false) {
		a_board->add_to_right(right_side.top(),0);
		right_side.pop();
	}
	while (left_side.empty() == false) {
		a_board->add_to_left(left_side.front(),0);
		left_side.pop();
	}
}

void Serialization::read_boneyard(Board* a_board) {
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
	while (toupper(a_string.at(0)) != 'P') {
		temp1 = new Tile;
		temp1->set_side_left(a_string.at(0) - 48);
		temp1->set_side_right(a_string.at(2) - 48);
		right_side.push(*temp1);
		a_stream >> a_string;
		delete temp1;
	}
	a_board->create_pile(right_side);
}

void Serialization::read_last_passed() {
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

Player* Serialization::read_next_play(Human* p1, Computer* p2, Board* the_board) {
	while(a_string.compare("Player:") != 0) {
		a_stream >> a_string;
	}
	if (a_stream >> a_string) {
		if (toupper(a_string.at(0)) == 'C') {
			p1->set_passed(last_player_passed);
			return p2;
		}
		else {
			p2->set_passed(last_player_passed);
			return p1;
			// human should play
		}
	}
	else {
		cout << "Error reading who plays next please enter (h/c) for human or computer: ";
		while (toupper(a_string.at(0)) != 'H' && toupper(a_string.at(0)) != 'C') {
			if (!one_too_far) {
				cin.ignore();
			}
			getline(cin, a_string);
		}
		if (toupper(a_string.at(0)) == 'C') {
			p1->set_passed(last_player_passed);
			return p2;
		}
		else {
			p2->set_passed(last_player_passed);
			return p1;
			// human should play
		}
	}
	
}

void Serialization::read_from_file(Human* p1, Computer* computer, Board* the_board, int &nummoves, int &score) {
	cout << "Enter filename: ";
	cin >> filename;
	in_file.open(filename);
	if (in_file.is_open() == false) {
		cerr << "File unable to open";
		return;
	}
	while (!in_file.eof()) {
		getline(in_file, a_string);
		a_stream << a_string;
		a_stream << " ";
	}
	one_too_far = false;
	read_score(score);
	read_nummoves(nummoves);
	the_board->set_center(nummoves);
	read_player_hand(computer);
	read_player_hand(p1);
	read_layout(the_board);
	read_boneyard(the_board);
	read_last_passed();
	a_player = read_next_play(p1,computer, the_board);
	if (a_player->is_human()) {
		p1->set_player_move(true);
		p1->set_passed(false);
		computer->set_player_move(false);
		computer->set_passed(last_player_passed);
	}
	else {
		computer->set_player_move(true);
		computer->set_passed(false);
		p1->set_player_move(false);
		p1->set_passed(last_player_passed);
	}
}

bool Serialization::want_to_save(char a_char) {
	a_char = 'f';
	while (toupper(a_char) != 'Y' && toupper(a_char) != 'N') {
		cout << "\n\nWould you like to save your game(y/n): ";
		cin >> a_char;
	}
	if (toupper(a_char) == 'Y') {
		return true;
	}
	else {
		return false;
	}
}

void Serialization::print_just_hand(Hand* a_hand) {
	a_stream.str("");
	for (int i = 0; i < a_hand->size(*a_hand->get_hand()); i++) {
		temp = a_hand->at(i);
		a_stream << temp.get_side_left();
		a_stream << "-";
		a_stream << temp.get_side_right();
		a_stream << " ";
	}
}

void Serialization::print_just_board(std::vector<Tile> a_vec) {
	a_stream.str("");
	a_stream << "L ";
	for (int i = 0; i < a_vec.size(); i++) {
		a_stream << a_vec.at(i).get_side_left();
		a_stream << "-";
		a_stream << a_vec.at(i).get_side_right();
		a_stream << " ";
	}
	a_stream << "R";
}

void Serialization::print_just_boneyard(std::stack<Tile> pile) {
	a_stream.str("");
	while (pile.empty() == false) {
		a_stream << pile.top().get_side_left();
		a_stream << "-";
		a_stream << pile.top().get_side_right();
		a_stream << " ";
		pile.pop();
	}
}

void Serialization::print_to_file(int score, int nummoves, Hand* computer_hand, Human* p1, Board* a_board, int computer_score, bool computer_move, bool computer_passed) {
	std::cout << "Enter name of text file (ex. \"test\" for \"test.txt\"): ";
	std::cin >> filename;
	filename.append(".txt");
	out_file.open(filename);
	out_file << "Tournament Score: " << score << '\n';
	out_file << "Round No.: " << nummoves << '\n' << '\n';

	out_file << "Computer: \n";
	print_just_hand(computer_hand);
	out_file << "   Hand: " << a_stream.str() << '\n';
	out_file << "   Score: " << computer_score << '\n' << '\n';

	out_file << "Human: \n";
	print_just_hand(p1->get_hand());
	out_file << "   Hand: " << a_stream.str() << '\n';
	out_file << "   Score: " << p1->get_score() << '\n' << '\n';

	out_file << "Layout: \n";
	print_just_board(a_board->create_vector_to_print(nummoves));
	out_file << "  " << a_stream.str() << '\n' << '\n';

	out_file << "Boneyard: \n";
	print_just_boneyard(a_board->get_stack());
	out_file << a_stream.str() << '\n' << '\n';

	out_file << "Previous Player Passed: ";
	if(computer_move) {
		if (p1->get_passed()) {
			out_file << "Yes";
		}
		else {
			out_file << "No";
		}
		out_file << "\n\nNext Player: Computer";
	}
	else {
		if (computer_passed) {
			out_file << "Yes";
		}
		else {
			out_file << "No";
		}
		out_file << "\n\nNext Player: Human";
	}
	::cout << "File saved, till later\n";
	::exit(EXIT_SUCCESS);
}

void Serialization::print_to_file(int score, int nummoves, Computer* computer, Hand* p1_hand, Board* a_board, int human_score, bool human_move, bool human_passed) {
	std::cout << "Enter name of text file (ex. \"test\" for \"test.txt\"): ";
	std::cin >> filename;
	filename.append(".txt");
	out_file.open(filename);
	out_file << "Tournament Score: " << score << '\n';
	out_file << "Round No.: " << nummoves << '\n' << '\n';

	out_file << "Computer: \n";
	print_just_hand(computer->get_hand());
	out_file << "   Hand: " << a_stream.str() << '\n';
	out_file << "   Score: " << computer->get_score() << '\n' << '\n';

	out_file << "Human: \n";
	print_just_hand(p1_hand);
	out_file << "   Hand: " << a_stream.str() << '\n';
	out_file << "   Score: " << human_score << '\n' << '\n';

	out_file << "Layout: \n";
	print_just_board(a_board->create_vector_to_print(nummoves));
	out_file << "  " << a_stream.str() << '\n' << '\n';

	out_file << "Boneyard: \n";
	print_just_boneyard(a_board->get_stack());
	out_file << a_stream.str() << '\n' << '\n';

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
	std::cout << "File saved, till later\n";
	::system("pause");
	::exit(EXIT_SUCCESS);
}