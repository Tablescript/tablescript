/* ConditionalExpression.h

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

#ifndef _TS_CONDITIONALEXPRESSION_H_
#define _TS_CONDITIONALEXPRESSION_H_

#include "Expression.h"

namespace TS
{

	class Interpreter;

	class ConditionalExpression : public Expression
	{

		Expression *test_;
		Expression *trueValue_;
		Expression *falseValue_;

	protected:
		// _evaluate()
		//
		virtual Object *evaluate_( Interpreter *interpreter, Scope *scope );

	public:
		ConditionalExpression( int lineNumber, Expression *test, Expression *trueValue, Expression *falseValue );
		ConditionalExpression( const ConditionalExpression &ce );
		virtual ~ConditionalExpression();

		// clone()
		//
		virtual Expression *clone() const;
	};
}

#endif
