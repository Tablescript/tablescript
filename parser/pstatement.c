/* pstatement.c

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

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "pstatement.h"
#include "pexpression.h"
#include "plist.h"

#ifdef WIN32
#include <malloc.h>
#endif

/* elseifNew()
 *
 */
struct PElseIf *elseifNew(struct PExpr *test, struct PList *block)
{

	struct PElseIf *ei = (struct PElseIf *) malloc(sizeof(struct PElseIf));
	ei->test = test;
	ei->block = block;
	return ei;
}

/* tableEntryNew()
 *
 */
struct PTableEntry *tableEntryNew(int low, int high, struct PList *b1, struct PExpr *e, struct PList *b2)
{

	struct PTableEntry *te = (struct PTableEntry *) malloc(sizeof(struct PTableEntry));
	te->low = low;
	te->high = high;
	te->block1 = b1;
	te->expr = e;
	te->block2 = b2;
	return te;
}

/* pairNew()
 *
 */
struct PPair *pairNew(struct PExpr *name, struct PExpr *value)
{

	struct PPair *p = (struct PPair *) malloc(sizeof(struct PPair));
	p->name = name;
	p->value = value;
	return p;
}

/* stmtNew()
 *
 */
struct PStmt *stmtNew(enum PStmtTag tag, int lineNumber)
{

	struct PStmt *s = (struct PStmt *) malloc(sizeof(struct PStmt));
	s->tag = tag;
	s->lineNumber = lineNumber;
	return s;
}

/* stmtNewIf()
 *
 */
struct PStmt *stmtNewIf(int lineNumber, struct PExpr *test, struct PList *ifBlock, struct PList *elseifs, struct PList *elseBlock)
{

	struct PStmt *s = stmtNew(ST_IF, lineNumber);
	s->e = test;
	s->l1 = ifBlock;
	s->l2 = elseifs;
	s->l3 = elseBlock;
	return s;
}

/* stmtNewFor()
 *
 */
struct PStmt *stmtNewFor(int lineNumber, char *id, struct PExpr *list, struct PList *block)
{

	struct PStmt *s = stmtNew(ST_FOR, lineNumber);
	s->s1 = id;
	s->e = list;
	s->l1 = block;
	return s;
}

/* stmtNewWhile()
 *
 */
struct PStmt *stmtNewWhile(int lineNumber, struct PExpr *test, struct PList *block)
{

	struct PStmt *s = stmtNew(ST_WHILE, lineNumber);
	s->e = test;
	s->l1 = block;
	return s;
}

/* stmtNewFunction()
 *
 */
struct PStmt *stmtNewFunction(int lineNumber, char *name, struct PList *fargs, struct PList *block)
{

	struct PStmt *s = stmtNew(ST_FUNCTION, lineNumber);
	s->s1 = name;
	s->l1 = fargs;
	s->l2 = block;
	return s;
}

/* stmtNewImport()
 *
 */
struct PStmt *stmtNewImport(int lineNumber, struct PExpr *expr)
{

	struct PStmt *s = stmtNew(ST_IMPORT, lineNumber);
	s->e = expr;
	return s;
}

/* stmtNewExpr()
 *
 */
struct PStmt *stmtNewExpr(int lineNumber, struct PExpr *expr)
{

	struct PStmt *s = stmtNew(ST_EXPR, lineNumber);
	s->e = expr;
	return s;
}

/* stmtNewTable()
 *
 */
struct PStmt *stmtNewTable(int lineNumber, char *name, struct PList *args, char *dice, struct PList *block, struct PList *entries)
{

	struct PStmt *s = stmtNew(ST_TABLE, lineNumber);
	s->s1 = name;
	s->l1 = args;
	s->s2 = dice;
	s->l2 = block;
	s->l3 = entries;
	return s;
}

/* stmtNewBreak()
 *
 */
struct PStmt *stmtNewBreak(int lineNumber)
{

	return stmtNew(ST_BREAK, lineNumber);
}

/* stmtNewContinue()
 *
 */
struct PStmt *stmtNewContinue(int lineNumber)
{

	return stmtNew(ST_CONTINUE, lineNumber);
}

/* stmtNewExit()
 *
 */
struct PStmt *stmtNewExit(int lineNumber)
{

    return stmtNew(ST_EXIT, lineNumber);
}

/* stmtNewReturn()
 *
 */
struct PStmt *stmtNewReturn(int lineNumber, struct PExpr* expr)
{

	struct PStmt *s = stmtNew(ST_RETURN, lineNumber);
	s->e = expr;
	return s;
}

struct PStmt *stmtNewClass(int lineNumber, char *name, struct PList *methods)
{

	struct PStmt *s = stmtNew(ST_CLASS, lineNumber);
	s->s1 = name;
	s->l1 = methods;
	return s;
}

/* stmtDelete()
 *
 */
void statementDelete(struct PStmt *s)
{

	if(s->e) exprDelete(s->e);
	if(s->l1) listDelete(s->l1);
	if(s->l2) listDelete(s->l2);
	if(s->l3) listDelete(s->l3);
	if(s->s1) free(s->s1);
	if(s->s2) free(s->s2);

	free(s);
}
