/*

   Scope.h

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

#ifndef _TS_SCOPE_H_
#define _TS_SCOPE_H_

#include <map>
#include <string>

namespace TS
{

	class Object;

	class Scope
	{

        // parentScope_
        //
        // Pointer to the scope's parent. Null if this is the global scope.
		Scope *parentScope_;

        // symbols_
        //
        std::map< std::string, Object * > symbols_;

        // returnValue_
        //
		Object *returnValue_;

	protected:

		// recursiveSetSymbol_()
		//
		bool recursiveSetSymbol_( const std::string &name, Object *value );

	public:
		Scope( Scope *parentScope );
		virtual ~Scope();

		// setSymbol()
		//
		void setSymbol( const std::string &name, Object *value );

		// setLocalSymbol()
		//
		void setLocalSymbol( const std::string &name, Object *value );

		// getSymbol()
		//
		Object *getSymbol( const std::string &name ) const;

		// setReturnValue()
		//
		void setReturnValue( Object *value );

		// getReturnValue()
		//
		Object *getReturnValue() const;
	};
}

#endif
