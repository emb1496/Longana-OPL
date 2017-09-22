#include "Help.h"
Help::Help() {
	while (!my_vec.empty()) {
		my_vec.pop_back();
	}
}

Help::Help(Hand* a_hand, vector<Tile> a_vec_to_print, bool last_passed)
{
	// returns a vector of tiles to play
	my_vec = Computer::best_tiles_to_play(a_hand);
	for (int i = 0; i < my_vec.size(); i++) {
		if (my_vec[i].isDouble()) {
			// play double on right side
			if (a_vec_to_print.at(a_vec_to_print.size()-1).get_side_right() == my_vec[i].get_side_left()) {
				cout << "\n\nYou could play "; my_vec[i].print(); cout << " to the right side\n\n";
				break;
			}
		}
		else {
			if (last_passed) {
				if (a_vec_to_print.at(a_vec_to_print.size() - 1).get_side_right() == my_vec[i].get_side_left() || a_vec_to_print.at(a_vec_to_print.size() - 1).get_side_right() == my_vec[i].get_side_left()) {
					cout << "\nYou could play "; my_vec[i].print(); cout << " to the right side\n";
				}
			}
			if (a_vec_to_print.at(0).get_side_left() == my_vec[i].get_side_left() || a_vec_to_print.at(0).get_side_left() == my_vec[i].get_side_right()) {
				cout << "\n\nYou could play "; my_vec[i].print(); cout << " to the left side\n\n";
				break;
			}
		}
		if (my_vec[i].isDouble()) {
			if (a_vec_to_print.at(0).get_side_left() == my_vec[i].get_side_left()) {
				cout << "\n\nYou could play "; my_vec[i].print(); cout << " to the left side\n\n";
				break;
			}
			if (last_passed) {
				if (a_vec_to_print.at(a_vec_to_print.size() - 1).get_side_right() == my_vec[i].get_side_left() || a_vec_to_print.at(a_vec_to_print.size() - 1).get_side_right() == my_vec[i].get_side_left()) {
					cout << "\nYou could play "; my_vec[i].print(); cout << " to the right side\n";
				}
			}
		}
	}
}