/* MemberExpression.h

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

#ifndef _TS_MEMBEREXPRESSION_H_
#define _TS_MEMBEREXPRESSION_H_

#include "Expression.h"
#include "TList.h"

namespace TS
{

    class Instance;
	class Interpreter;
    class Scope;
	class Object;

	// MemberExpression Class
	//
	class MemberExpression : public Expression
	{

		Expression *base_;
		std::string memberName_;

        // getInstance_()
        //
        Instance *getInstance_( Interpreter *interpreter, Scope *scope );

	protected:
		// evaluate_()
		//
		virtual Object *evaluate_( Interpreter *interpreter, Scope *scope );

	public:
		MemberExpression( int lineNumber, Expression *base, const std::string &memberName );
		MemberExpression( const MemberExpression &ce );
		virtual ~MemberExpression();

		// clone()
		//
		virtual Expression *clone() const;

        // evaluateAsLHS()
        //
        virtual LHSObject *evaluateAsLHS( Interpreter *interpreter, Scope *scope );
	};
}

#endif
