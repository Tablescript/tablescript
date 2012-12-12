/* LHSObject.h

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

#ifndef _TS_LHSOBJECT_H_
#define _TS_LHSOBJECT_H_

#include <string>

namespace TS
{

	class Object;
	class Interpreter;
	class Scope;
    class Instance;

	// LHSObject
	//
	class LHSObject
	{

	public:
		LHSObject();
		virtual ~LHSObject();

		// evaluate()
		//
		virtual Object *evaluate( Interpreter *interpreter, Scope *scope ) = 0;

		// assign()
		//
		virtual bool assign( Interpreter *interpreter, Scope *scope, Object *value ) = 0;
	};

	// LHSIdentifier
	//
	class LHSIdentifier : public LHSObject
	{

		std::string identifier_;

	public:
		LHSIdentifier( const std::string &identifier );
		virtual ~LHSIdentifier();

		// evaluate()
		//
		virtual Object *evaluate( Interpreter *interpreter, Scope *scope );

		// assign()
		//
		virtual bool assign( Interpreter *interpreter, Scope *scope, Object *value );
	};

	// LHSElement
	//
	class LHSElement : public LHSObject
	{

		Object *subject_;
		Object *key_;

	public:
		LHSElement( Object *subject, Object *key );
		virtual ~LHSElement();

		// evaluate()
		//
		virtual Object *evaluate( Interpreter *interpreter, Scope *scope );

		// assign()
		//
		virtual bool assign( Interpreter *interpreter, Scope *scope, Object *value );
	};

    // LHSMember
    //
    class LHSMember : public LHSObject
    {

        Instance *instance_;
        std::string memberName_;

    public:
        LHSMember( Instance *instance, const std::string &memberName );
        virtual ~LHSMember();

        // evaluate()
        //
        virtual Object *evaluate( Interpreter *interpreter, Scope *scope );

        // assign()
        //
        virtual bool assign( Interpreter *interpreter, Scope *scope, Object *value );
    };
}

#endif
