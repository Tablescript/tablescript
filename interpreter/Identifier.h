/* Identifier.h

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

#ifndef _TS_IDENTIFIER_H_
#define _TS_IDENTIFIER_H_

#include "Expression.h"
#include <string>

namespace TS
{

	class Interpreter;

	class Identifier : public Expression
	{

		std::string name_;

	protected:
		virtual ~Identifier();

		// _evaluate()
		//
		virtual Object *evaluate_( Interpreter *interpreter, Scope *scope );

	public:
		Identifier( int lineNumber, const std::string &name );
		Identifier( const Identifier &i );

		// clone()
		//
		virtual Expression *clone() const;

		// evaluateAsLHS()
		//
		virtual LHSObject *evaluateAsLHS( Interpreter *interpreter, Scope *scope );
	};
}

#endif
