/* Function.cpp

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

#include "Function.h"
#include "Block.h"
#include "List.h"
#include "Scope.h"
#include "Interpreter.h"
#include "None.h"
#include "Error.h"
#include "Statement.h"

#include <iostream>

namespace TS
{

	// Constructor
	//
	Function::Function( const std::string &name, std::vector< std::string > *fargs, Block *block )
		: name_( name ),
        fargs_( fargs ),
		block_( block )
	{
	}

	// Destructor
	//
	Function::~Function()
	{

		// FunctionStatement destructor will delete _fargs and _block
	}

	// isTrue()
	//
	bool Function::isTrue() const
	{

		return true;
	}

	// call()
	//
	// todo: move return value into caller? maybe?
	Object *Function::call( Interpreter *interpreter, Scope *scope, List *parameters, const std::string &callScope )
	{

		// check parameter list length
		if ( parameters->getLength() != fargs_->size() )
		{

			setRuntimeError( ERROR_FUNCTION_TAKES_X_PARAMETERS, name_.c_str(), fargs_->size(), parameters->getLength() );
			return 0;
		}

		// evaluate parameters and add to new scope
		for ( unsigned int i = 0; i < fargs_->size(); ++i )
		{

			Object *parameter = parameters->getElementInt( i ); // new reference
			scope->setLocalSymbol( ( *fargs_ )[ i ], parameter ); // takes reference
			parameter->decRef();
		}

		// execute block
		if ( block_->execute( interpreter, scope ) == EXEC_FAIL )
        {

            pushErrorContext( callScope + "::" + name_ );
			return 0; // error already set
        }

		return scope->getReturnValue(); // new reference
	}
}

