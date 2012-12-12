/* Block.cpp

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

#include "Block.h"
#include "Statement.h"

namespace TS
{

	// Default Constructor
	//
	Block::Block()
	{
	}

	// Copy Constructor
	//
	Block::Block( const Block &b )
	{

		std::list< Statement * >::const_iterator i, iEnd = b.statements_.end();
		for ( i = b.statements_.begin(); i != iEnd; ++i )
			statements_.push_back( ( *i )->clone() );
	}

	// Destructor
	//
	Block::~Block()
	{

		std::list< Statement * >::iterator i, iEnd = statements_.end();
		for ( i = statements_.begin(); i != iEnd; ++i )
			delete *i;
	}

	// clone()
	//
	Block *Block::clone() const
	{

		return new Block( *this );
	}

	// addStatement()
	//
	void Block::addStatement( Statement *s )
	{

		statements_.push_back( s );
	}

	// execute()
	//
	int Block::execute( Interpreter *interpreter, Scope *scope )
	{

		std::list< Statement * >::iterator i, iEnd = statements_.end();
		for ( i = statements_.begin(); i != iEnd; ++i )
		{

			int ret = ( *i )->execute( interpreter, scope );
			if ( ret != EXEC_SUCCESS )
				return ret; // error already set
		}

		return EXEC_SUCCESS;
	}
}

