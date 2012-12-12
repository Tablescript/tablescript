/* Expression.h

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

#ifndef _TS_EXPRESSION_H_
#define _TS_EXPRESSION_H_

namespace TS
{

	class Object;
	class Interpreter;
	class Scope;
	class LHSObject;

    // Expression class
    //
	class Expression
	{

		int lineNumber_;

	protected:
		virtual Object *evaluate_( Interpreter *interpreter, Scope *scope ) = 0;

	public:
		Expression( int lineNumber );
		Expression( const Expression &e );
		virtual ~Expression();

		// clone()
		//
		virtual Expression *clone() const = 0;

		// evaluate()
		//
		Object *evaluate( Interpreter *interpreter, Scope *scope );

		// evaluateAsLHS()
		//
		// This method evaluates the contained expression as the left-hand side of
		//  an assignment.
		virtual LHSObject *evaluateAsLHS( Interpreter *interpreter, Scope *scope );
	};
}

#endif
