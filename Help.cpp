/************************************************************
* Name:  Elliott Barinberg                                  *
* Project : Project 1 - Longana								*
* Class : CMPS 366 OPL										*
* Date : 9/21/17											*
************************************************************/
#include "Help.h"
Help::Help() {
	while (!my_vec.empty()) {
		my_vec.pop_back();
	}
	printed = false;
}

Help::Help(Hand* a_hand, vector<Tile> a_vec_to_print, bool last_passed)
{
	printed = false;
	// returns a vector of tiles to play
	my_vec = Computer::best_tiles_to_play(a_hand);
	for (int i = 0; i < my_vec.size(); i++) {
		if (my_vec[i].isDouble()) {
			// play double on right side
			if (a_vec_to_print.at(a_vec_to_print.size() - 1).get_side_right() == my_vec[i].get_side_left()) {
				cout << "\n\nYou could play "; my_vec[i].print(); cout << " to the right side\n\n";
				printed = true;
				break;
			}
		}
		else {
			if (last_passed) {
				if (a_vec_to_print.at(a_vec_to_print.size() - 1).get_side_right() == my_vec[i].get_side_left() || a_vec_to_print.at(a_vec_to_print.size() - 1).get_side_right() == my_vec[i].get_side_right()) {
					cout << "\nYou could play "; my_vec[i].print(); cout << " to the right side\n";
					printed = true;
					break;
				}
			}
			if (a_vec_to_print.at(0).get_side_left() == my_vec[i].get_side_left() || a_vec_to_print.at(0).get_side_left() == my_vec[i].get_side_right()) {
				cout << "\nYou could play "; my_vec[i].print(); cout << " to the left side\n";
				printed = true;
				break;
			}
		}
		if (my_vec[i].isDouble()) {
			if (a_vec_to_print.at(0).get_side_left() == my_vec[i].get_side_left()) {
				cout << "\nYou could play "; my_vec[i].print(); cout << " to the left side\n";
				printed = true;
				break;
			}
			if (last_passed) {
				if (a_vec_to_print.at(a_vec_to_print.size() - 1).get_side_right() == my_vec[i].get_side_left() || a_vec_to_print.at(a_vec_to_print.size() - 1).get_side_right() == my_vec[i].get_side_left()) {
					cout << "\nYou could play "; my_vec[i].print(); cout << " to the right side\n";
					printed = true;
					break;
				}
			}
		}
	}
	if (!printed) {
		cout << "\nThere are no legal moves, you should pass\n";
	}
	else {
		cout << "\nThe computer sees this tile as the best tile you could legally play\n";
	}
}

Help::~Help() {
	while (!my_vec.empty()) {
		my_vec.pop_back();
	}
}


