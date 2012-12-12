/* pdump.c

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

#include <string.h>
#include <stdio.h>
#include "pdump.h"

struct { char *name; listDumpFunc df; } listDumpFuncs[] = {
	{ "LT_STRINGS", listDumpString },
	{ "LT_EXPRS", listDumpExpr },
	{ "LT_STMTS", listDumpStmt },
	{ "LT_ENTRIES", listDumpEntry },
	{ "LT_RESULTS", listDumpResult },
	{ "LT_ELSEIFS", listDumpElseIf },
	{ "LT_PAIRS", listDumpPair },
	{ "LT_METHODS", listDumpMethod } };

void prepareSpaces( char *spaces, int spacesSize, int indent )
{
	
	memset( spaces, ' ', spacesSize );
	spaces[ indent * 2 ] = 0;
}

/* listDump()
 *
 */
void listDump(struct PList *l, int indent)
{

	char spaces[100];
	struct PListElement *le;

	prepareSpaces( spaces, 100, indent );

	if(!l)
	{

		printf("%sNULL\n", spaces);
		return;
	}

	printf("%s%s:\n", spaces, listDumpFuncs[l->tag].name);

	le = l->front;
	while(le != NULL)
	{

		listDumpFuncs[l->tag].df(le, indent + 1);
		le = le->next;
	}
}

/* listDumpString()
 *
 */
void listDumpString(struct PListElement *le, int indent)
{

	char spaces[100];
	
	prepareSpaces( spaces, 100, indent );

	printf("%s%s\n", spaces, (char *) le->data);
}

/* listDumpStmt()
 *
 */
void listDumpStmt(struct PListElement *le, int indent)
{

	stmtDump((struct PStmt *) le->data, indent);
}

/* listDumpExpr()
 *
 */
void listDumpExpr(struct PListElement *le, int indent)
{

	exprDump((struct PExpr *) le->data, indent);
}

/* listDumpEntry()
 *
 */
void listDumpEntry(struct PListElement *le, int indent)
{

	struct PTableEntry *te = (struct PTableEntry *) le->data;
	char spaces[100];
	
	prepareSpaces( spaces, 100, indent );

	printf("%sENTRY:\n", spaces);
	if(te->low == -1)
			printf("%s  ROLLS: N/A\n", spaces);
	else
		if(te->high == -1)
			printf("%s  ROLLS: %d", spaces, te->low);
		else
			printf("%s  ROLLS: %d-%d", spaces, te->low, te->high);
	//printf("%s  RESULTS:\n", spaces);
	printf("%sPRE:\n", spaces);
	listDump(te->block1, indent + 1);
	printf("%sEXPR:\n", spaces);
	exprDump(te->expr, indent + 1);
	printf("%sPOST:\n", spaces);
	listDump(te->block2, indent + 1);
}

/* listDumpResult()
 *
 */
void listDumpResult(struct PListElement *le, int indent)
{
	
}

/* listDumpElseIf()
 *
 */
void listDumpElseIf(struct PListElement *le, int indent)
{

	struct PElseIf *elseif = (struct PElseIf *) le->data;

	exprDump(elseif->test, indent);
	listDump(elseif->block, indent);
}

/* listDumpPair()
 *
 */
void listDumpPair(struct PListElement *le, int indent)
{

	struct PPair *pair = (struct PPair *) le->data;

	exprDump(pair->name, indent);
	exprDump(pair->value, indent);
}

/* listDumpMethod()
 *
 */
void listDumpMethod(struct PListElement *le, int indent)
{
	
	stmtDump((struct PStmt *) le->data, indent);
}

struct { char *name; stmtDumpFunc df; } stmtDumpFuncs[] = {
	{ "ST_IF", stmtDumpIf },
	{ "ST_FOR", stmtDumpFor },
	{ "ST_WHILE", stmtDumpWhile },
	{ "ST_FUNCTION", stmtDumpFunction },
	{ "ST_IMPORT", stmtDumpImport },
	{ "ST_EXPR", stmtDumpExpr },
	{ "ST_TABLE", stmtDumpTable },
	{ "ST_BREAK", stmtDumpBreak },
	{ "ST_CONTINUE", stmtDumpContinue },
    { "ST_EXIT", stmtDumpExit },
	{ "ST_RETURN", stmtDumpExpr },
	{ "ST_CLASS", stmtDumpClass } };

/* stmtDump()
 *
 */
void stmtDump(struct PStmt *s, int indent)
{

	char spaces[100];
	
	prepareSpaces( spaces, 100, indent );

	if(!s)
	{

		printf("%sNULL\n", spaces);
		return;
	}

	printf("%s%s:\n", spaces, stmtDumpFuncs[s->tag].name);
	stmtDumpFuncs[s->tag].df(s, indent + 1);
}

/* stmtDumpIf()
 *
 */
void stmtDumpIf(struct PStmt *s, int indent)
{

	char spaces[100];
	
	prepareSpaces( spaces, 100, indent );

	printf("%sCONDITION:\n", spaces);
	exprDump(s->e, indent + 1);
	printf("%sIF BLOCK:\n", spaces);
	listDump(s->l1, indent + 1);
	if(s->l2)
	{

		printf("%sELSEIFS:\n", spaces);
		listDump(s->l2, indent + 1);
	}
	if(s->l3)
	{

		printf("%sELSE:\n", spaces);
		listDump(s->l3, indent + 1);
	}
}

/* stmtDumpFor()
 *
 */
void stmtDumpFor(struct PStmt *s, int indent)
{

	char spaces[100];
	
	prepareSpaces( spaces, 100, indent );

	printf("%sIDENTIFIER: %s\n", spaces, s->s1);
	exprDump(s->e, indent + 1);
	listDump(s->l1, indent + 1);
}

/* stmtDumpWhile()
 *
 */
void stmtDumpWhile(struct PStmt *s, int indent)
{

	char spaces[100];
	
	prepareSpaces( spaces, 100, indent );

	printf("%sCONDITION:\n", spaces);
	exprDump(s->e, indent + 1);
	printf("%sBLOCK:\n", spaces);
	listDump(s->l1, indent + 1);
}

/* stmtDumpFunction()
 *
 */
void stmtDumpFunction(struct PStmt *s, int indent)
{

	char spaces[100];
	
	prepareSpaces( spaces, 100, indent );

	printf("%sNAME: %s\n", spaces, s->s1);
	if(s->l1)
	{

		printf("%sARGS:\n", spaces);
		listDump(s->l1, indent + 1);
	}
	printf("%sBLOCK:\n", spaces);
	listDump(s->l2, indent + 1);
}

/* stmtDumpImport()
 *
 */
void stmtDumpImport(struct PStmt *s, int indent)
{

	char spaces[100];
	
	prepareSpaces( spaces, 100, indent );

	printf("%sMODULE:\n", spaces);
	exprDump(s->e, indent + 1);
}

/* stmtDumpExpr()
 *
 */
void stmtDumpExpr(struct PStmt *s, int indent)
{

	exprDump(s->e, indent);
}

/* stmtDumpTable()
 *
 */
void stmtDumpTable(struct PStmt *s, int indent)
{

	char spaces[100];
	
	prepareSpaces( spaces, 100, indent );

	printf("%sNAME: %s\n", spaces, s->s1);
	printf("%sARGS:\n", spaces);
	listDump(s->l1, indent + 1);
	printf("%sDICE: %s\n", spaces, s->s2 ? s->s2 : "N/A");
	//printf("%sENTRIES:\n", spaces);
	listDump(s->l2, indent);
	listDump(s->l3, indent);
}

void stmtDumpBreak(struct PStmt *s, int indent) {}
void stmtDumpContinue(struct PStmt *s, int indent) {}
void stmtDumpExit(struct PStmt *s, int indent) {}

void stmtDumpReturn(struct PStmt *s, int indent)
{

	exprDump(s->e, indent + 1);
}

/* stmtDumpClass()
 *
 */
void stmtDumpClass(struct PStmt *s, int indent)
{
	
	char spaces[100];
	
	prepareSpaces( spaces, 100, indent );
	
	printf("%sNAME: %s\n", spaces, s->s1);
	if(s->l1)
	{
		
		listDump(s->l1, indent + 1);
	}
}

struct { char *name; exprDumpFunc df; } exprDumpFuncs[] = {
	{ "ET_AND", exprDumpEE },
	{ "ET_OR", exprDumpEE },
	{ "ET_ADD", exprDumpEE },
	{ "ET_SUB", exprDumpEE },
	{ "ET_MUL", exprDumpEE },
	{ "ET_DIV", exprDumpEE },
	{ "ET_MOD", exprDumpEE },
	{ "ET_EQ", exprDumpEE },
	{ "ET_NE", exprDumpEE },
	{ "ET_LT", exprDumpEE },
	{ "ET_GT", exprDumpEE },
	{ "ET_LE", exprDumpEE },
	{ "ET_GE", exprDumpEE },
	{ "ET_POS", exprDumpEE },
	{ "ET_NEG", exprDumpEE },
	{ "ET_NOT", exprDumpEE },
	{ "ET_CALL", exprDumpEL },
	{ "ET_ELEMENT", exprDumpEE },
	{ "ET_SLICE", exprDumpEEE },
	{ "ET_ASSIGN", exprDumpEE },
	{ "ET_ADD_ASSIGN", exprDumpEE },
	{ "ET_SUB_ASSIGN", exprDumpEE },
	{ "ET_MUL_ASSIGN", exprDumpEE },
	{ "ET_DIV_ASSIGN", exprDumpEE },
	{ "ET_INT_LIT", exprDumpI },
	{ "ET_STRING_LIT", exprDumpS },
	{ "ET_FLOAT_LIT", exprDumpF },
	{ "ET_DICE_LIT", exprDumpS },
	{ "ET_LIST_LIT", exprDumpL },
	{ "ET_MAP_LIT", exprDumpL },
	{ "ET_NONE_LIT", NULL },
	{ "ET_IDENTIFIER", exprDumpS },
	{ "ET_POST_INC", exprDumpE },
	{ "ET_POST_DEC", exprDumpE },
	{ "ET_PRE_INC", exprDumpE },
	{ "ET_PRE_DEC", exprDumpE },
	{ "ET_CONDITIONAL", exprDumpEEE },
	{ "ET_IN", exprDumpEE } };

/* exprDump()
 *
 */
void exprDump(struct PExpr *e, int indent)
{

	char spaces[100];
	
	prepareSpaces( spaces, 100, indent );

	if(!e)
	{

		printf("%sNULL\n", spaces);
		return;
	}

	printf("%s%s\n", spaces, exprDumpFuncs[e->tag].name);
	if(exprDumpFuncs[e->tag].df != NULL)
		exprDumpFuncs[e->tag].df(e, indent + 1);
}

/* exprDumpE()
 *
 */
void exprDumpE(struct PExpr *e, int indent)
{

	exprDump(e->e1, indent);
}

/* exprDumpEE()
 *
 */
void exprDumpEE(struct PExpr *e, int indent)
{

	exprDump(e->e1, indent);
	exprDump(e->e2, indent);
}

/* exprDumpEEE()
 *
 */
void exprDumpEEE(struct PExpr *e, int indent)
{

	exprDump(e->e1, indent);
	exprDump(e->e2, indent);
	exprDump(e->e3, indent);
}

/* exprDumpEL()
 *
 */
void exprDumpEL(struct PExpr *e, int indent)
{

	exprDump(e->e1, indent);
	listDump(e->l, indent);
}

/* exprDumpSL()
 *
 */
void exprDumpSL(struct PExpr *e, int indent)
{

	char spaces[100];
	
	prepareSpaces( spaces, 100, indent );

	printf("%s%s\n", spaces, e->s);
	listDump(e->l, indent);
}

/* exprDumpL()
 *
 */
void exprDumpL(struct PExpr *e, int indent)
{

	listDump(e->l, indent);
}

/* exprDumpI()
 *
 */
void exprDumpI(struct PExpr *e, int indent)
{

	char spaces[100];
	
	prepareSpaces( spaces, 100, indent );

	printf("%s%i\n", spaces, e->i);
}

/* exprDumpF()
 *
 */
void exprDumpF(struct PExpr *e, int indent)
{

	char spaces[100];
	
	prepareSpaces( spaces, 100, indent );

	printf("%s%f\n", spaces, e->f);
}

/* exprDumpS()
 *
 */
void exprDumpS(struct PExpr *e, int indent)
{

	char spaces[100];
	
	prepareSpaces( spaces, 100, indent );

	printf("%s\"%s\"\n", spaces, e->s);
}
