/* Error.cpp

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

#include "Error.h"
#include "Interpreter.h"

#include <string.h>
#include <stdarg.h>
#include <sstream>

namespace TS
{

	// Line Number
	//
	int errorLineNumber = 0;

	// The Error Message
	//
	std::string errorMessage;

	// setRuntimeError()
	//
	void setRuntimeError( const char *format, ... )
	{

		if ( !format )
			return;

		// assume a reasonable size
		size_t length = strlen( format ) * 2;
		char *msg = new char[ length ];

		// format the message
		va_list marker;
		va_start( marker, format );
		vsnprintf( msg, length, format, marker );

		// assign the error message and convert to std::string
		errorMessage += msg;

		// clean up
		delete [] msg;
	}

	// setError_NOSUPPORT()
	//
	void setError_NOSUPPORT( const char *type, const char *action )
	{

		std::ostringstream ss;
		ss << "Type '" << type << "' does not support " << action << ".";
		errorMessage = ss.str();
	}

    // The Stack Trace
    //
    std::list< std::string > stackTrace;

    // pushErrorContext()
    //
    void pushErrorContext( const std::string &context )
    {

        stackTrace.push_back( context );
    }


    // Error Messages
    //
    const char *ERROR_EXPRESSION_NOT_INSTANCE = "Expression to the left of the . does not evaluate to an instance";
    const char *ERROR_DIVIDE_BY_ZERO = "Divide by zero";
    const char *ERROR_MODULO_DIVIDE_BY_ZERO = "Module divide by zero";
    const char *ERROR_FUNCTION_TAKES_X_PARAMETERS = "Function %s() takes %d parameter(s) - %d provided";
    const char *ERROR_PARAMETER_X_MUST_BE_TYPE_Y = "%s() parameter %d must be of type %s";
    const char *ERROR_INVALID_LHS = "Invalid left-hand side";
    const char *ERROR_FOR_EXPRESSION_MUST_BE_LIST = "For loop expression must evaluate to a list";
    const char *ERROR_INCDEC_ONLY_FOR_INTEGERS = "Increment/decrement operator only applies to integers";
    const char *ERROR_INVALID_EXPRESSION_TAG = "Invalid expression tag (%s)";
    const char *ERROR_INDEX_X_OUT_OF_BOUNDS = "Index %d out of bounds";
    const char *ERROR_INDEX_MUST_BE_INTEGER = "Index must be an integer";
    const char *ERROR_INVALID_KEY_X = "Invalid key '%s'";
    const char *ERROR_MAP_KEY_MUST_BE_STRING = "Map key must be a string";
    const char *ERROR_FEATURE_X_NOT_IMPLEMENTED = "Feature '%s' has not been implemented yet";
    const char *ERROR_TYPE_X_DOES_NOT_SUPPORT_Y = "Type '%s' does not support %s";
    const char *ERROR_INTERNAL_INVALID_BINARYEXPRESSION_TAG_X = "Internal error - BinaryExpression with invalid tag (%d)";
    const char *ERROR_INVALID_DICE_LITERAL_X = "Invalid dice literal '%s'";
    const char *ERROR_INVALID_FORMAT_STRING = "Invalid format string";
    const char *ERROR_BREAK_WITH_NO_LOOP = "Break statement with no enclosing loop";
    const char *ERROR_CONTINUE_WITH_NO_LOOP = "Continue statement with no enclosing loop";
    const char *ERROR_RETURN_IN_TABLE = "Return statement not allowed in table block";
    const char *ERROR_NO_METHOD_X = "Object has no method named '%s'";
    const char *ERROR_NOT_ENOUGH_STRING_FORMAT_PARAMETERS = "Not enough string format parameters";
    const char *ERROR_TOO_MANY_STRING_FORMAT_PARAMETERS = "Too many string format parameters";
    const char *ERROR_NO_TABLE_ENTRY_FOR_X = "No table entry for roll (%d)";
    const char *ERROR_INVALID_INDEX_X = "Index %d invalid";
}
