/* MapLiteral.h

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

#ifndef _TS_MAPLITERAL_H_
#define _TS_MAPLITERAL_H_

#include <string>
#include "Expression.h"
#include "TList.h"

namespace TS
{

	class Pair
	{

		Expression *key_;
		Expression *value_;

	public:
		Pair( Expression *key, Expression *value );
		Pair( const Pair &p );
		virtual ~Pair();

		// clone()
		//
		Pair *clone() const;

		Expression *getKey() const;
		Expression *getValue() const;
	};

	class MapLiteral : public Expression
	{

		PairList *elements_;

	protected:
		// _evaluate()
		//
		virtual Object *evaluate_( Interpreter *interpreter, Scope *scope );

	public:
		MapLiteral( int lineNumber, PairList *elements );
		MapLiteral( const MapLiteral &ml );
		virtual ~MapLiteral();

		// clone()
		//
		virtual Expression *clone() const;
	};
}

#endif
