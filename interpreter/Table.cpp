/* Table.cpp

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

#include "Table.h"
#include "Dice.h"
#include "TableEntry.h"
#include "Error.h"
#include "Scope.h"
#include "Interpreter.h"
#include "List.h"
#include "None.h"
#include "Integer.h"
#include "Block.h"
#include "Statement.h"

namespace TS
{

	// Constructor
	//
	Table::Table(
            const std::string &name,
			std::vector< std::string > *args,
			const std::string &dice,
			Block *block,
			std::list< TableEntry * > *elements )
		: name_( name ),
        args_( args ),
		dice_( dice ),
		block_( block ),
		elements_( elements )
	{
	}

	// Destructor
	//
	Table::~Table()
	{

		// TableStatement destructor will delete _args and _elements
	}

	// maxEntry()
	//
	unsigned int Table::maxEntry() const
	{

		unsigned int result = 0;
		std::list< TableEntry * >::iterator i, iEnd = elements_->end();
		for ( i = elements_->begin(); i != iEnd; ++i )
		{

			unsigned int upper = ( *i )->getUpper();
			if ( upper > result )
				result = upper;
		}

		return result;
	}

	// call()
	//
	Object *Table::call( Interpreter *interpreter, Scope *scope, List *parameters, const std::string &callScope )
	{

		// roll
		unsigned int roll;
		if ( dice_.size() != 0 )
			roll = rollDice( dice_ );
		else
			roll = rollDie( maxEntry() );

		// determine which entry applies
		TableEntry *entry = 0;
		std::list< TableEntry * >::iterator i, iEnd = elements_->end();
		for ( i = elements_->begin(); i != iEnd; ++i )
		{

			if ( ( *i )->applies( roll ) )
			{

				entry = ( *i );
				break;
			}
		}

		// make sure there is an applicable entry
		if ( !entry )
		{

			setRuntimeError( ERROR_NO_TABLE_ENTRY_FOR_X, roll );
            pushErrorContext( callScope + "::" + name_ );
			return 0;
		}

		// create a new local scope
		Scope localScope( scope );

		// add parameters to local scope
		for ( unsigned int j = 0; j < args_->size(); ++j )
		{

			Object *parameter = parameters->getElementInt( j ); // new reference
			localScope.setLocalSymbol( ( *args_ )[ j ], parameter ); // takes reference
			parameter->decRef();
		}

		// add roll to local scope
		Integer *rollValue = new Integer( roll ); // new reference
		localScope.setLocalSymbol( "ROLL", rollValue ); // takes reference
		rollValue->decRef();

		// run table block
		int ret = block_->execute( interpreter, &localScope );
		if ( Statement::isExecutionError( ret ) )
		{

			switch ( ret ) {

			case EXEC_BREAK:
				setRuntimeError( ERROR_BREAK_WITH_NO_LOOP );
				break;

			case EXEC_CONTINUE:
				setRuntimeError( ERROR_CONTINUE_WITH_NO_LOOP );
				break;

			case EXEC_RETURN:
				setRuntimeError( ERROR_RETURN_IN_TABLE );
				break;
			}

            pushErrorContext( callScope + "::" + name_ );
			return 0; // error already set
		}

		// apply entry
		Object *result = entry->evaluate( interpreter, &localScope ); // new reference
        if ( !result )
        {

            pushErrorContext( callScope + "::" + name_ );
            return 0; // error already set
        }

		return result;
	}

	// getElement()
	//
	Object *Table::getElement( Interpreter *interpreter, Scope *scope, Object *key )
	{

		Integer *intKey = dynamic_cast< Integer * >( key );
		if ( !intKey )
		{

			setRuntimeError( ERROR_INDEX_MUST_BE_INTEGER );
			return 0;
		}

		int keyValue = intKey->getValue();

		std::list< TableEntry * >::iterator i, iEnd = elements_->end();
		for ( i = elements_->begin(); i != iEnd; ++i )
		{

			if ( ( *i )->applies( keyValue ) )
				return ( *i )->evaluate( interpreter, scope ); // new reference
		}

		setRuntimeError( ERROR_INVALID_INDEX_X, keyValue );
		return 0;
	}
}

