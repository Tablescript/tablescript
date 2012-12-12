/* LHSObject.cpp

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

#include "LHSObject.h"
#include "Interpreter.h"
#include "Scope.h"
#include "Instance.h"
#include <iostream>

namespace TS
{

	// Constructor
	//
	LHSObject::LHSObject()
	{
	}

	// Destructor
	//
	LHSObject::~LHSObject()
	{
	}

	// Constructor
	//
	LHSIdentifier::LHSIdentifier( const std::string &identifier )
		: identifier_( identifier )
	{
	}

	// Destructor
	//
	LHSIdentifier::~LHSIdentifier()
	{
	}

	// evaluate()
	//
	Object *LHSIdentifier::evaluate( Interpreter *interpreter, Scope *scope )
	{

		return scope->getSymbol( identifier_ ); // new reference
	}

	// assign()
	//
	bool LHSIdentifier::assign( Interpreter *interpreter, Scope *scope, Object *value )
	{

		scope->setSymbol( identifier_, value ); // takes reference

		return true;
	}

	// Constructor
	//
	LHSElement::LHSElement( Object *subject, Object *key )
		: subject_( subject ), // stolen reference
		key_( key ) // stolen reference
	{
	}

	// Destructor
	//
	LHSElement::~LHSElement()
	{

		// clean up
		subject_->decRef();
		key_->decRef();
	}

	// evaluate()
	//
	Object *LHSElement::evaluate( Interpreter *interpreter, Scope *scope )
	{

		return subject_->getElement( scope, key_ ); // new reference
	}

	// assign()
	//
	bool LHSElement::assign( Interpreter *interpreter, Scope *scope, Object *value )
	{

		if ( !subject_->setElement( key_, value ) ) // takes reference
			return false;

		return true;
	}

    // Constructor
    //
    LHSMember::LHSMember( Instance *instance, const std::string &memberName )
        : instance_( instance ),
        memberName_( memberName )
    {
    }

    // Destructor
    //
    LHSMember::~LHSMember()
    {

        // clean up
        instance_->decRef();
    }

    // evaluate()
    //
    Object *LHSMember::evaluate( Interpreter *interpreter, Scope *scope )
    {

        return instance_->getMember( memberName_ ); // new reference
    }

    // assign()
    //
    bool LHSMember::assign( Interpreter *interpreter, Scope *scope, Object *value )
    {

        instance_->setMember( memberName_, value ); // takes reference

        return true;
    }
}

