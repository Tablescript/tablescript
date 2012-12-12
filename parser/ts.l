/* ts.l

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

D					[0-9]
L					[a-zA-Z_]
H					[a-fA-F0-9]
E					[eE][+-]?{D}+

%{

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ts.tab.h"

extern int ts_lineNumber;

%}

%%

\/\/[^\n]*\n		{ ++ts_lineNumber; }
#[^\n]*\n			{ ++ts_lineNumber; }

"import"			{ return IMPORT; }
"if"				{ return IF; }
"elseif"			{ return ELSEIF; }
"else"				{ return ELSE; }
"for"				{ return FOR; }
"in"				{ return IN; }
"while"				{ return WHILE; }
"break"				{ return BREAK; }
"continue"			{ return CONTINUE; }
"namespace"   { return NAMESPACE; }
"function"			{ return FUNCTION; }
"class"				{ return CLASS; }
"return"			{ return RETURN; }
"table"				{ return TABLE; }
"exit"              { return EXIT; }

"and"				{ return OP_AND; }
"or"				{ return OP_OR; }
"mod"				{ return OP_MOD; }

"None"				{ return NONE_LIT; }

{D}+				{
						yylval.i = atoi(yytext);
						return INT_LIT;
					}
{D}+{E}				{
						yylval.f = atof(yytext);
						return FLOAT_LIT;
					}
{D}*"."{D}+({E})?	{
						yylval.f = atof(yytext);
						return FLOAT_LIT;
					}
{D}+"."{D}*({E})?	{
						yylval.f = atof(yytext);
						return FLOAT_LIT;
					}

\"(\\.|[^\\"])*\"	{
						yylval.s = (char *) malloc(strlen(yytext) - 1);
						strncpy(yylval.s, &yytext[1], strlen(yytext) - 2);
						yylval.s[strlen(yytext) - 2] = 0;
						return STRING_LIT;
					}
{D}*[dD]{D}+([lL]{D}+)?([hH]{D}+)?		{
						yylval.s = (char *) malloc(strlen(yytext) + 1);
						strcpy(yylval.s, yytext);
						return DICE_LIT;
					}

{L}({L}|{D})*		{
						yylval.s = (char *) malloc(strlen(yytext) + 1);
						strcpy(yylval.s, yytext);
						return IDENTIFIER;
					}

";"					{ return ';'; }
":"					{ return ':'; }
"("					{ return '('; }
")"					{ return ')'; }
"{"					{ return '{'; }
"}"					{ return '}'; }
"["					{ return '['; }
"]"					{ return ']'; }
"+"					{ return '+'; }
"-"					{ return '-'; }
"*"					{ return '*'; }
"/"					{ return '/'; }
"%"					{ return '%'; }
"="					{ return '='; }
","					{ return ','; }
"."					{ return '.'; }
"!"					{ return '!'; }
"=="				{ return OP_EQ; }
"!="				{ return OP_NE; }
"<"					{ return '<'; }
">"					{ return '>'; }
"<="				{ return OP_LE; }
">="				{ return OP_GE; }
"++"				{ return OP_INC; }
"--"				{ return OP_DEC; }
"+="				{ return ADD_ASSIGN; }
"-="				{ return SUB_ASSIGN; }
"*="				{ return MUL_ASSIGN; }
"/="				{ return DIV_ASSIGN; }

[ \t]				{ }
\n					{ ++ts_lineNumber; }
.					{ }

%%

