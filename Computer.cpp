/************************************************************
* Name:  Elliott Barinberg                                  *
* Project : Project 1 - Longana								*
* Class : CMPS 366 OPL										*
* Date : 9/9/17												*
************************************************************/
#include "Computer.h"

Computer::Computer() {
	while (!best_play_order.empty()) {
		best_play_order.pop_back();
	}
	has_legal_move = false;
	num = 0;
	let = '\0';
}


// this will return the tiles we desire to play at location 0->N where N is size
vector<Tile> Computer::best_tiles_to_play(Hand* a_hand) {
	vector<Tile> a_vec_to_return;
	vector<int> left_tiles;
	vector<int> right_tiles;
	while (!right_tiles.empty()) {
		right_tiles.pop_back();
	}
	while (!left_tiles.empty()) {
		left_tiles.pop_back();
	}
	while (!a_vec_to_return.empty()) {
		a_vec_to_return.pop_back();
	}
	for (int i = 0; i < 7; i++) {
		left_tiles.push_back(0);
	}
	for (int i = 0; i < a_hand->size(); i++) {
		a_vec_to_return.push_back(a_hand->get_hand()->at(i));
		switch (a_vec_to_return[i].get_side_right()) {
		case 0: 
			left_tiles[0]++;
			break;
		case 1:
			left_tiles[1]++;
			break;
		case 2:
			left_tiles[2]++;
			break;
		case 3:
			left_tiles[3]++;
			break;
		case 4:
			left_tiles[4]++;
			break;
		case 5:
			left_tiles[5]++;
			break;
		case 6:
			left_tiles[6]++;
			break;
		}
		switch (a_vec_to_return[i].get_side_left()) {
		case 0:
			left_tiles[0]++;
			break;
		case 1:
			left_tiles[1]++;
			break;
		case 2:
			left_tiles[2]++;
			break;
		case 3:
			left_tiles[3]++;
			break;
		case 4:
			left_tiles[4]++;
			break;
		case 5:
			left_tiles[5]++;
			break;
		case 6:
			left_tiles[6]++;
			break;
		}
	}
	for (int i = 0; i < a_hand->size(); i++) {
		right_tiles.push_back(left_tiles[a_vec_to_return[i].get_side_left()] + left_tiles[a_vec_to_return[i].get_side_right()]);
	}
	for (int i = 0; i < a_hand->size()-1; i++) {
		for (int j = 0; j < a_hand->size() - i - 1; i++) {
			if (right_tiles[j] < right_tiles[j + 1]) {
				std::swap(right_tiles.at(j), right_tiles.at(j + 1));
				std::swap(a_vec_to_return[j], a_vec_to_return[j + 1]);
			}
		}
	}
	
	return a_vec_to_return;
}

/* *************************************************************************************

************************************************************************************* */
bool Computer::play_tile(Tile* play_tile, int left_end, int right_end, Board* a_board, bool last_played) {
	if (play_tile->get_side_left() == play_tile->get_side_right()) {
		if (play_tile->get_side_left() == left_end) {
			cout << "\nComputer moves tile ";	play_tile->print();	cout << " to the left side" << endl;
			a_board->add_to_left(*play_tile);
			Player::remove_tile(*play_tile);
			return true;
		}
	}
	else if (last_played && ((play_tile->get_side_left() == left_end) || (play_tile->get_side_right()==left_end))) {
		Player::remove_tile(*play_tile);
		a_board->add_to_left(*play_tile);
		cout << "\nComputer moves tile "; play_tile->print(); cout << " to the left side" << endl;
		return true;
	}
	else if (play_tile->get_side_right() == right_end || play_tile->get_side_left() == right_end) {
		Player::remove_tile(*play_tile);
		a_board->add_to_right(*play_tile);
		cout << "\nComputer moves tile ";	play_tile->print();	cout << " to the right side" << endl;
		return true;
	}
	if (play_tile->get_side_left() == play_tile->get_side_right()) {
		if (play_tile->get_side_left() == right_end) {
			cout << "\nComputer moves tile ";	play_tile->print();	cout << "to the right side" << endl;
			a_board->add_to_right(*play_tile);
			Player::remove_tile(*play_tile);
			return true;
		}
	}
	return false;
}


bool Computer::has_a_legal_move(bool last_moved, int left_end, int right_end, Hand* a_hand) {
	for (int i = 0; i < a_hand->size(); i++) {
		if (last_moved) {
			if (left_end == a_hand->at(i).get_side_left() || left_end == a_hand->at(i).get_side_right()) {
				return true;
			}
		}
		if (a_hand->at(i).get_side_left() == a_hand->at(i).get_side_right()) {
			// tile same number both sides
			if (left_end == a_hand->at(i).get_side_left() || right_end == a_hand->at(i).get_side_left()) {
				return true;
			}
		}
		else if (right_end == a_hand->at(i).get_side_left() || right_end == a_hand->at(i).get_side_right()) {
			return true;
		}
	}
	return false;
}
/* *********************************************************************

********************************************************************* */
void Computer::play(int boneyard_size, int left_end, int right_end, Board* a_board, bool last_moved) {
	if (Player::get_player_move() == false) {
		return;
	}
	num = 1;
	let = 'a';
	has_legal_move = has_a_legal_move(last_moved, left_end, right_end, Player::get_hand());
	if (has_legal_move) {
		Player::set_passed(false);
		while (!best_play_order.empty()) {
			best_play_order.pop_back();
		}
		// gets list of tiles with best ones to move at 0 and worst at the end
		best_play_order = best_tiles_to_play(Player::get_hand());
		for (int i = 0; i < best_play_order.size(); i++) {
			if (play_tile(&best_play_order[i], left_end, right_end, a_board, last_moved)) {
				break;
			}
		}
	}
	else {
		if (boneyard_size > 0) {
			cout << "\nNo legal moves, computer must draw a tile\n" << endl;
			Player::fill_hand(a_board->get_top_n(1));
			Player::set_passed(true);
		}
		else {
			cout << "\nNo legal moves, stock is empty, human's turn to play\n" << endl;
			Player::set_passed(true);
		}
	}
	Player::set_player_move(false);
}

bool Computer::is_human() { return false; }