/* FunctionStatement.cpp

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

#include "FunctionStatement.h"
#include "Block.h"
#include "Function.h"
#include "Interpreter.h"
#include "Scope.h"

#include <iostream>

namespace TS
{

	// Constructor
	//
	FunctionStatement::FunctionStatement(
			int lineNumber,
			const std::string &name,
			StringList *fargs,
			Block *block )
		: Statement( lineNumber ),
		name_( name ),
		fargs_( fargs ),
		block_( block )
	{
	}

	// Copy Constructor
	//
	FunctionStatement::FunctionStatement( const FunctionStatement &fs )
		: Statement( fs ),
		name_( fs.name_ )
	{

		fargs_ = fs.fargs_->clone();
		block_ = fs.block_->clone();
	}

	// Destructor
	//
	FunctionStatement::~FunctionStatement()
	{

		delete fargs_;
		delete block_;
	}

	// getName()
	//
	std::string FunctionStatement::getName() const
	{

		return name_;
	}

	// clone()
	//
	Statement *FunctionStatement::clone() const
	{

		return new FunctionStatement( *this );
	}

	// execute()
	//
	int FunctionStatement::execute( Interpreter *interpreter, Scope *scope )
	{

		Function *function = new Function( name_, fargs_->clone(), block_->clone() ); // new reference
		scope->setLocalSymbol( name_, function ); // takes reference

		// clean up
		function->decRef();

		return EXEC_SUCCESS;
	}
}

