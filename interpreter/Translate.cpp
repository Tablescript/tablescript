/* Translate.cpp

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

#include "Translate.h"
#include "Block.h"
#include "Expression.h"
#include "IfStatement.h"
#include "ForStatement.h"
#include "WhileStatement.h"
#include "ImportStatement.h"
#include "FunctionStatement.h"
#include "ExpressionStatement.h"
#include "ClassStatement.h"
#include "MethodMap.h" // TODO

#include "UnaryExpression.h"
#include "BinaryExpression.h"
#include "AssignmentExpression.h"
#include "IntegerLiteral.h"
#include "FloatLiteral.h"
#include "StringLiteral.h"
#include "DiceLiteral.h"
#include "Identifier.h"
#include "ConditionalExpression.h"
#include "ElementExpression.h"
#include "CallExpression.h"
#include "ListLiteral.h"
#include "TableStatement.h"
#include "TableEntry.h"
#include "BreakStatement.h"
#include "ContinueStatement.h"
#include "ExitStatement.h"
#include "ReturnStatement.h"
#include "NoneLiteral.h"
#include "MapLiteral.h"
#include "IncDecExpression.h"
#include "MemberExpression.h"
#include "MethodExpression.h"

#include "../parser/pstructs.h"

#include <iostream>

extern "C" struct PList *ts_parseTree;

namespace TS
{

	// translateParseTree()
	//
	Block *translateParseTree()
	{

		return translateBlock(ts_parseTree);
	}

	// translateBlock()
	//
	Block *translateBlock(struct PList *b)
	{

		Block *block = new Block;

		if(b)
		{

			struct PListElement *le = b->front;
			while(le)
			{

				Statement *s = translateStatement(static_cast<struct PStmt *>(le->data));
				block->addStatement(s);

				le = le->next;
			}
		}

		return block;
	}

	// translateStatement()
	//
	Statement *translateStatement(struct PStmt *s)
	{

		Statement *result = 0;
		Expression *e1;
		Block *b1, *b2;
		ElseIfList *elseifList;
		StringList *stringList;
		TableEntryList *tableEntryList;
		MethodMap *methodMap;

		switch(s->tag)
		{

		case ST_IF:
			e1 = translateExpression(s->e);
			b1 = translateBlock(s->l1);
			elseifList = translateElseIfList(s->l2);
			b2 = translateBlock(s->l3);
			result = new IfStatement(s->lineNumber, e1, b1, elseifList, b2);
			break;

		case ST_FOR:
			e1 = translateExpression(s->e);
			b1 = translateBlock(s->l1);
			result = new ForStatement(s->lineNumber, s->s1, e1, b1);
			break;

		case ST_WHILE:
			e1 = translateExpression(s->e);
			b1 = translateBlock(s->l1);
			result = new WhileStatement(s->lineNumber, e1, b1);
			break;

		case ST_IMPORT:
			e1 = translateExpression(s->e);
			result = new ImportStatement(s->lineNumber, e1);
			break;

		case ST_EXPR:
			e1 = translateExpression(s->e);
			result = new ExpressionStatement(s->lineNumber, e1);
			break;

		case ST_FUNCTION:
			stringList = translateStringList(s->l1);
			b1 = translateBlock(s->l2);
			result = new FunctionStatement(s->lineNumber, s->s1, stringList, b1);
			break;

		case ST_TABLE:
			stringList = translateStringList(s->l1);
			b1 = translateBlock(s->l2);
			tableEntryList = translateTableEntryList(s->l3);
			result = new TableStatement(s->lineNumber, s->s1, stringList, s->s2, b1, tableEntryList);
			break;

		case ST_BREAK:
			result = new BreakStatement(s->lineNumber);
			break;

		case ST_CONTINUE:
			result = new ContinueStatement(s->lineNumber);
			break;

        case ST_EXIT:
            result = new ExitStatement(s->lineNumber);
            break;

		case ST_RETURN:
			result = new ReturnStatement(s->lineNumber, translateExpression(s->e));
			break;

		case ST_CLASS:
			methodMap = translateMethodMap( s->l1 );
			result = new ClassStatement( s->lineNumber, s->s1, methodMap );
			break;

		default:
			break;
		}

		return result;
	}

	// translateStringList()
	//
	StringList *translateStringList(struct PList *l)
	{

		StringList *list = new StringList;

		if(l)
		{

			struct PListElement *le = l->front;
			while(le)
			{

				list->push_back(std::string(static_cast<char *>(le->data)));
				le = le->next;
			}
		}

		return list;
	}

	// translateElseIfList()
	//
	ElseIfList *translateElseIfList(struct PList *l)
	{

		ElseIfList *list = new ElseIfList;
		Expression *test;
		Block *block;

		// if there are no elseifs, return an empty list
		if(l)
		{

			struct PListElement *le = l->front;
			while(le)
			{

				struct PElseIf *elseif = static_cast<struct PElseIf *>(le->data);
				test = translateExpression(elseif->test);
				block = translateBlock(elseif->block);
				list->push_back(new ElseIf(test, block));
				le = le->next;
			}
		}

		return list;
	}

	// translateExpressionList()
	//
	ExpressionList *translateExpressionList(struct PList *list)
	{

		ExpressionList *result = new ExpressionList;

		if(list)
		{

			struct PListElement *le = list->front;
			while(le)
			{

				Expression *e = translateExpression(static_cast<struct PExpr *>(le->data));
				result->push_back(e);

				le = le->next;
			}
		}

		return result;
	}

	// translateTableEntryList()
	//
	TableEntryList *translateTableEntryList(struct PList *l)
	{

		TableEntryList *result = new TableEntryList;

		if(l)
		{

			struct PListElement *le = l->front;
			while(le)
			{

				struct PTableEntry *te = static_cast<struct PTableEntry *>(le->data);
				Block *b1 = 0;
				Expression *e = 0;
				Block *b2 = 0;
				if(te->block1)
					b1 = translateBlock(te->block1);
				if(te->expr)
					e = translateExpression(te->expr);
				if(te->block2)
					b2 = translateBlock(te->block2);
				result->push_back(new TableEntry(te->low, te->high, b1, e, b2));

				le = le->next;
			}
		}

		return result;
	}

	// translatePairList()
	//
	PairList *translatePairList(struct PList *l)
	{

		PairList *result = new PairList;

		if(l)
		{

			struct PListElement *le = l->front;
			while(le)
			{

				struct PPair *p = static_cast<struct PPair *>(le->data);
				Expression *e1 = translateExpression(p->name);
				Expression *e2 = translateExpression(p->value);
				result->push_back(new Pair(e1, e2));

				le = le->next;
			}
		}

		return result;
	}

	// translateMethodMap()
	//
	MethodMap *translateMethodMap( struct PList *l )
	{

		MethodMap *result = new MethodMap;

		if ( l )
		{

			struct PListElement *le = l->front;
			while ( le )
			{

				Statement *s = translateStatement( static_cast< struct PStmt * >( le->data ) );
				FunctionStatement *fs = dynamic_cast< FunctionStatement * >( s );
				result->insert( std::make_pair( fs->getName(), fs ) );

				le = le->next;
			}
		}

		return result;
	}

	// translateExpression()
	//
	Expression *translateExpression(struct PExpr *e)
	{

		Expression *result = 0;
		Expression *e1, *e2, *e3;
		ExpressionList *el;
		PairList *pl;

		switch(e->tag)
		{

		case ET_AND:
		case ET_OR:
		case ET_ADD:
		case ET_SUB:
		case ET_MUL:
		case ET_DIV:
		case ET_MOD:
		case ET_EQ:
		case ET_NE:
		case ET_LT:
		case ET_GT:
		case ET_LE:
		case ET_GE:
		case ET_IN:
			e1 = translateExpression(e->e1);
			e2 = translateExpression(e->e2);
			result = new BinaryExpression(e->lineNumber, e->tag, e1, e2);
			break;

		case ET_POS:
		case ET_NEG:
		case ET_NOT:
			e1 = translateExpression(e->e1);
			result = new UnaryExpression(e->lineNumber, e->tag, e1);
			break;

		case ET_CALL:
			e1 = translateExpression(e->e1);
			el = translateExpressionList(e->l);
			result = new CallExpression(e->lineNumber, e1, el);
			break;

		case ET_MEMBER:
			e1 = translateExpression(e->e1);
			result = new MemberExpression(e->lineNumber, e1, e->s);
			break;

		case ET_METHOD:
			e1 = translateExpression(e->e1);
			el = translateExpressionList(e->l);
			result = new MethodExpression(e->lineNumber, e1, e->s, el);
			break;

		case ET_ELEMENT:
			e1 = translateExpression(e->e1);
			e2 = translateExpression(e->e2);
			result = new ElementExpression(e->lineNumber, e1, e2);
			break;

		case ET_SLICE:
			break;

		case ET_ASSIGN:
		case ET_ADD_ASSIGN:
		case ET_SUB_ASSIGN:
		case ET_MUL_ASSIGN:
		case ET_DIV_ASSIGN:
			e1 = translateExpression(e->e1);
			e2 = translateExpression(e->e2);
			result = new AssignmentExpression(e->lineNumber, e1, e2);
			break;

		case ET_INT_LIT:
			result = new IntegerLiteral(e->lineNumber, e->i);
			break;

		case ET_STRING_LIT:
			el = translateExpressionList(e->l);
			result = new StringLiteral(e->lineNumber, e->s, el);
			break;

		case ET_FLOAT_LIT:
			result = new FloatLiteral(e->lineNumber, e->f);
			break;

		case ET_DICE_LIT:
			result = new DiceLiteral(e->lineNumber, e->s);
			break;

		case ET_LIST_LIT:
			el = translateExpressionList(e->l);
			result = new ListLiteral(e->lineNumber, el);
			break;

		case ET_MAP_LIT:
			pl = translatePairList(e->l);
			result = new MapLiteral(e->lineNumber, pl);
			break;

		case ET_NONE_LIT:
			result = new NoneLiteral(e->lineNumber);
			break;

		case ET_IDENTIFIER:
			result = new Identifier(e->lineNumber, e->s);
			break;

		case ET_POST_INC:
		case ET_POST_DEC:
		case ET_PRE_INC:
		case ET_PRE_DEC:
			e1 = translateExpression(e->e1);
			result = new IncDecExpression(e->lineNumber, e->tag, e1);
			break;

		case ET_CONDITIONAL:
			e1 = translateExpression(e->e1);
			e2 = translateExpression(e->e2);
			e3 = translateExpression(e->e3);
			result = new ConditionalExpression(e->lineNumber, e1, e2, e3);
			break;

		default:
			break;
		}

		return result;
	}

}
