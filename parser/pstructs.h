/* pstructs.h

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

#ifndef _PARSER_STRUCTS_H_
#define _PARSER_STRUCTS_H_

/* PListElement
 *
 */
struct PListElement
{

	void *data;
	struct PListElement *next;
};

/* PListTag
 *
 */
enum PListTag
{

	LT_STRINGS = 0,		/* list of strings */
	LT_EXPRS,			/* ... expressions */
	LT_STMTS,			/* ... statements */
	LT_ENTRIES,			/* ... table entries */
	LT_RESULTS,			/* ... entry results */
	LT_ELSEIFS,			/* ... elseifs */
	LT_PAIRS,			/* ... pairs */
	LT_METHODS,			/* ... class methods */
	LTCOUNT
};

/* PList
 *
 */
struct PList
{

	enum PListTag tag;

	struct PListElement *front;
	struct PListElement *back;
};

/* PExprTag
 *
 */
enum PExprTag
{

	ET_AND = 0,
	ET_OR,
	ET_ADD,
	ET_SUB,
	ET_MUL,
	ET_DIV,
	ET_MOD,
	ET_EQ,
	ET_NE,
	ET_LT,
	ET_GT,
	ET_LE,
	ET_GE,
	ET_POS,
	ET_NEG,
	ET_NOT,
	ET_CALL,
	ET_MEMBER,
	ET_METHOD,
	ET_ELEMENT,
	ET_SLICE,
	ET_ASSIGN,
	ET_ADD_ASSIGN,
	ET_SUB_ASSIGN,
	ET_MUL_ASSIGN,
	ET_DIV_ASSIGN,
	ET_INT_LIT,
	ET_STRING_LIT,
	ET_FLOAT_LIT,
	ET_DICE_LIT,
	ET_LIST_LIT,
	ET_MAP_LIT,
	ET_NONE_LIT,
	ET_IDENTIFIER,
	ET_POST_INC,
	ET_POST_DEC,
	ET_PRE_INC,
	ET_PRE_DEC,
	ET_CONDITIONAL,
	ET_IN,
	ETCOUNT
};

/* PExpr
 *
 */
struct PExpr
{

	enum PExprTag tag;

	int lineNumber;

	struct PExpr *e1;
	struct PExpr *e2;
	struct PExpr *e3;
	struct PList *l;
	int i;
	float f;
	char *s;
};

/* PStmtTag
 *
 */
enum PStmtTag
{

	ST_IF = 0,
	ST_FOR,
	ST_WHILE,
	ST_FUNCTION,
	ST_IMPORT,
	ST_EXPR,
	ST_TABLE,
	ST_BREAK,
	ST_CONTINUE,
    ST_EXIT,
	ST_RETURN,
	ST_CLASS,
	STCOUNT
};

/* PStmt
 *
 */
struct PStmt
{

	enum PStmtTag tag;

	int lineNumber;

	struct PExpr *e;
	struct PList *l1;
	struct PList *l2;
	struct PList *l3;
	char *s1;
	char *s2;
};

/* PElseIf
 *
 */
struct PElseIf
{

	struct PExpr *test;
	struct PList *block;
};

/* PTableEntry
 *
 */
struct PTableEntry
{

	int low;
	int high;
	struct PList *block1;
	struct PExpr *expr;
	struct PList *block2;
};

/* PPair
 *
 */
struct PPair
{

	struct PExpr *name;
	struct PExpr *value;
};

#endif
