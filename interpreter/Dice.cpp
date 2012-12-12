/* Dice.cpp

   TableScript
   Copyright (C) 2003 Jamie Hale

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include "Dice.h"
#include <vector>
#include <algorithm>

namespace TS
{

	unsigned const int ROLLERROR = ( unsigned int ) -1;

	// rollDice()
	//
	unsigned int rollDice( const std::string &dice )
	{

		unsigned int i;
		std::string countString;
		std::string dieString;
		std::string dropLowString;
		std::string dropHighString;

		int state = 0;
		for ( i = 0; i < dice.size(); ++i )
		{

			char c = dice[ i ];

			switch ( state )
			{

			// collecting count
			case 0:
				if ( c == 'd' || c == 'D' )
					state = 1;
				else
					countString += c;
				break;

			// collecting die
			case 1:
				if ( c == 'l' || c == 'L' )
					state = 2;
				else
					if ( c == 'h' || c == 'H' )
						state = 3;
					else
						dieString += c;
				break;

			// collecting drop low dice count
			case 2:
				if ( c == 'h' || c == 'H' )
					state = 3;
				else
					dropLowString += c;
				break;

			case 3:
				dropHighString += c;
				break;

			}
		}

		// make sure we've seen a D - we will always have a D in the string from the
		//  parser
		if ( state == 0 )
			return ROLLERROR;

		// get the roll count
		unsigned int count = 1;
		if ( !countString.empty() )
			count = atoi( countString.c_str() );

		// determine which die
		if ( dieString.empty() )
			return ROLLERROR;
		unsigned int die = atoi( dieString.c_str() );

		// drop how many low dice?
		unsigned int dropLow = 0;
		if ( !dropLowString.empty() )
			dropLow = atoi( dropLowString.c_str() );

		// drop how many high dice?
		unsigned int dropHigh = 0;
		if ( !dropHighString.empty() )
			dropHigh = atoi( dropHighString.c_str() );

		// sanity check - don't get rid of more than we're rolling!
		if ( dropLow + dropHigh > count )
			return ROLLERROR;

		// roll the dice
		std::vector< unsigned int > rolls;
		for( i = 0; i < count; ++i )
			rolls.push_back( rollDie( die ) );

		// sort the results
		std::sort( rolls.begin(), rolls.end() );

		// find the proper sum
		unsigned int sum = 0;
		for ( i = dropLow; i < ( count - dropHigh ); ++i )
			sum += rolls[ i ];

		return sum;
	}

	// rollDie()
	//
	unsigned int rollDie( unsigned int max )
	{

		return ( unsigned int ) ( ( rand() / ( float ) RAND_MAX ) * max ) + 1;
	}
}
