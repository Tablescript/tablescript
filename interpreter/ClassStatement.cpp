/* ClassStatement.cpp

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

#include "ClassStatement.h"
#include "Class.h"
#include "Interpreter.h"
#include "Scope.h"
#include "MethodMap.h"

#include <iostream>

namespace TS
{

	// Constructor
	//
	ClassStatement::ClassStatement(
			int lineNumber,
			const std::string &name,
			MethodMap *methodMap )
		: Statement( lineNumber ),
		name_( name ),
		methodMap_( methodMap )
	{
	}

	// Copy Constructor
	//
	ClassStatement::ClassStatement( const ClassStatement &cs )
		: Statement( cs ),
		name_( cs.name_ )
	{

		methodMap_ = cs.methodMap_->clone();
	}

	// Destructor
	//
	ClassStatement::~ClassStatement()
	{

		delete methodMap_;
	}

	// clone()
	//
	Statement *ClassStatement::clone() const
	{

		return new ClassStatement( *this );
	}

	// execute()
	//
	int ClassStatement::execute( Interpreter *interpreter, Scope *scope )
	{

		Class *classObject = new Class( name_, methodMap_->clone() ); // new reference

		// set constructor function into local symbol table
		scope->setLocalSymbol( name_, classObject ); // takes reference

		// clean up
		classObject->decRef();

		return EXEC_SUCCESS;
	}
}
