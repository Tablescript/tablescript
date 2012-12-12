/* main.c
 *
 *
 */

#include <stdio.h>
#include "parser/ts.tab.h"
#include "parser/pdump.h"

extern FILE *yyin;
int yyparse(void);

extern struct PList *ts_parseTree;

int main(int argc, char *argv[])
{

	/*yyin = fopen("newtables.ts", "r");*/
	yyparse();
	listDump(ts_parseTree, 0);

	return 0;
}
