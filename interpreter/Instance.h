/* Instance.h

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

#ifndef _TS_INSTANCE_H_
#define _TS_INSTANCE_H_

#include "Object.h"

#include <string>

namespace TS
{

	class Scope;
	class MethodMap;
	class Function;

	class Instance : public Object
	{

        std::string className_;
		Scope *scope_;

	protected:
		virtual ~Instance();

	public:
		Instance( std::string &className, Scope *scope );

		// getTypeName()
		//
		inline virtual const char *getTypeName() const { return "Instance"; }

        // isTrue()
        //
        inline virtual bool isTrue() const { return true; }

		// getMember()
		//
		Object *getMember( const std::string &memberName ) const;

        // setMember()
        //
        void setMember( const std::string &memberName, Object *value );

        // callMethod()
        //
        Object *callMethod( Interpreter *interpreter, const std::string &methodName, List *parameters );
	};
}

#endif
