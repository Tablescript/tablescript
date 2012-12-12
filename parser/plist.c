/* plist.c

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
#include "pstructs.h"

/* listElementNew()
 *
 */
struct PListElement *listElementNew(void *data)
{

	struct PListElement *le = (struct PListElement *) malloc(sizeof(struct PListElement));
	le->data = data;
	le->next = NULL;
	return le;
}

/* listNew()
 *
 */
struct PList *listNew(enum PListTag t, void *data)
{

	struct PList *l = (struct PList *) malloc(sizeof(struct PList));
	l->tag = t;
	l->front = listElementNew(data);
	l->back = l->front;
	return l;
}

/* listDelete()
 *
 */
void listDelete(struct PList *l)
{

	struct PListElement *next;
	struct PListElement *element = l->front;
	while(element != NULL)
	{

		next = element->next;
		free(element);
		element = next;
	}

	free(l);
}

/* listAdd()
 *
 */
void listAdd(struct PList *l, void *data)
{

	struct PListElement *le = listElementNew(data);

	if(l->front == NULL)
	{

		l->front = le;
		l->back = le;
		return;
	}

	l->back->next = le;
	l->back = le;
}
