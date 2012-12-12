/* TableEntry.cpp

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

#include "TableEntry.h"
#include "None.h"
#include "Expression.h"
#include "Block.h"
#include "Statement.h"
#include "Error.h"
#include "String.h"

namespace TS
{

	// Constructor
	//
	TableEntry::TableEntry(
			unsigned int low,
			unsigned int high,
			Block *pre,
			Expression *expr,
			Block *post )
		: low_( low ),
		high_( high ),
		pre_( pre ),
		expr_( expr ),
		post_( post )
	{
	}

	// Copy Constructor
	//
	TableEntry::TableEntry( const TableEntry &te )
		: low_( te.low_ ),
		high_( te.high_),
		pre_( 0 ),
		expr_( 0 ),
		post_( 0 )
	{

		if ( te.pre_ )
			pre_ = te.pre_->clone();
		if ( te.expr_ )
			expr_ = te.expr_->clone();
		if ( te.post_ )
			post_ = te.post_->clone();
	}

	// Destructor
	//
	TableEntry::~TableEntry()
	{

		delete pre_;
		delete expr_;
		delete post_;
	}

	// clone()
	//
	TableEntry *TableEntry::clone() const
	{

		return new TableEntry( *this );
	}

	// applies()
	//
	bool TableEntry::applies( unsigned int roll )
	{

		if ( high_ == 0 && roll == low_ )
			return true;
		if ( roll >= low_ && roll <= high_ )
			return true;
		return false;
	}

	// getUpper()
	//
	unsigned int TableEntry::getUpper() const
	{

		if ( high_ == 0 )
			return low_;

		return high_;
	}

	// evaluate()
	//
	Object *TableEntry::evaluate( Interpreter *interpreter, Scope *scope )
	{

		Object *result = new String; // new reference

		// handle a pre-expression block
		if ( pre_ )
		{

			int ret = pre_->execute( interpreter, scope );
			if ( Statement::isExecutionError( ret ) )
			{

				switch ( ret )
				{

				case EXEC_FAIL:
					// error message already set
					break;

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

				result->decRef();

				return 0;
			}
		}

		// evaluate entry expression
		if ( expr_ )
		{

			result->decRef();

			result = expr_->evaluate( interpreter, scope ); // new reference
			if ( !result )
				return 0;
		}

		// handle a post-expression block
		if ( post_ )
		{

			int ret = post_->execute( interpreter, scope );
			if ( Statement::isExecutionError( ret ) )
			{

				switch ( ret )
				{

				case EXEC_FAIL:
					// error message already set
					break;

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

				result->decRef();

				return 0;
			}
		}

		return result;
	}
}

