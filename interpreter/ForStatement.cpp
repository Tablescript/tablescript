/* ForStatement.cpp

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

#include "ForStatement.h"
#include "Expression.h"
#include "Block.h"
#include "Interpreter.h"
#include "Scope.h"
#include "List.h"
#include "Error.h"

namespace TS
{

	// Constructor
	//
	ForStatement::ForStatement(
			int lineNumber,
			char *identifier,
			Expression *expression,
			Block *block)
		: Statement( lineNumber ),
		identifier_( identifier ),
		expression_( expression ),
		block_( block )
	{
	}

	// Copy Constructor
	//
	ForStatement::ForStatement( const ForStatement &fs )
		: Statement( fs ),
		identifier_( fs.identifier_ )
	{

		expression_ = fs.expression_->clone();
		block_ = fs.block_->clone();
	}

	// Destructor
	//
	ForStatement::~ForStatement()
	{

		delete expression_;
		delete block_;
	}

	// clone()
	//
	Statement *ForStatement::clone() const
	{

		return new ForStatement( *this );
	}

	// execute()
	//
	int ForStatement::execute( Interpreter *interpreter, Scope *scope )
	{

		Object *listValue = expression_->evaluate( interpreter, scope ); // new reference
		if ( !listValue )
			return EXEC_FAIL; // erro already set

		List *list = dynamic_cast< List * >( listValue );
		if ( !list )
		{

			// clean up
			listValue->decRef();

			setRuntimeError( ERROR_FOR_EXPRESSION_MUST_BE_LIST );
			return EXEC_FAIL;
		}

		// create a new local scope
		Scope localScope( scope );

		for ( unsigned int i = 0; i < list->getLength(); ++i )
		{

			Object *element = list->getElementInt( i ); // new reference
			localScope.setLocalSymbol( identifier_, element ); // takes reference
            element->decRef();

			int ret = block_->execute( interpreter, &localScope );

			// handle breaks
			if ( ret == EXEC_BREAK )
				break;

			// handle continues
			if ( ret == EXEC_CONTINUE )
				continue;

			if ( ret != EXEC_SUCCESS )
			{

				// clean up
				listValue->decRef();

				return ret;
			}
		}

		// clean up
		listValue->decRef();

		return EXEC_SUCCESS;
	}
}

