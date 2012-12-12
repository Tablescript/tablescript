/* Builtins.cpp

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

#include "Builtins.h"
#include "List.h"
#include "String.h"
#include "None.h"
#include "Integer.h"
#include "Float.h"
#include "Error.h"
#include "Map.h"
#include "Interpreter.h"
#include "Statement.h"

#include <iostream>

namespace TS
{

	// print()
	//
	Object *print( Interpreter *interpreter, Scope *scope, List *parameters )
	{

		if ( parameters->getLength() != 1 )
		{

			setRuntimeError( ERROR_FUNCTION_TAKES_X_PARAMETERS, "print", 1, parameters->getLength() );
			return 0;
		}

		Object *parameter = parameters->getElementInt( 0 ); // new reference

		// convert to string - relies on the fact that there is valid default
		//  behaviour for this call
		String *string = parameter->toString(); // new reference

		std::cout << string->getValue() << std::endl;

        // clean up
		parameter->decRef();
		string->decRef();

		none->addRef();
		return none;
	}

	// range()
	//
	Object *range( Interpreter *interpreter, Scope *scope, List *parameters )
	{

		if( parameters->getLength() != 1 )
		{

			setRuntimeError( ERROR_FUNCTION_TAKES_X_PARAMETERS, "range", 1, parameters->getLength() );
			return 0;
		}

		Object *parameter = parameters->getElementInt( 0 ); // new reference
		Integer *length = dynamic_cast< Integer * >( parameter ); // steals reference
		if ( !length )
		{

            // clean up
            parameter->decRef();

            setRuntimeError( ERROR_PARAMETER_X_MUST_BE_TYPE_Y, "range", 1, "integer" );
			return 0;
		}

		int l = length->getValue();
		List *result = new List( l ); // new reference
		for ( int i = 0; i < l; ++i )
        {

            Integer *element = new Integer( i ); // new reference
			result->setElementInt( i, element ); // takes reference
            element->decRef();
        }

        // clean up
        length->decRef();

		return result;
	}

	// len()
	//
	Object *len( Interpreter *interpreter, Scope *scope, List *parameters )
	{

		if ( parameters->getLength() != 1 )
		{

			setRuntimeError( ERROR_FUNCTION_TAKES_X_PARAMETERS, "len", 1, parameters->getLength() );
			return 0;
		}

		Object *parameter = parameters->getElementInt( 0 ); // new reference
		int length = parameter->getLength();

		Object *result = 0;
		if ( length != -1 )
			result = new Integer( length ); // new reference

        // clean up
		parameter->decRef();

		return result;
	}

	// append()
	//
	Object *append( Interpreter *interpreter, Scope *scope, List *parameters )
	{

		if ( parameters->getLength() != 2 )
		{

			setRuntimeError( ERROR_FUNCTION_TAKES_X_PARAMETERS, "append", 2, parameters->getLength() );
			return 0;
		}

		Object *parameter = parameters->getElementInt( 0 ); // new reference
		List *list = dynamic_cast< List * >( parameter ); // steals reference
		if ( !list )
		{

            // clean up
            parameter->decRef();

            setRuntimeError( ERROR_PARAMETER_X_MUST_BE_TYPE_Y, "apppend", 1, "list" );
			return 0;
		}

        Object *value = parameters->getElementInt( 1 ); // new reference
		list->append( value ); // takes reference

        // clean up
        list->decRef();
        value->decRef();

		none->addRef();
		return none;
	}

	// systemCall()
	//
	Object *systemCall( Interpreter *interpreter, Scope *scope, List *parameters )
	{

		if ( parameters->getLength() != 1 )
		{

			setRuntimeError( ERROR_FUNCTION_TAKES_X_PARAMETERS, "system", 1, parameters->getLength() );
			return 0;
		}

		Object *parameter = parameters->getElementInt( 0 ); // new reference
		String *string = parameter->toString(); // new reference

		int ret = system( ( string->getValue() ).c_str() );

        // clean up
		string->decRef();
		parameter->decRef();

		return new Integer( ret ); // new reference
	}

	// toInteger()
	//
	Object *toInteger( Interpreter *interpreter, Scope *scope, List *parameters )
	{

		if ( parameters->getLength() != 1 )
		{

			setRuntimeError( ERROR_FUNCTION_TAKES_X_PARAMETERS, "int", 1, parameters->getLength() );
			return 0;
		}

		Object *parameter = parameters->getElementInt( 0 ); // new reference
		Integer *result = parameter->toInteger(); // new reference

        // clean up
		parameter->decRef();

		return result;
	}

	// toFloat()
	//
	Object *toFloat( Interpreter *interpreter, Scope *scope, List *parameters )
	{

		if ( parameters->getLength() != 1 )
		{

			setRuntimeError( ERROR_FUNCTION_TAKES_X_PARAMETERS, "float", 1, parameters->getLength() );
			return 0;
		}

		Object *parameter = parameters->getElementInt( 0 ); // new reference
		Float *result = parameter->toFloat(); // new reference

        // clean up
		parameter->decRef();

		return result;
	}

	// toString()
	//
	Object *toString( Interpreter *interpreter, Scope *scope, List *parameters )
	{

		if ( parameters->getLength() != 1 )
		{

			setRuntimeError( ERROR_FUNCTION_TAKES_X_PARAMETERS, "string", 1, parameters->getLength() );
			return 0;
		}

		Object *parameter = parameters->getElementInt( 0 ); // new reference
		String *result = parameter->toString(); // new reference

        // clean up
		parameter->decRef();

		return result;
	}

	// keys()
	//
	Object *keys( Interpreter *interpreter, Scope *scope, List *parameters )
	{

		if ( parameters->getLength() != 1 )
		{

			setRuntimeError( ERROR_FUNCTION_TAKES_X_PARAMETERS, "keys", 1, parameters->getLength() );
			return 0;
		}

		Object *parameter = parameters->getElementInt( 0 ); // new reference
		Map *map = dynamic_cast< Map * >( parameter ); // steals reference
		if ( !map )
		{

            // clean up
            parameter->decRef();

            setRuntimeError( ERROR_PARAMETER_X_MUST_BE_TYPE_Y, "keys", 1, "map" );
			return 0;
		}

        Object *keys = map->getKeys(); // new reference

        // clean up
        map->decRef();

		return keys;
	}

	// hasKey()
	//
	Object *hasKey( Interpreter *interpreter, Scope *scope, List *parameters )
	{

		if ( parameters->getLength() != 2 )
		{

            setRuntimeError( ERROR_FUNCTION_TAKES_X_PARAMETERS, "hasKey", 2, parameters->getLength() );
			return 0;
		}

		Object *parameter = parameters->getElementInt( 0 ); // new reference
		Map *map = dynamic_cast< Map * >( parameter ); // steals reference
		if ( !map )
		{

            // clean up
            parameter->decRef();

            setRuntimeError( ERROR_PARAMETER_X_MUST_BE_TYPE_Y, "hasKey", 1, "map" );
			return 0;
		}

		parameter = parameters->getElementInt( 1 ); // new reference
		String *key = dynamic_cast< String * >( parameter ); // steals reference
		if ( !key )
		{

            // clean up
            map->decRef();
            parameter->decRef();

            setRuntimeError( ERROR_PARAMETER_X_MUST_BE_TYPE_Y, "hasKey", 2, "string" );
			return 0;
		}

		Object *result;
		if ( map->hasKey( key->getValue() ) )
			result = new Integer( 1 ); // new reference
		else
			result = new Integer( 0 ); // new reference

        // clean up
        map->decRef();
        key->decRef();

		return result;
	}

	// eval()
	//
	Object *eval( Interpreter *interpreter, Scope *scope, List *parameters )
	{

		if ( parameters->getLength() != 1 )
		{

            setRuntimeError( ERROR_FUNCTION_TAKES_X_PARAMETERS, "eval", 1, parameters->getLength() );
			return 0;
		}

		Object *parameter = parameters->getElementInt( 0 ); // new reference
		String *code = parameter->toString(); // new reference
		if ( !code )
		{

            // clean up
            parameter->decRef();

			return 0; // error already set
		}

		bool ret = interpreter->eval( code->getValue() );
		if ( !ret )
		{

            // clean up
            parameter->decRef();
			code->decRef();

			return 0; // error already set
		}

        // clean up
        parameter->decRef();
		code->decRef();

		none->addRef();
		return none;
	}

    // getType()
    //
	Object *getType( Interpreter *interpreter, Scope *scope, List *parameters )
	{

		if ( parameters->getLength() != 1 )
		{

            setRuntimeError( ERROR_FUNCTION_TAKES_X_PARAMETERS, "type", 1, parameters->getLength() );
			return 0;
		}

		Object *parameter = parameters->getElementInt( 0 ); // new reference
		String *result = new String( parameter->getTypeName() ); // new reference

        // clean up
		parameter->decRef();

		return result;
	}

	// initializeBuiltins()
	//
	void initializeBuiltins( Scope *globalScope )
	{

		globalScope->setLocalSymbol( "print",  new AddInFunction( print ) );
		globalScope->setLocalSymbol( "range",  new AddInFunction( range ) );
		globalScope->setLocalSymbol( "len",    new AddInFunction( len ) );
		globalScope->setLocalSymbol( "append", new AddInFunction( append ) );
		globalScope->setLocalSymbol( "system", new AddInFunction( systemCall ) );
		globalScope->setLocalSymbol( "int",    new AddInFunction( toInteger ) );
		globalScope->setLocalSymbol( "float",  new AddInFunction( toFloat ) );
		globalScope->setLocalSymbol( "str",    new AddInFunction( toString ) );
		globalScope->setLocalSymbol( "keys",   new AddInFunction( keys ) );
		globalScope->setLocalSymbol( "hasKey", new AddInFunction( hasKey ) );
		globalScope->setLocalSymbol( "eval",   new AddInFunction( eval ) );
		globalScope->setLocalSymbol( "type",   new AddInFunction( getType ) );
	}

	// Constructor
	//
	AddInFunction::AddInFunction( AddInFunctionPtr entry )
		: entry_( entry )
	{
	}

	// Destructor
	//
	AddInFunction::~AddInFunction()
	{
	}

	// isTrue()
	//
	bool AddInFunction::isTrue() const
	{

		return true;
	}

	// call()
	//
	Object *AddInFunction::call( Interpreter *interpreter, Scope *scope, List *parameters, const std::string &callScope )
	{

		return entry_( interpreter, scope, parameters );
	}
}
