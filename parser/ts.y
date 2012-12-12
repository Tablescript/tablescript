/* ts.y

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

%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pstatement.h"
#include "pexpression.h"
#include "plist.h"
/*#include "pdump.h"*/

/***************************************************************************/
/* Filename                                                                */
/*                                                                         */
/* This is the name of the file currently being parsed.                    */
/***************************************************************************/
char *ts_filename = NULL;
void ts_setFilename(const char *filename)
{

	if(ts_filename != NULL)
		free(ts_filename);

	if(filename == NULL)
	{

		ts_filename = NULL;
		return;
	}

	ts_filename = (char *) malloc(strlen(filename) + 1);
	strcpy(ts_filename, filename);
}

/***************************************************************************/
/* Current Line Number                                                     */
/*                                                                         */
/* This is the line number of the last scanned token.                      */
/***************************************************************************/
int ts_lineNumber = 1;

/***************************************************************************/
/* Parse Tree                                                              */
/*                                                                         */
/* This is the resulting parse tree.                                       */
/***************************************************************************/
struct PList *ts_parseTree;


int yylex(void);

/***************************************************************************/
/* yyerror()                                                               */
/*                                                                         */
/***************************************************************************/
int yyerror(char *s)
{

	printf("Error in %s: %s (Line %d)\n", ts_filename, s, ts_lineNumber);
	return 0;
}

/***************************************************************************/
/* yywrap()                                                                */
/*                                                                         */
/***************************************************************************/
int yywrap()
{

	return 1;
}

%}

%union
{

	int i;
	float f;
	char *s;

	struct PStmt *stmt;
	struct PExpr *expr;
	struct PList *list;
	struct PElseIf *elseif;
	struct PTableEntry *entr;
	struct PPair *pair;
}

%token <s> IDENTIFIER
%token <i> INT_LIT
%token <s> STRING_LIT
%token <f> FLOAT_LIT
%token <s> DICE_LIT
%token NONE_LIT

%token OP_MOD
%token OP_AND
%token OP_OR
%token OP_EQ
%token OP_NE
%token OP_LE
%token OP_GE
%token OP_INC
%token OP_DEC
%token ADD_ASSIGN
%token SUB_ASSIGN
%token MUL_ASSIGN
%token DIV_ASSIGN

%token IMPORT

%token IF
%token ELSEIF
%token ELSE

%token FOR
%token IN
%token WHILE
%token BREAK
%token CONTINUE
%token EXIT

%token NAMESPACE
%token FUNCTION
%token CLASS
%token RETURN
%token TABLE

%type <list> statements
%type <list> optional_statements
%type <stmt> statement

%type <expr> literal
%type <list> pair_list
%type <list> pairs
%type <pair> pair
%type <expr> primary_expression
%type <expr> member_access
%type <expr> method_invocation
%type <expr> postfix_expression
%type <list> expression_list
%type <list> expressions
%type <expr> list_access
%type <expr> unary_expression
%type <expr> multiplicative_expression
%type <expr> additive_expression
%type <expr> relational_expression
%type <expr> equality_expression
%type <expr> in_expression
%type <expr> and_expression
%type <expr> or_expression
%type <expr> conditional_expression
%type <expr> assignment_expression
%type <expr> expression
%type <stmt> expression_statement

%type <stmt> if_statement
%type <list> elseif_list
%type <elseif> elseif_statement
%type <list> else_statement

%type <stmt> for_loop
%type <stmt> while_loop

%type <stmt> namespace_definition

%type <stmt> function_definition
%type <list> function_args
%type <list> formal_args

%type <stmt> class_definition
%type <list> class_methods

%type <stmt> table_definition
%type <list> table_args
%type <s> optional_dice
%type <list> optional_block
%type <list> table_entry_list			/* can be empty */
%type <list> table_entries
%type <entr> table_entry

%expect 1

%%

program
	: statements
		{ ts_parseTree = $1; }
	;

/***************************************************************************/
/*                                STATEMENTS                               */
/*                                                                         */
/***************************************************************************/
statements
    : statement
		{ $$ = listNew(LT_STMTS, $1); }
	| statements statement
		{ listAdd($1, $2); $$ = $1; }
	;

optional_statements
    :
        { $$ = NULL; }
    | statements
        { $$ = $1; }
    ;

statement
    : expression_statement
		{ $$ = $1; }
	| IMPORT expression ';'
		{ $$ = stmtNewImport(ts_lineNumber, $2); }
	| if_statement
		{ $$ = $1; }
	| for_loop
		{ $$ = $1; }
	| while_loop
		{ $$ = $1; }
	| namespace_definition
		{ $$ = $1; }
	| function_definition
		{ $$ = $1; }
	| table_definition
		{ $$ = $1; }
	| class_definition
		{ $$ = $1; }
	| BREAK ';'
		{ $$ = stmtNewBreak(ts_lineNumber); }
	| CONTINUE ';'
		{ $$ = stmtNewContinue(ts_lineNumber); }
    | EXIT ';'
        { $$ = stmtNewExit(ts_lineNumber); }
	| RETURN ';'
		{ $$ = stmtNewReturn(ts_lineNumber, NULL); }
	| RETURN expression ';'
		{ $$ = stmtNewReturn(ts_lineNumber, $2); }
	;

expression_statement
	: ';'
		{ $$ = stmtNewExpr(ts_lineNumber, NULL); }
	| expression ';'
		{ $$ = stmtNewExpr(ts_lineNumber, $1); }
	;

/***************************************************************************/
/*                              EXPRESSIONS                                */
/*                                                                         */
/***************************************************************************/
primary_expression
	: literal
		{ $$ = $1; }
	| IDENTIFIER
		{ $$ = exprNewS(ET_IDENTIFIER, ts_lineNumber, $1); }
	| '(' expression ')'
		{ $$ = $2; }
	| member_access
		{ $$ = $1; }
	| method_invocation
		{ $$ = $1;}
	;

literal
	: INT_LIT
		{ $$ = exprNewI(ET_INT_LIT, ts_lineNumber, $1); }
	| FLOAT_LIT
		{ $$ = exprNewF(ET_FLOAT_LIT, ts_lineNumber, $1); }
	| STRING_LIT
		{ $$ = exprNewSL(ET_STRING_LIT, ts_lineNumber, $1, NULL); }
	| STRING_LIT '%'  '[' expressions ']'
		{ $$ = exprNewSL(ET_STRING_LIT, ts_lineNumber, $1, $4); }
	| DICE_LIT
		{ $$ = exprNewS(ET_DICE_LIT, ts_lineNumber, $1); }
	| '[' expression_list ']'
		{ $$ = exprNewL(ET_LIST_LIT, ts_lineNumber, $2); }
	| '{' pair_list '}'
		{ $$ = exprNewL(ET_MAP_LIT, ts_lineNumber, $2); }
	| NONE_LIT
		{ $$ = exprNew(ET_NONE_LIT, ts_lineNumber); }
	;

pair_list
	:
		{ $$ = NULL; }
	| pairs
		{ $$ = $1; }
	;

pairs
	: pair
		{ $$ = listNew(LT_PAIRS, $1); }
	| pairs ',' pair
		{ listAdd($1, $3); $$ = $1; }
	;

pair
	: expression ':' expression
		{ $$ = pairNew($1, $3); }
	;

member_access
	: primary_expression '.' IDENTIFIER
		{ $$ = exprNewES(ET_MEMBER, ts_lineNumber, $1, $3); }
	;
	
method_invocation
	: primary_expression '.' IDENTIFIER '(' ')'
		{ $$ = exprNewESL(ET_METHOD, ts_lineNumber, $1, $3, NULL); }
	| primary_expression '.' IDENTIFIER '(' expressions ')'
		{ $$ = exprNewESL(ET_METHOD, ts_lineNumber, $1, $3, $5); }
	;

postfix_expression
	: primary_expression
		{ $$ = $1; }
	| list_access
		{ $$ = $1; }
	| postfix_expression '(' ')'
		{ $$ = exprNewEL(ET_CALL, ts_lineNumber, $1, NULL); }
	| postfix_expression '(' expressions ')'
		{ $$ = exprNewEL(ET_CALL, ts_lineNumber, $1, $3); }
	| postfix_expression OP_INC
		{ $$ = exprNewE(ET_POST_INC, ts_lineNumber, $1); }
	| postfix_expression OP_DEC
		{ $$ = exprNewE(ET_POST_DEC, ts_lineNumber, $1); }
	;

list_access
	: postfix_expression '[' expression ']'
		{ $$ = exprNewEE(ET_ELEMENT, ts_lineNumber, $1, $3); }
	| postfix_expression '[' expression ':' ']'
		{ $$ = exprNewEEE(ET_SLICE, ts_lineNumber, $1, $3, NULL); }
	| postfix_expression '[' ':' expression ']'
		{ $$ = exprNewEEE(ET_SLICE, ts_lineNumber, $1, NULL, $4); }
	| postfix_expression '[' expression ':' expression ']'
		{ $$ = exprNewEEE(ET_SLICE, ts_lineNumber, $1, $3, $5); }
	;

expression_list
	:
		{ $$ = NULL; }
	| expressions
		{ $$ = $1; }
	;

expressions
	: assignment_expression
		{ $$ = listNew(LT_EXPRS, $1); }
	| expressions ',' assignment_expression
		{ listAdd($1, $3); $$ = $1; }
	;

unary_expression
	: postfix_expression
		{ $$ = $1; }
	| OP_INC postfix_expression
		{ $$ = exprNewE(ET_PRE_INC, ts_lineNumber, $2); }
	| OP_DEC postfix_expression
		{ $$ = exprNewE(ET_PRE_DEC, ts_lineNumber, $2); }
	| '+' postfix_expression
		{ $$ = exprNewE(ET_POS, ts_lineNumber, $2); }
	| '-' postfix_expression
		{ $$ = exprNewE(ET_NEG, ts_lineNumber, $2); }
	| '!' postfix_expression
		{ $$ = exprNewE(ET_NOT, ts_lineNumber, $2); }
	;

multiplicative_expression
	: unary_expression
		{ $$ = $1; }
	| multiplicative_expression '*' unary_expression
		{ $$ = exprNewEE(ET_MUL, ts_lineNumber, $1, $3); }
	| multiplicative_expression '/' unary_expression
		{ $$ = exprNewEE(ET_DIV, ts_lineNumber, $1, $3); }
	| multiplicative_expression OP_MOD unary_expression
		{ $$ = exprNewEE(ET_MOD, ts_lineNumber, $1, $3); }
	;

additive_expression
	: multiplicative_expression
		{ $$ = $1; }
	| additive_expression '+' multiplicative_expression
		{ $$ = exprNewEE(ET_ADD, ts_lineNumber, $1, $3); }
	| additive_expression '-' multiplicative_expression
		{ $$ = exprNewEE(ET_SUB, ts_lineNumber, $1, $3); }
	;

relational_expression
	: additive_expression
		{ $$ = $1; }
	| relational_expression '<' additive_expression
		{ $$ = exprNewEE(ET_LT, ts_lineNumber, $1, $3); }
	| relational_expression '>' additive_expression
		{ $$ = exprNewEE(ET_GT, ts_lineNumber, $1, $3); }
	| relational_expression OP_LE additive_expression
		{ $$ = exprNewEE(ET_LE, ts_lineNumber, $1, $3); }
	| relational_expression OP_GE additive_expression
		{ $$ = exprNewEE(ET_GE, ts_lineNumber, $1, $3); }
	;

equality_expression
	: relational_expression
		{ $$ = $1; }
	| equality_expression OP_EQ relational_expression
		{ $$ = exprNewEE(ET_EQ, ts_lineNumber, $1, $3); }
	| equality_expression OP_NE relational_expression
		{ $$ = exprNewEE(ET_NE, ts_lineNumber, $1, $3); }
	;

in_expression
	: equality_expression
		{ $$ = $1; }
	| in_expression IN equality_expression
		{ $$ = exprNewEE(ET_IN, ts_lineNumber, $1, $3); }
	;

and_expression
	: in_expression
		{ $$ = $1; }
	| and_expression OP_AND in_expression
		{ $$ = exprNewEE(ET_AND, ts_lineNumber, $1, $3); }
	;

or_expression
	: and_expression
		{ $$ = $1; }
	| or_expression OP_OR and_expression
		{ $$ = exprNewEE(ET_OR, ts_lineNumber, $1, $3); }
	;

conditional_expression
	: or_expression
		{ $$ = $1; }
	| or_expression '?' expression ':' conditional_expression
		{ $$ = exprNewEEE(ET_CONDITIONAL, ts_lineNumber, $1, $3, $5); }
	;

assignment_expression
	: conditional_expression
		{ $$ = $1; }
	| unary_expression '=' assignment_expression
		{ $$ = exprNewEE(ET_ASSIGN, ts_lineNumber, $1, $3); }
	| unary_expression MUL_ASSIGN assignment_expression
		{ $$ = exprNewEE(ET_MUL_ASSIGN, ts_lineNumber, $1, $3); }
	| unary_expression DIV_ASSIGN assignment_expression
		{ $$ = exprNewEE(ET_DIV_ASSIGN, ts_lineNumber, $1, $3); }
	| unary_expression ADD_ASSIGN assignment_expression
		{ $$ = exprNewEE(ET_ADD_ASSIGN, ts_lineNumber, $1, $3); }
	| unary_expression SUB_ASSIGN assignment_expression
		{ $$ = exprNewEE(ET_SUB_ASSIGN, ts_lineNumber, $1, $3); }
	;

expression
	: assignment_expression
		{ $$ = $1; }
	;

/***************************************************************************/
/*                             IF STATEMENTS                               */
/*                                                                         */
/***************************************************************************/
if_statement
	: IF '(' expression ')' '{' optional_statements '}'
		{ $$ = stmtNewIf(ts_lineNumber, $3, $6, NULL, NULL); }
	| IF '(' expression ')' '{' optional_statements '}' else_statement
		{ $$ = stmtNewIf(ts_lineNumber, $3, $6, NULL, $8); }
	| IF '(' expression ')' '{' optional_statements '}' elseif_list
		{ $$ = stmtNewIf(ts_lineNumber, $3, $6, $8, NULL); }
	| IF '(' expression ')' '{' optional_statements '}' elseif_list else_statement
		{ $$ = stmtNewIf(ts_lineNumber, $3, $6, $8, $9); }
	;

elseif_list
	: elseif_statement
		{ $$ = listNew(LT_ELSEIFS, $1); }
	| elseif_list elseif_statement
		{ listAdd($1, $2); $$ = $1; }
	;

elseif_statement
	: ELSEIF '(' expression ')' '{' optional_statements '}'
		{ $$ = elseifNew($3, $6); }
	;

else_statement
	: ELSE '{' optional_statements '}'
		{ $$ = $3; }
	;

/***************************************************************************/
/*                               FOR LOOPS                                 */
/*                                                                         */
/***************************************************************************/
for_loop
	: FOR IDENTIFIER IN expression '{' optional_statements '}'
		{ $$ = stmtNewFor(ts_lineNumber, $2, $4, $6); }
	;

/***************************************************************************/
/*                              WHILE LOOPS                                */
/*                                                                         */
/***************************************************************************/
while_loop
	: WHILE '(' expression ')' '{' optional_statements '}'
		{ $$ = stmtNewWhile(ts_lineNumber, $3, $6); }
	;

/***************************************************************************/
/*                              NAMESPACES                                 */
/*                                                                         */
/***************************************************************************/
namespace_definition
	: NAMESPACE IDENTIFIER '{' statements '}'
		{ $$ = NULL; }
	;

/***************************************************************************/
/*                               FUNCTIONS                                 */
/*                                                                         */
/***************************************************************************/
function_definition
	: FUNCTION IDENTIFIER '(' function_args ')' '{' optional_statements '}'
		{ $$ = stmtNewFunction(ts_lineNumber, $2, $4, $7); }
	;

function_args
	:
		{ $$ = NULL; }
	| formal_args
		{ $$ = $1; }
	;

formal_args
	: IDENTIFIER
		{ $$ = listNew(LT_STRINGS, $1); }
	| formal_args ',' IDENTIFIER
		{ listAdd($1, $3); }
	;

/***************************************************************************/
/*                                CLASSES                                  */
/*                                                                         */
/***************************************************************************/
class_definition
	: CLASS IDENTIFIER '{' class_methods '}'
		{ $$ = stmtNewClass(ts_lineNumber, $2, $4); }
	;

class_methods
	: function_definition
		{ $$ = listNew(LT_METHODS, $1); }
	| class_methods function_definition
		{ listAdd($1, $2); $$ = $1; }
	;

/***************************************************************************/
/*                                TABLES                                   */
/*                                                                         */
/***************************************************************************/
table_definition
	: TABLE IDENTIFIER table_args optional_dice '{' optional_block table_entry_list '}'
		{ $$ = stmtNewTable(ts_lineNumber, $2, $3, $4, $6, $7); }
	;

table_args
	:
		{ $$ = NULL; }
	| '(' formal_args ')'
		{ $$ = $2; }
	;

optional_dice
	:
		{ $$ = ""; }
	| DICE_LIT
		{ $$ = $1; }
	;

optional_block
	:
		{ $$ = NULL; }
	| '{' optional_statements '}'
		{ $$ = $2; }
	;

table_entry_list
	:
		{ $$ = NULL; }
	| table_entries
		{ $$ = $1; }
	;

table_entries
	: table_entry
		{ $$ = listNew(LT_ENTRIES, $1); }
	| table_entries table_entry
		{ listAdd($1, $2); $$ = $1; }
	;

table_entry
	: INT_LIT ':'
		{ $$ = tableEntryNew($1, 0, NULL, NULL, NULL); }
	| INT_LIT ':' '(' expression ')'
		{ $$ = tableEntryNew($1, 0, NULL, $4, NULL); }
	| INT_LIT ':' '(' expression ')' '{' optional_statements '}'
		{ $$ = tableEntryNew($1, 0, NULL, $4, $7); }
	| INT_LIT ':' '{' optional_statements '}' '(' expression ')'
		{ $$ = tableEntryNew($1, 0, $4, $7, NULL); }
	| INT_LIT ':' '{' optional_statements '}'
		{ $$ = tableEntryNew($1, 0, $4, NULL, NULL); }
	| INT_LIT '-' INT_LIT ':'
		{ $$ = tableEntryNew($1, $3, NULL, NULL, NULL); }
	| INT_LIT '-' INT_LIT ':' '(' expression ')'
		{ $$ = tableEntryNew($1, $3, NULL, $6, NULL); }
	| INT_LIT '-' INT_LIT ':' '(' expression ')' '{' optional_statements '}'
		{ $$ = tableEntryNew($1, $3, NULL, $6, $9); }
	| INT_LIT '-' INT_LIT ':' '{' optional_statements '}' '(' expression ')'
		{ $$ = tableEntryNew($1, $3, $6, $9, NULL); }
	| INT_LIT '-' INT_LIT ':' '{' optional_statements '}'
		{ $$ = tableEntryNew($1, $3, $6, NULL, NULL); }
	;

%%
