/*
 * dropfour-text.cpp: the text version of Drop Four
 *
 * Copyright (C) 2005 Peter Kirby.
 * E-mail Peter Kirby at gmail (peterkirby) or at www.peterkirby.com.
 *
 * "Drop Four" is a clone of the "Connect Four" (tm) of Milton Bradley.
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
 */

/*
 * Drop Four: general design by Peter Kirby
 *
 * This is written in C++.  I wrote a previous version in QBasic, but it was
 * on the slow side at higher difficulty levels.  This is an attempt to
 * optimize the Artificial Intelligence of the program.  The graphics are
 * non-existent at this point and could certainly be added.  The interface
 * functions can be changed (in ioface.cpp) without any change to board.cpp.
 *
 * Well, I did create a graphical GUI using the Windows API functions;
 * however, I am not satisfied with having a Windows-only program.  Therefore
 * this program will be designed to use wxWidgets.  The text interface is
 * primarily for those wishing to test out the AI while the wxWidgets GUI
 * is being developed.  The files board.cpp and board.h *must* remain exactly
 * the same in both the text version and the graphical version.
 *
 * To avoid long lines, use tabs width 4 or less; however, the tabbing should
 * be consistent at any width. A sort of Hungarian is used to indicate what
 * the variables do (whether they are arrays, or indexes, and so on).
 *
 * Further comments are dispersed throughout the source code.
 */

#include <iostream>
using namespace std;
#include <time.h>
#include <stdlib.h>
#include "ioface.h"
#include "../board/board.h"
using namespace DropFour;

int main()
{
	Board board;
	int rgBoardPos[ Board::mconst_posLim ];
	clock_t clkBefore, clkAfter;

	init();

	if ( askfirst() )
	{
		board.setHumanFirst();
	}
	else
	{
		board.setComputerFirst();
	}
	
	board.setDifficulty( askdifficulty() );

	board.getBoardState( rgBoardPos );
	display( rgBoardPos );

	while (!board.isGameOver())
	{
		if ( board.isComputerTurn() )
		{
			clkBefore = clock();
			board.takeComputerTurn();
			clkAfter = clock();
			cout << endl << "The computer took ";
			cout << ( clkAfter - clkBefore ) / (double)CLOCKS_PER_SEC;
			cout << " seconds to make its decision." << endl;
		}
		else
		{
			while ( board.takeHumanTurn( askmove() ) == Board::mconst_colNil )
				; // loop until a valid move is entered
				  // even though askmove() already validates input
		}

		board.getBoardState( rgBoardPos );
		display( rgBoardPos );
	}

	endgame( board.isComputerWin() ? 1 : ( board.isHumanWin() ? -1 : 0 ) );

	return EXIT_SUCCESS;
}
