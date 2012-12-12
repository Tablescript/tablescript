/* pexpression.c

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

#include "pexpression.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* exprNew()
 *
 */
struct PExpr *exprNew(enum PExprTag t, int lineNumber)
{

	struct PExpr *e = (struct PExpr *) malloc(sizeof(struct PExpr));
	memset(e, 0, sizeof(struct PExpr));
	e->tag = t;
	e->lineNumber = lineNumber;
	return e;
}

/* exprNewE()
 *
 */
struct PExpr *exprNewE(enum PExprTag t, int lineNumber, struct PExpr *e1)
{

	struct PExpr *e = exprNew(t, lineNumber);
	e->e1 = e1;
	return e;
}

/* exprNewEE()
 *
 */
struct PExpr *exprNewEE(enum PExprTag t, int lineNumber, struct PExpr *e1, struct PExpr *e2)
{

	struct PExpr *e = exprNew(t, lineNumber);
	e->e1 = e1;
	e->e2 = e2;
	return e;
}

/* exprNewEEE()
 *
 */
struct PExpr *exprNewEEE(enum PExprTag t, int lineNumber, struct PExpr *e1, struct PExpr *e2, struct PExpr *e3)
{

	struct PExpr *e = exprNew(t, lineNumber);
	e->e1 = e1;
	e->e2 = e2;
	e->e3 = e3;
	return e;
}

/* exprNewEL()
 *
 */
struct PExpr *exprNewEL(enum PExprTag t, int lineNumber, struct PExpr *e1, struct PList *l)
{

	struct PExpr *e = exprNew(t, lineNumber);
	e->e1 = e1;
	e->l = l;
	return e;
}

/* exprNewESL()
 *
 */
struct PExpr *exprNewESL(enum PExprTag t, int lineNumber, struct PExpr *e1, char *s, struct PList *l)
{

	struct PExpr *e = exprNew(t, lineNumber);
	e->e1 = e1;
	e->s = s;
	e->l = l;
	return e;
}

/* exprNewES()
 *
 */
struct PExpr *exprNewES(enum PExprTag t, int lineNumber, struct PExpr *e1, char *s)
{

	struct PExpr *e = exprNew(t, lineNumber);
	e->e1 = e1;
	e->s = s;
	return e;
}

/* exprNewSL()
 *
 */
struct PExpr *exprNewSL(enum PExprTag t, int lineNumber, char *s, struct PList *l)
{

	struct PExpr *e = exprNew(t, lineNumber);
	e->s = s;
	e->l = l;
	return e;
}

/* exprNewL()
 *
 */
struct PExpr *exprNewL(enum PExprTag t, int lineNumber, struct PList *l)
{

	struct PExpr *e = exprNew(t, lineNumber);
	e->l = l;
	return e;
}

/* exprNewI()
 *
 */
struct PExpr *exprNewI(enum PExprTag t, int lineNumber, int i)
{

	struct PExpr *e = exprNew(t, lineNumber);
	e->i = i;
	return e;
}

/* exprNewF()
 *
 */
struct PExpr *exprNewF(enum PExprTag t, int lineNumber, float f)
{

	struct PExpr *e = exprNew(t, lineNumber);
	e->f = f;
	return e;
}

/* exprNewS()
 *
 */
struct PExpr *exprNewS(enum PExprTag t, int lineNumber, char *s)
{

	struct PExpr *e = exprNew(t, lineNumber);
	e->s = s;
	return e;
}

/* exprDelete()
 *
 */
void exprDelete(struct PExpr *e)
{

	switch(e->tag)
	{

	case ET_AND:
	case ET_OR:
	case ET_ADD:
	case ET_SUB:
	case ET_MUL:
	case ET_DIV:
	case ET_EQ:
	case ET_LT:
	case ET_GT:
	case ET_LE:
	case ET_GE:
		exprDelete(e->e1);
		exprDelete(e->e1);
		break;

	case ET_STRING_LIT:
	case ET_DICE_LIT:
		free(e->s);
		break;

	default:
		break;
	}

	free(e);
}
