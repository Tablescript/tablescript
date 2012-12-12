/* Interpreter.h

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

#ifndef _TS_INTERPRETER_H_
#define _TS_INTERPERTER_H_

#include "Scope.h"

#include <string>
#include <list>

typedef bool ( *userEntry )( TS::Scope * );

namespace TS
{

	class Block;

    //! Main TableScript Interpreter
    //!
    //! This class implements the main routine of the TableScript interpreter.
	class Interpreter
	{

		//! Global Scope
		//!
		Scope globalScope_;

		//! User Libraries
		//!
		//! Each entry in this list is a handle to a user module. These
        //!  modules are loaded when the user imports a dynamic library
        //!  file, and they are freed when the Interpreter object gets
        //!  destroyed.
		std::list< void * > modules_;

        //! Populates the passed list with paths to search for the file
        //!  being imported.
        //!
		void getPath( std::list< std::string > &path );

        //! Executes something...
        //!
		bool execute();

	public:

        //! Constructor
        //!
		Interpreter( int argc, char *argv[] );

        //! Destructor
        //!
		~Interpreter();

		//! Imports (and executes) the passed module name into the working
        //!  environment.
		//!
		bool import( const std::string &module );

		//! Executes the passed string into the working environment.
		//!
		bool eval( const std::string &text );

        //! Retrieves a pointer to the global scope.
        //!
        inline Scope *getGlobalScope() { return &globalScope_; }
	};
}

#endif
