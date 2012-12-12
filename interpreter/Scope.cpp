/*

   Scope.cpp

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

#include "Scope.h"
#include "None.h"

#include <iostream>

namespace TS
{

	// Constructor
	//
	Scope::Scope( Scope *parentScope )
		: parentScope_( parentScope )
	{

		// initialize return value
		none->addRef();
		returnValue_ = none;
	}

	// Destructor
	//
	Scope::~Scope()
	{

		returnValue_->decRef();
	}

	// recursiveSetSymbol_()
	//
	bool Scope::recursiveSetSymbol_( const std::string &name, Object *value )
	{

        // is the symbol already set in this scope?
        std::map< std::string, Object * >::const_iterator i = symbols_.find( name );
        if ( i != symbols_.end() )
        {

			setLocalSymbol( name, value );
            return true;
        }

        // is there a parent scope to check?
		if ( parentScope_ )
			return parentScope_->recursiveSetSymbol_( name, value );

        // otherwise, indicate that we were unable to set it
		return false;
	}

	// setSymbol()
	//
	void Scope::setSymbol( const std::string &name, Object *value )
	{

        // start the recursive check to see if the symbol is already define, and if
        //  it isn't, set it in this scope
		if ( !recursiveSetSymbol_( name, value ) )
			setLocalSymbol( name, value );
	}

	// setLocalSymbol()
	//
	void Scope::setLocalSymbol( const std::string &name, Object *value )
	{

        std::map< std::string, Object * >::iterator i = symbols_.find( name );
        if ( i != symbols_.end() )
            i->second->decRef();

        value->addRef();
		symbols_[ name ] = value;
	}

	// getSymbol()
	//
	Object *Scope::getSymbol( const std::string &name ) const
	{

        // is the symbol in thie scope?
        std::map< std::string, Object * >::const_iterator i = symbols_.find( name );
        if ( i != symbols_.end() )
        {

            Object *result = i->second;
            result->addRef();

            return result;
        }

        // is there a parent scope to check?
        if ( parentScope_ )
            return parentScope_->getSymbol( name );

        // otherwise, indicate that no such symbol exists
		return 0;
	}

	// setReturnValue()
	//
	void Scope::setReturnValue( Object *value )
	{

		value->addRef(); // take reference

		returnValue_ = value;
	}

	// getReturnValue()
	//
	Object *Scope::getReturnValue() const
	{

		returnValue_->addRef(); // new reference

		return returnValue_;
	}
}

