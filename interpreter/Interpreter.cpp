/*

   Interpreter.cpp

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

#include "Interpreter.h"
#include "Block.h"
#include "Translate.h"
#include "Scope.h"
#include "Builtins.h"
#include "None.h"
#include "Statement.h"
#include "List.h"
#include "String.h"
#include "Error.h"

#include <iostream>
#include <dlfcn.h>
#include <time.h>
#include <sstream>

extern "C" FILE *yyin;
extern "C" int yyparse();
extern "C" struct PList *ts_parseTree;
extern "C" char *ts_filename;
extern "C" void ts_setFilename(const char *filename);
extern "C" void listDelete(struct PList *l);

namespace TS
{

	// Constructor
	//
	Interpreter::Interpreter( int argc, char *argv[] )
		: globalScope_( 0 )
	{

		// initialize the one and only None object
		//None::initialize();

		// add all built-in functions to globals
		initializeBuiltins( &globalScope_ );

		// initialize random number generator
		srand( time( NULL ) );

		// build and set ARGV
		List *argvList = new List( argc );
		for ( int i = 0; i < argc; ++i )
			argvList->setElementInt( i, new String( argv[ i ] ) );
		globalScope_.setLocalSymbol( "ARGV", argvList );

		// build and set ENV
		//Map *envMap = new Map;
		//char **env = environ();
		//while(*env)
		//{

		//	std::string envString(*env);

		//}
	}

	// Destructor
	//
	Interpreter::~Interpreter()
	{

		// close any dynamic libraries
		std::list< void * >::iterator i, iEnd = modules_.end();
		for ( i = modules_.begin(); i != iEnd; ++i )
			dlclose( *i );
	}

	// getPath()
	//
	void Interpreter::getPath( std::list< std::string > &path )
	{

		// always include the working directory
		path.push_back( "./" );

		// grab the path from the environment
		char *tsPath = getenv( "TSPATH" );
		if ( !tsPath )
			return;

		char *tsPathLocal = new char[ strlen( tsPath ) + 1 ];
		strcpy( tsPathLocal, tsPath );

		// split the path adding each entry to the list
		char *tok = strtok( tsPathLocal, ":" );
		while ( tok )
		{

			path.push_back( std::string( tok ) );
			tok = strtok( NULL, ":" );
		}

		delete [] tsPathLocal;
	}

	// execute()
	//
	bool Interpreter::execute()
	{

		// parse file - the resulting parse tree is allocated in ts_parseTree
		yyparse();
		if ( !ts_parseTree )
			return false; // error already set

		// translate file
		Block *block = translateParseTree();
		if ( !block )
		{

			// clean up
			listDelete( ts_parseTree );

			setRuntimeError( 0, "Internal error: unable to translate parse tree." );
			return false;
		}

		// clean up
		listDelete( ts_parseTree );
		ts_parseTree = 0;

		// execute block
		int ret = block->execute( this, &globalScope_ );

		// clean up
		delete block;

		if ( ret == EXEC_SUCCESS || ret == EXEC_EXIT )
			return true;
		return false;
	}

	// import()
	//
	bool Interpreter::import( const std::string &module )
	{

		// grab path from the environment
		std::list< std::string > path;
		getPath( path );

		// loop through each of the pathed directories attempting to read the
		//  requested module there
		std::list< std::string >::iterator i, iEnd = path.end();
		for ( i = path.begin(); i != iEnd; ++i )
		{

			// ensure there is a trailing / on the path
			std::string pathDir = ( *i );
			if ( pathDir.length() > 0 )
				if ( pathDir[ pathDir.length() - 1 ] != '/' )
					pathDir += "/";

			std::string pathName;
			/*
			// attempt to open a dynamic library
			std::string pathName = pathDir + module + ".so";
			std::cout << "Trying " << pathName << std::endl;
			void *handle = dlopen( pathName.c_str(), RTLD_NOW );
			if ( !handle )
				std::cout << "Failed: " << dlerror() << std::endl;
			if ( handle )
			{

				std::cout << "Opened " << pathName << std::endl;
				// attempt to grab initialization entry point
				void *entry = dlsym( handle, "tsInitialize" );
				if ( !entry )
				{

					dlclose( handle );

					setRuntimeError( "Unable to initialize user module: %s", module.c_str() );
					return false;
				}

				// attempt to initialize user library
				//userEntry tsInitialize = reinterpret_cast< userEntry >( entry );
				userEntry tsInitialize = ( userEntry ) entry;
				try
				{

					if ( !tsInitialize( scope ) )
					{

						dlclose( handle );

						setRuntimeError( "Error initializing user module: %s", module.c_str() );
						return false;
					}
				}
				catch( ... )
				{

					dlclose( handle );

					setRuntimeError( "User module threw an exception: %s", module.c_str() );
					return false;
				}

				// add library handle to the modules list
				modules_.push_back( handle );

				return true;
			}
			*/

			// attempt to open a script file
			pathName = pathDir + module;
			//std::cout << "Trying " << pathName << std::endl;
			yyin = fopen( pathName.c_str(), "r" );
			if ( yyin )
			{

				// parse and execute file
				ts_setFilename( module.c_str() );
				bool result = execute();
				ts_setFilename( 0 );

				return result;
			}

			// attempt to open a script file
			pathName = pathDir + module + ".ts";
			//std::cout << "Trying " << pathName << std::endl;
			yyin = fopen( pathName.c_str(), "r" );
			if ( yyin )
			{

				// parse and execute file
				ts_setFilename( module.c_str() );
				bool result = execute();
				ts_setFilename( 0 );

				return result;
			}
		}

		// report error
		setRuntimeError( 0, "Module not found: %s", module.c_str() );
		return false;
	}

	// eval()
	//
	bool Interpreter::eval( const std::string &text )
	{

		setRuntimeError( 0, "Interpreter::eval() not implemented yet" );
		return false;
	}
}

