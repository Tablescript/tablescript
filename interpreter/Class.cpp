/* Class.cpp

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

#include "Class.h"
#include "Scope.h"
#include "MethodMap.h"
#include "Instance.h"
#include "Interpreter.h"
#include "Error.h"
#include "List.h"

#include <iostream>

namespace TS
{

	// Constructor
	//
	Class::Class( const std::string &className, MethodMap *methodMap )
		: className_( className ),
		methodMap_( methodMap )
	{


	}

	// Destructor
	//
	Class::~Class()
	{

        delete methodMap_;
	}

	// isTrue()
	//
	bool Class::isTrue() const
	{

		return true;
	}

	// call()
	//
	Object *Class::call( Interpreter *interpreter, Scope *scope, List *parameters, const std::string & )
	{

		Scope *instanceScope = new Scope( interpreter->getGlobalScope() );

        // execute all method statements into the instance scope
		MethodMap::iterator i, iEnd = methodMap_->end();
		for ( i = methodMap_->begin(); i != iEnd; ++i )
		{

			FunctionStatement *functionStatement = i->second;

			if ( functionStatement->execute( interpreter, instanceScope ) == EXEC_FAIL )
                return 0; // error already set
		}

        // create an instance of the class
		Instance *instance = new Instance( className_, instanceScope ); // new reference

        // call constructor
        Object *result = instance->callMethod( interpreter, "__init__", parameters );
        if ( !result )
        {

            // clean up
            instance->decRef();

            return 0; // error already set
        }

        // clean up
        result->decRef();

        return instance;
	}
}

