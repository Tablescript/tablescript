/* pstatement.h

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

#ifndef _PARSER_STATEMENT_H_
#define _PARSER_STATEMENT_H_

#include "pstructs.h"

struct PElseIf *elseifNew(struct PExpr *test, struct PList *block);

struct PTableEntry *tableEntryNew(int low, int high, struct PList *b1, struct PExpr *e, struct PList *b2);

struct PPair *pairNew(struct PExpr *name, struct PExpr *value);

struct PStmt *stmtNewIf(int lineNumber, struct PExpr *test, struct PList *ifBlock, struct PList *elseifs, struct PList *elseBlock);
struct PStmt *stmtNewFor(int lineNumber, char *id, struct PExpr *list, struct PList *block);
struct PStmt *stmtNewWhile(int lineNumber, struct PExpr *test, struct PList *block);
struct PStmt *stmtNewFunction(int lineNumber, char *name, struct PList *fargs, struct PList *block);
struct PStmt *stmtNewImport(int lineNumber, struct PExpr *expr);
struct PStmt *stmtNewExpr(int lineNumber, struct PExpr *expr);
struct PStmt *stmtNewTable(int lineNumber, char *name, struct PList *args, char *dice, struct PList *block, struct PList *entries);
struct PStmt *stmtNewBreak(int lineNumber);
struct PStmt *stmtNewContinue(int lineNumber);
struct PStmt *stmtNewExit(int lineNumber);
struct PStmt *stmtNewReturn(int lineNumber, struct PExpr *expr);
struct PStmt *stmtNewClass(int lineNumber, char *name, struct PList *methods);

void stmtDelete(struct PStmt *s);

#endif
