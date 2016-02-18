#include "sorted-list.h"

int compareint(void* int1, void* int2)
{
	if ((int1 != NULL) && (int2 != NULL))
	{
		int i1 = *((int*)int1), i2 = *((int*)int2);

		if (i1 == i2) return 0;
		else if (i1 < i2) return -1;
		else if (i1 > i2) return 1;
	}

	printf("one of them is null\n");
	return -1; //1 or -1, should not matter; just want it inserted into the list
}

void destroyint(void* singledataitem)
{
	return;
	//free(singledataitem);
}

int main(int argc,char* argv[])
{
	SLCreate(NULL,NULL);
	SortedListPtr newPtr = SLCreate(&compareint, &destroyint);
	int i = 0, List[] = {1,3,4,6,2,2};
	for(;i < (sizeof(List) / sizeof(List[0])); i++)
	{
		printf("SLinsert for %d returned %d\n", List[i], SLInsert(newPtr, &List[i]));
		
	}
	
	for(SortedListPtr current = newPtr; current->PtrNext != NULL; current = current->PtrNext)
	{
		printf("hi\n");
		//printf("%d/n", (int)(*((int*)current->thing))); /* desired result: 1 \n 2 \n 3 \n 4 \n 6, preserves order */		
	} 
	return 0;
}
