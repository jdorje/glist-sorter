#include "sorted-list.h"



SortedListPtr SLCreate(CompareFuncT cf, DestructFuncT df)
{
        SortedListPtr sl = NULL;
        sl =  malloc(sizeof(SortedList));
        if (sl != NULL)
        {
		sl->head = sl;
                sl->thing = NULL;
                sl->PtrNext = NULL;
		sl->cf = cf;
		sl->df = df;
                return sl;
        }

        return NULL;
}

SortedListPtr GetSLPFromIndex(int index, SortedListPtr head)
{
	int i = 0;
	if(head != NULL)
	{
		for(SortedListPtr current = head; current->PtrNext != NULL; current = current->PtrNext,i++)
		{
			if(i == index)
			{
				return current;
			}
		}

	}
	return NULL;
}

int SLInsert(SortedListPtr list, void *newObj)
{
	if ((list->thing == NULL) && (list->PtrNext == NULL)) //they are giving us the head, but we cannot check directly
	{
		list->thing = newObj;
		list->PtrNext = NULL;
		return 1;
	}
	
	//int insertbefore = 0;
	SortedListPtr thingThatPointsToUs = list;
	SortedListPtr current = list;
/*
 * "insertbefore" is the index item of the element of the list, that our newly inserted item will point TO.
*/
	BOOL endOfList = FALSE, stillStepping = FALSE;

	do
	{
		int comparison_result = list->cf(current->thing, newObj);
		printf("compare result of %d to %d is %d\n", *((int*)current->thing), *((int*)newObj), comparison_result);
		//It's not doing this comparison enough. Not comparing 3 to 4 after we add it. 
		switch (comparison_result)
		{
			case 0:
				//*(current->thing) == *newObj
				return 0;
			case 1:
				//*(current->thing) > *newObj
				
				if (current->PtrNext != NULL)
				{
					thingThatPointsToUs = current;
					if (current != NULL) {
						current = current->PtrNext;
					}
					continue;
				}
				else
				{
					printf("we're not supposed to be here\n");
					endOfList = TRUE;
				}

				stillStepping = FALSE;
				break; 
			case -1:
				//*(current->thing) < *newObj

				// 1 is in the list, we're trying to add 3
				// ok.
				// 3, 1 are in the list. we want to add 0.
				//
				stillStepping = TRUE;

				break;
			default:
				printf("bad CompareFuncT implementation! exiting\n");
				exit(-1);
		}
		
		if (!stillStepping)
		{
			SortedListPtr newThing = malloc(sizeof(SortedList));
			if(newThing != NULL)
			{
				newThing->thing = newObj;
				//printf("current = %x\n", current);
				//printf("endOfList = %d\n", endOfList);
				newThing->PtrNext = endOfList ? NULL : current;
				//newThing->PtrNext = GetSLPFromIndex(insertbefore, list);
				
				if (thingThatPointsToUs == list->head) {
					//printf("tTPtU's value is %d\n", *((int*)thingThatPointsToUs->thing));
					list->head = newThing;
					printf("we are the new head\n");
				} else {		
					thingThatPointsToUs->PtrNext = newThing;
					printf("set thingThatPointsToUs's PtrNext to %x", thingThatPointsToUs->PtrNext);
				}

				printf("set newThing's PtrNext to %x\n", newThing->PtrNext);

				return 1; 
			}
		}

		thingThatPointsToUs = current;
		current = current->PtrNext;

	} while((current != NULL) && (current->PtrNext != NULL));

	//if we're here, we're adding something to the end of the list.
	SortedListPtr newThing = malloc(sizeof(SortedList));
	if (newThing != NULL)
	{
		newThing->thing = newObj;
		newThing->PtrNext = NULL;
		return 1;
	}	

	printf("unsuccessful insertion\n");
	return 0;
}
