/* pdump.h

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

#ifndef _PARSER_DUMP_H_
#define _PARSER_DUMP_H_

#include "pstructs.h"

typedef void (*listDumpFunc)(struct PListElement *, int);
void listDump(struct PList *l, int indent);
void listDumpString(struct PListElement *le, int indent);
void listDumpStmt(struct PListElement *le, int indent);
void listDumpExpr(struct PListElement *le, int indent);
void listDumpEntry(struct PListElement *le, int indent);
void listDumpResult(struct PListElement *le, int indent);
void listDumpElseIf(struct PListElement *le, int indent);
void listDumpPair(struct PListElement *le, int indent);
void listDumpMethod(struct PListElement *le, int indent);

typedef void (*stmtDumpFunc)(struct PStmt *, int);
void stmtDump(struct PStmt *s, int indent);
void stmtDumpIf(struct PStmt *s, int indent);
void stmtDumpFor(struct PStmt *s, int indent);
void stmtDumpWhile(struct PStmt *s, int indent);
void stmtDumpFunction(struct PStmt *s, int indent);
void stmtDumpImport(struct PStmt *s, int indent);
void stmtDumpExpr(struct PStmt *s, int indent);
void stmtDumpTable(struct PStmt *s, int indent);
void stmtDumpBreak(struct PStmt *s, int indent);
void stmtDumpContinue(struct PStmt *s, int indent);
void stmtDumpExit(struct PStmt *s, int indent);
void stmtDumpReturn(struct PStmt *s, int indent);
void stmtDumpClass(struct PStmt *s, int indent);

typedef void (*exprDumpFunc)(struct PExpr *, int);
void exprDump(struct PExpr *e, int indent);
void exprDumpE(struct PExpr *e, int indent);
void exprDumpEE(struct PExpr *e, int indent);
void exprDumpEEE(struct PExpr *e, int indent);
void exprDumpEL(struct PExpr *e, int indent);
void exprDumpSL(struct PExpr *e, int indent);
void exprDumpL(struct PExpr *e, int indent);
void exprDumpI(struct PExpr *e, int indent);
void exprDumpF(struct PExpr *e, int indent);
void exprDumpS(struct PExpr *e, int indent);

#endif
