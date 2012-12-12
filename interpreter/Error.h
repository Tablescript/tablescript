/* Error.h

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

#ifndef _TS_ERROR_H_
#define _TS_ERROR_H_

#include <string>

namespace TS
{

    class Interpreter;

	// Line Number
	//
	// This is the line number on which the error occurred.
	extern int errorLineNumber;

	// Error Message
	//
	// This is a reference to the error message string. Clients can access this
	//  directly or through the formatting function below.
	extern std::string errorMessage;

	// setRuntimeError()
	//
	// This function allows clients to build formatted error messages.
	void setRuntimeError( const char *format, ... );

	// setError_NOSUPPORT()
	//
	void setError_NOSUPPORT( const char *type, const char *action );

    // pushErrorContext()
    //
    void pushErrorContext( const std::string &context );

    // Error Messages
    //
    extern const char *ERROR_EXPRESSION_NOT_INSTANCE;
    extern const char *ERROR_DIVIDE_BY_ZERO;
    extern const char *ERROR_MODULO_DIVIDE_BY_ZERO;
    extern const char *ERROR_FUNCTION_TAKES_X_PARAMETERS;
    extern const char *ERROR_PARAMETER_X_MUST_BE_TYPE_Y;
    extern const char *ERROR_INVALID_LHS;
    extern const char *ERROR_FOR_EXPRESSION_MUST_BE_LIST;
    extern const char *ERROR_INCDEC_ONLY_FOR_INTEGERS;
    extern const char *ERROR_INVALID_EXPRESSION_TAG;
    extern const char *ERROR_INDEX_X_OUT_OF_BOUNDS;
    extern const char *ERROR_INDEX_MUST_BE_INTEGER;
    extern const char *ERROR_INVALID_KEY_X;
    extern const char *ERROR_MAP_KEY_MUST_BE_STRING;
    extern const char *ERROR_FEATURE_X_NOT_IMPLEMENTED;
    extern const char *ERROR_TYPE_X_DOES_NOT_SUPPORT_Y;
    extern const char *ERROR_INTERNAL_INVALID_BINARYEXPRESSION_TAG_X;
    extern const char *ERROR_INVALID_DICE_LITERAL_X;
    extern const char *ERROR_INVALID_FORMAT_STRING;
    extern const char *ERROR_BREAK_WITH_NO_LOOP;
    extern const char *ERROR_CONTINUE_WITH_NO_LOOP;
    extern const char *ERROR_RETURN_IN_TABLE;
    extern const char *ERROR_NO_METHOD_X;
    extern const char *ERROR_NOT_ENOUGH_STRING_FORMAT_PARAMETERS;
    extern const char *ERROR_TOO_MANY_STRING_FORMAT_PARAMETERS;
    extern const char *ERROR_NO_TABLE_ENTRY_FOR_X;
    extern const char *ERROR_INVALID_INDEX_X;
}

#endif
