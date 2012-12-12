/* Instance.cpp

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

#include "Instance.h"
#include "Scope.h"
#include "Error.h"

#include <iostream>

namespace TS
{

	// Constructor
	//
	Instance::Instance( std::string &className, Scope *scope )
		: className_( className ),
        scope_( scope )
	{
	}

	// Destructor
	//
	Instance::~Instance()
	{

		delete scope_;
	}

	// getMember()
	//
	Object *Instance::getMember( const std::string &memberName ) const
	{

        return scope_->getSymbol( memberName ); // new reference
	}

    // setMember()
    //
    void Instance::setMember( const std::string &memberName, Object *value )
    {

        scope_->setSymbol( memberName, value ); // takes reference
    }

    // callMethod()
    //
    Object *Instance::callMethod( Interpreter *interpreter, const std::string &methodName, List *parameters )
    {

        // get method object
        Object *method = scope_->getSymbol( methodName ); // new reference
        if ( !method )
        {

            setRuntimeError( ERROR_NO_METHOD_X, methodName.c_str() );
            return 0;
        }

        // set instance variable
        scope_->setLocalSymbol( "this", this ); // takes reference

        // call method
        Object *result = method->call( interpreter, scope_, parameters, className_ ); // new reference

        // clean up
        method->decRef();

        return result;
    }
}

