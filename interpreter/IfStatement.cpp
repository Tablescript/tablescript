/* IfStatement.cpp

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

#include "IfStatement.h"
#include "Expression.h"
#include "Block.h"
#include "Object.h"
#include "Error.h"
#include "Scope.h"

namespace TS
{

	// Constructor
	//
	ElseIf::ElseIf( Expression *test, Block *block )
		: test_( test ),
		block_( block )
	{
	}

	// Copy Constructor
	//
	ElseIf::ElseIf( const ElseIf &ei )
	{

		test_ = ei.test_->clone();
		block_ = ei.block_->clone();
	}

	// Destructor
	//
	ElseIf::~ElseIf()
	{

		delete test_;
		delete block_;
	}

	// clone()
	//
	ElseIf *ElseIf::clone() const
	{

		return new ElseIf( *this );
	}

	// getTest()
	//
	Expression *ElseIf::getTest() const
	{

		return test_;
	}

	// getBlock()
	//
	Block *ElseIf::getBlock() const
	{

		return block_;
	}

	// Constructor
	//
	IfStatement::IfStatement(
			int lineNumber,
			Expression *ifTest,
			Block *ifBlock,
			ElseIfList *elseifs,
			Block *elseBlock )
		: Statement( lineNumber ),
		ifTest_( ifTest ),
		ifBlock_( ifBlock ),
		elseifs_( elseifs ),
		elseBlock_( elseBlock )
	{
	}

	// Copy Constructor
	//
	IfStatement::IfStatement( const IfStatement &is )
		: Statement( is ),
		elseifs_( 0 ),
		elseBlock_( 0 )
	{

		ifTest_ = is.ifTest_->clone();
		ifBlock_ = is.ifBlock_->clone();
		if ( is.elseifs_ )
			elseifs_ = is.elseifs_->clone();
		if ( is.elseBlock_ )
			elseBlock_ = is.elseBlock_->clone();
	}

	// Destructor
	//
	IfStatement::~IfStatement()
	{

		delete ifTest_;
		delete ifBlock_;
		delete elseifs_;
		delete elseBlock_;
	}

	// clone()
	//
	Statement *IfStatement::clone() const
	{

		return new IfStatement( *this );
	}

	// execute()
	//
	// todo: tidy this up!
	int IfStatement::execute( Interpreter *interpreter, Scope *scope )
	{

		Object *testResult;

		// evaluate the if test expression
		testResult = ifTest_->evaluate( interpreter, scope ); // new reference
		if ( !testResult )
			return EXEC_FAIL; // error already set

		// if the result is non-zero...
		if ( testResult->isTrue() )
		{

			// clean up
			testResult->decRef();

			// create a new local scope
			Scope localScope( scope );

			// execute the if block
			return ifBlock_->execute( interpreter, &localScope );
		}

		// clean up
		testResult->decRef();

		// elseifs...
		ElseIfList::iterator i, iEnd = elseifs_->end();
		for ( i = elseifs_->begin(); i != iEnd; ++i )
		{

			ElseIf *elseif = *i;
			Expression *elseifTest = elseif->getTest();
			testResult = elseifTest->evaluate( interpreter, scope ); // new reference
			if ( !testResult )
				return EXEC_FAIL; // error already set

			if ( testResult->isTrue() )
			{

				// clean up
				testResult->decRef();

				// create a new local scope
				Scope localScope( scope );

				// execute the elseif block
				Block *elseifBlock = elseif->getBlock();
				return elseifBlock->execute( interpreter, &localScope );
			}

			// clean up
			testResult->decRef();
		}

		// create a new local scope
		Scope localScope( scope );

		// execute the else block
		return elseBlock_->execute( interpreter, &localScope );
	}
}

