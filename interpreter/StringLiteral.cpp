/* StringLiteral.cpp

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

#include "StringLiteral.h"
#include "String.h"
#include "Error.h"
#include "Integer.h"
#include "Float.h"
#include <sstream>
#include <iomanip>

namespace TS
{

	// ParameterBlock::clear()
	//
	void StringLiteral::ParameterBlock::clear()
	{

		zeroFill = false;
		width = 0;
		precision = 0;
	}

	// Constructor
	//
	StringLiteral::StringLiteral( int lineNumber, const std::string &format, ExpressionList *parameters )
		: Expression( lineNumber ),
		format_( format ),
		parameters_( parameters )
	{
	}

	// Copy Constructor
	//
	StringLiteral::StringLiteral( const StringLiteral &sl )
		: Expression( sl ),
		format_( sl.format_ )
	{

		parameters_ = sl.parameters_->clone();
	}

	// Destructor
	//
	StringLiteral::~StringLiteral()
	{

		delete parameters_;
	}

	// clone()
	//
	Expression *StringLiteral::clone() const
	{

		return new StringLiteral( *this );
	}

	// getNextParameter()
	//
	Object *StringLiteral::getNextParameter( ParameterBlock *parameter, Interpreter *interpreter, Scope *scope )
	{

		// make sure we have enough parameters
		if ( parameter->index >= parameters_->size() )
		{

			setRuntimeError( ERROR_NOT_ENOUGH_STRING_FORMAT_PARAMETERS );
			return 0;
		}

		// grab the proper parameter
		Expression *e = ( *parameters_ )[ parameter->index ]; // borrowed reference
		return e->evaluate( interpreter, scope ); // new reference
	}

	// addIntegerParameter()
	//
	bool StringLiteral::addIntegerParameter( std::ostringstream &ss, ParameterBlock *parameter, Interpreter *interpreter, Scope *scope )
	{

		Object *value = getNextParameter( parameter, interpreter, scope ); // new reference
		if ( !value )
			return false;

		// convert parameter to an integer
		Integer *i = value->toInteger(); // new reference
		if ( !i )
		{

			value->decRef();
			return false;
		}

		// add the integer to the stream
		ss << i->getValue();

		value->decRef();
		i->decRef();

		return true;
	}

	// addFloatParameter()
	//
	bool StringLiteral::addFloatParameter( std::ostringstream &ss, ParameterBlock *parameter, Interpreter *interpreter, Scope *scope )
	{

		Object *value = getNextParameter( parameter, interpreter, scope ); // new reference
		if ( !value )
			return false;

		// convert parameter to a float
		Float *f = value->toFloat(); // new reference
		if ( !f )
		{

			value->decRef();
			return false;
		}

		// add the float to the stream
		ss << f->getValue();

		value->decRef();
		f->decRef();

		return true;
	}

	// addStringParameter()
	//
	bool StringLiteral::addStringParameter( std::ostringstream &ss, ParameterBlock *parameter, Interpreter *interpreter, Scope *scope )
	{

		Object *value = getNextParameter( parameter, interpreter, scope ); // new reference
		if ( !value )
			return false;

		// convert parameter to a string
		String *s = value->toString(); // new reference
		if ( !s )
		{

			value->decRef();
			return false;
		}

		// add the string to the stream
		ss << ( s->getValue() ).c_str();

		value->decRef();
		s->decRef();

		return true;
	}

	// addParameter()
	//
	bool StringLiteral::addParameter( char code, std::ostringstream &ss, ParameterBlock *parameter, Interpreter *interpreter, Scope *scope )
	{

		// zero fill
		if ( parameter->zeroFill )
			ss << std::setfill( '0' );

		// width
		ss << std::setw( parameter->width );

		// precision
		ss << std::setprecision( parameter->precision );

		if ( code == 'd' )
			return addIntegerParameter( ss, parameter, interpreter, scope );
		if ( code == 'f' )
			return addFloatParameter( ss, parameter, interpreter, scope );

		return addStringParameter( ss, parameter, interpreter, scope );
	}

	// evaluate()
	//
	Object *StringLiteral::evaluate_( Interpreter *interpreter, Scope *scope )
	{

		// parse state
		enum State { INIT, PERCENT, ZEROFILL, WIDTH, PRECISION } state = INIT;
		bool escaped = false;

		// parameter
		ParameterBlock parameter;
		parameter.clear();
		parameter.index = 0;

		// parse the format string
		std::ostringstream ss;
		std::string::iterator i, iEnd = format_.end();
		for ( i = format_.begin(); i != iEnd; ++i )
		{

			switch ( state )
			{

			case INIT:

				switch ( *i )
				{

				case '%':
					state = PERCENT;
					break;

				case '\\':
					if ( escaped )
					{

						ss << "\\";
						escaped = false;
					}
					else
						escaped = true;
					break;

				case 't':
					if ( escaped )
					{

						ss << "\t";
						escaped = false;
					}
					else
						ss << "t";
					break;

				case 'n':
					if ( escaped )
					{

						ss << "\n";
						escaped = false;
					}
					else
						ss << "n";
					break;

				case '\"':
					if ( escaped )
					{

						ss << "\"";
						escaped = false;
					}
					//else ??
					break;

				default:
					ss << ( *i );
					break;
				}
				break;

			case PERCENT:

				switch ( *i )
				{

				case '%':
					ss << "%";
					state = INIT;
					break;

				case '0':
					parameter.zeroFill = true;
					state = ZEROFILL;
					break;

				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					parameter.width *= 10;
					parameter.width += ( ( *i ) - '0' );
					state = WIDTH;
					break;

				case '.':
					state = PRECISION;
					break;

				case 'd':
				case 'f':
				case 's':
					if ( !addParameter( *i, ss, &parameter, interpreter, scope ) )
						return 0;
					parameter.clear();
					++parameter.index;
					state = INIT;
					break;

				default:
					setRuntimeError( ERROR_INVALID_FORMAT_STRING );
					return 0;
				}
				break;

			case ZEROFILL:

				switch ( *i )
				{

				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					parameter.width *= 10;
					parameter.width += ( ( *i ) - '0' );
					state = WIDTH;
					break;

				case '.':
					state = PRECISION;
					break;

				case 'd':
				case 'f':
				case 's':
					if ( !addParameter( *i, ss, &parameter, interpreter, scope ) )
						return 0;
					parameter.clear();
					++parameter.index;
					state = INIT;
					break;

				default:
					setRuntimeError( ERROR_INVALID_FORMAT_STRING );
					return 0;
				}
				break;

			case WIDTH:

				switch ( *i )
				{

				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					parameter.width *= 10;
					parameter.width += ( ( *i ) - '0' );
					break;

				case '.':
					state = PRECISION;
					break;

				case 'd':
				case 'f':
				case 's':
					if ( !addParameter( *i, ss, &parameter, interpreter, scope ) )
						return 0;
					parameter.clear();
					++parameter.index;
					state = INIT;
					break;

				default:
					setRuntimeError( ERROR_INVALID_FORMAT_STRING );
					return 0;
				}
				break;

			case PRECISION:

				switch ( *i )
				{

				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					parameter.precision *= 10;
					parameter.precision += ( ( *i ) - '0' );
					break;

				case 'd':
				case 'f':
				case 's':
					if ( !addParameter( *i, ss, &parameter, interpreter, scope ) )
						return 0;
					parameter.clear();
					++parameter.index;
					state = INIT;
					break;

				default:
					setRuntimeError( ERROR_INVALID_FORMAT_STRING );
					return 0;
				}
				break;
			}
		}

		if ( parameter.index < parameters_->size() )
		{

			setRuntimeError( ERROR_TOO_MANY_STRING_FORMAT_PARAMETERS );
			return 0;
		}

		return new String( ss.str() ); // new reference
	}

}

