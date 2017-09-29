/************************************************************
* Name:  Elliott Barinberg                                  *
* Project : Project 1 - Longana								*
* Class : CMPS 366 OPL										*
* Date : 9/20/17											*
************************************************************/
#ifndef HELP_H
#define HELP_H
#include "Hand.h"
#include "Board.h"
#include "stdafx.h"
#include "Computer.h"
using namespace std;
static class Help
{
public:
	// constructor 
	Help();

	// overloaded constructor->should be the only one used
	Help(Hand* a_hand, vector<Tile> a_vec, bool last_passed);

	// destructor
	~Help();
private:

	// printed is what tells computer if he should print whether or not it had no moves to play
	bool printed;

	// storage for best tile order
	vector<Tile> my_vec;
};
#endif