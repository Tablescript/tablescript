/* StringLiteral.h

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

#ifndef _TS_STRINGLITERAL_H_
#define _TS_STRINGLITERAL_H_

#include "Expression.h"
#include <string>
#include "TList.h"

namespace TS
{

	class Interpreter;

	class StringLiteral : public Expression
	{

		std::string format_;

		ExpressionList *parameters_;

		struct ParameterBlock
		{

			unsigned int index;
			bool zeroFill;
			int width;
			int precision;

			void clear();
		};

		Object *getNextParameter( ParameterBlock *parameter, Interpreter *interpreter, Scope *scope );
		bool addIntegerParameter( std::ostringstream &ss, ParameterBlock *parameter, Interpreter *interpreter, Scope *scope );
		bool addFloatParameter( std::ostringstream &ss, ParameterBlock *parameter, Interpreter *interpreter, Scope *scope );
		bool addStringParameter( std::ostringstream &ss, ParameterBlock *parameter, Interpreter *interpreter, Scope *scope );
		bool addParameter( char code, std::ostringstream &ss, ParameterBlock *parameter, Interpreter *interpreter, Scope *scope );

	protected:
		// _evaluate()
		//
		virtual Object *evaluate_( Interpreter *interpreter, Scope *scope );

	public:
		StringLiteral( int lineNumber, const std::string &format, ExpressionList *parameters );
		StringLiteral( const StringLiteral &sl );
		virtual ~StringLiteral();

		// clone()
		//
		virtual Expression *clone() const;
	};
}

#endif
