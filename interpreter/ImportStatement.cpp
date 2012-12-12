/* ImportStatement.cpp

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

#include "ImportStatement.h"
#include "Interpreter.h"
#include "Expression.h"
#include "String.h"
#include "Error.h"

namespace TS
{

	// Constructor
	//
	ImportStatement::ImportStatement( int lineNumber, Expression *module )
		: Statement( lineNumber ),
		module_( module )
	{
	}

	// Copy Constructor
	//
	ImportStatement::ImportStatement( const ImportStatement &is )
		: Statement( is )
	{

		module_ = is.module_->clone();
	}

	// Destructor
	//
	ImportStatement::~ImportStatement()
	{

		delete module_;
	}

	// clone()
	//
	Statement *ImportStatement::clone() const
	{

		return new ImportStatement( *this );
	}

	// execute()
	//
	int ImportStatement::execute( Interpreter *interpreter, Scope *scope )
	{

		// evaluate module name expression
		Object *value = module_->evaluate( interpreter, scope ); // new reference
		if ( !value )
			return EXEC_FAIL; // error already set

		// ensure module name evaluated to a string
		String *name = dynamic_cast< String * >( value ); // steals reference
		if ( !name )
		{

            // clean up
            value->decRef();

            setRuntimeError( "Module name must evaluate to a string." );
            return EXEC_FAIL;
        }

		// import module
        int result = EXEC_SUCCESS;
		if ( !interpreter->import( name->getValue() ) )
			result = EXEC_FAIL;

		// clean up
		name->decRef();

		return result;
	}
}

