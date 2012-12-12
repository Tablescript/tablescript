/* Function.h

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

#ifndef _TS_FUNCTION_H_
#define _TS_FUNCTION_H_

#include "Object.h"

#include <vector>
#include <string>

namespace TS
{

	class Block;
	class Interpreter;
	class Scope;

	class Function : public Object
	{

        std::string name_;
		std::vector<std::string> *fargs_;
		Block *block_;

	protected:
		virtual ~Function();

	public:
		Function( const std::string &name, std::vector< std::string > *fargs, Block *block );

		// getTypeName()
		//
		inline virtual const char *getTypeName() const { return "Function"; }

		// isTrue()
		//
		virtual bool isTrue() const;

		// call()
		//
		virtual Object *call( Interpreter *interpreter, Scope *scope, List *parameters, const std::string &callScope );
	};
}

#endif
