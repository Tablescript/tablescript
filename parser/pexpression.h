/* pexpression.h

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

#ifndef _PARSER_EXPRESSION_H_
#define _PARSER_EXPRESSION_H_

#include "pstructs.h"

struct PExpr *exprNew(enum PExprTag t, int lineNumber);
struct PExpr *exprNewE(enum PExprTag t, int lineNumber, struct PExpr *e1);
struct PExpr *exprNewEE(enum PExprTag t, int lineNumber, struct PExpr *e1, struct PExpr *e2);
struct PExpr *exprNewEEE(enum PExprTag t, int lineNumber, struct PExpr *e1, struct PExpr *e2, struct PExpr *e3);
struct PExpr *exprNewEL(enum PExprTag t, int lineNumber, struct PExpr *e1, struct PList *l);
struct PExpr *exprNewESL(enum PExprTag t, int lineNumber, struct PExpr *e1, char *s, struct PList *l);
struct PExpr *exprNewES(enum PExprTag t, int lineNumber, struct PExpr *e1, char *s);
struct PExpr *exprNewSL(enum PExprTag t, int lineNumber, char *s, struct PList *l);
struct PExpr *exprNewL(enum PExprTag t, int lineNumber, struct PList *l);
struct PExpr *exprNewI(enum PExprTag t, int lineNumber, int i);
struct PExpr *exprNewF(enum PExprTag t, int lineNumber, float f);
struct PExpr *exprNewS(enum PExprTag t, int lineNumber, char *s);
void exprDelete(struct PExpr *e);

#endif
