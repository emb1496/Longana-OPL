/************************************************************
* Name:  Elliott Barinberg                                  *
* Project : Project 1 - Longana								*
* Class : CMPS 366 OPL										*
* Date : 9/9/17												*
************************************************************/
#include "Human.h"
#include "Computer.h"
#include "Board.h"
#include "BoardView.h"
#include "Round.h"
#include "Tournament.h"
#include "Serialization.h"
#include <iostream>
using namespace std;

/* *********************************************************************

********************************************************************* */
int main() {
	Human *p1 = new Human;
	Computer *computer = new Computer;
	Board *the_board = new Board;
	Round *a_round = new Round;
	int nummoves = 0, score = 0;
	Tournament *game = new Tournament;
	Serialization *a_save = new Serialization(p1, computer, the_board, a_round, nummoves, score, game);
	return 0;
 }