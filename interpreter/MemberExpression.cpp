/* MemberExpression.cpp

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

#include "MemberExpression.h"
#include "List.h"
#include "Scope.h"
#include "Instance.h"
#include "LHSObject.h"
#include "Error.h"

#include <iostream>

namespace TS
{

	// Constructor
	//
	MemberExpression::MemberExpression( int lineNumber, Expression *base, const std::string &memberName )
		: Expression( lineNumber ),
		base_( base ),
		memberName_( memberName )
	{
	}

	// Copy Constructor
	//
	MemberExpression::MemberExpression( const MemberExpression &ce )
		: Expression( ce )
	{

		base_ = ce.base_->clone();
		memberName_ = ce.memberName_;
	}

	// Destructor
	//
	MemberExpression::~MemberExpression()
	{

		delete base_;
	}

	// clone()
	//
	Expression *MemberExpression::clone() const
	{

		return new MemberExpression( *this );
	}

    // getInstance_()
    //
    Instance *MemberExpression::getInstance_( Interpreter *interpreter, Scope *scope )
    {

        // evaluate the expression to get the instance
        Object *baseValue = base_->evaluate( interpreter, scope ); // new reference
        if ( !baseValue )
            return 0; // error already set

        // make sure it's actually an instance
        Instance *instance = dynamic_cast< Instance * >( baseValue );
        if ( !instance )
        {

            setRuntimeError( ERROR_EXPRESSION_NOT_INSTANCE );
            return 0;
        }

        return instance;
    }

	// evaluate()
	//
	Object *MemberExpression::evaluate_( Interpreter *interpreter, Scope *scope )
	{

        Instance *instance = getInstance_( interpreter, scope ); // new reference
        if ( !instance )
            return 0; // error already set

		Object *result = instance->getMember( memberName_ ); // new reference

		// clean up
		instance->decRef();

		return result;
	}

    // evaluateAsLHS()
    //
    LHSObject *MemberExpression::evaluateAsLHS( Interpreter *interpreter, Scope *scope )
    {

        Instance *instance = getInstance_( interpreter, scope ); // new reference
        if ( !instance )
            return 0; // error already set

        return new LHSMember( instance, memberName_ ); // takes reference
    }
}

