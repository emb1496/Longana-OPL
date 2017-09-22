#ifndef HELP_H
#define HELP_H
#include "Hand.h"
#include "Board.h"
#include "stdafx.h"
#include "Computer.h"
using namespace std;
class Help
{
public:
	Help();
	Help(Hand* a_hand, vector<Tile> a_vec, bool last_passed);
private:
	vector<Tile> my_vec;
};
#endif