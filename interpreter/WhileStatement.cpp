/*

   WhileStatement.cpp

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

#include "WhileStatement.h"
#include "Expression.h"
#include "Block.h"
#include "Interpreter.h"
#include "Object.h"
#include "Error.h"

namespace TS
{

	// Constructor
	//
	WhileStatement::WhileStatement(
			int lineNumber,
			Expression *test,
			Block *block )
		: Statement( lineNumber ),
		test_( test ),
		block_( block )
	{
	}

	// Copy Constructor
	//
	WhileStatement::WhileStatement( const WhileStatement &ws )
		: Statement( ws )
	{

		test_ = ws.test_->clone();
		block_ = ws.block_->clone();
	}

	// Destructor
	//
	WhileStatement::~WhileStatement()
	{

		delete test_;
		delete block_;
	}

	// clone()
	//
	Statement *WhileStatement::clone() const
	{

		return new WhileStatement( *this );
	}

	// execute()
	//
	int WhileStatement::execute( Interpreter *interpreter, Scope *scope )
	{

		while ( 1 )
		{

			// evaluate the test
			Object *testResult = test_->evaluate( interpreter, scope ); // new reference
			if ( !testResult )
				return EXEC_FAIL; // error already set

			// if the test evaluated as false, end the iteration...
			if ( !testResult->isTrue() )
			{

				testResult->decRef();
				break;
			}

			testResult->decRef();

			// create a new local scope
			Scope localScope( scope );

			// ... otherwise, run the block
			int ret = block_->execute( interpreter, &localScope );
			if ( ret == EXEC_BREAK )
				break;

			if ( ret == EXEC_CONTINUE )
				continue;

			if ( ret != EXEC_SUCCESS )
				return ret; // error already set
		}

		return EXEC_SUCCESS;
	}
}

