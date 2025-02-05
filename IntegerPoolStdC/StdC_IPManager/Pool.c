#include <stdio.h>
#include <stdlib.h>

#include "Pool.h"

/**
* @brief
* 
* @param
* 
* @return
* 
*/
PoolNode* CreatePoolNode(int value, ClientNode* client)
{
	PoolNode* poolNode = (PoolNode*) malloc(sizeof(PoolNode));
	if (poolNode != NULL)
	{
		poolNode->value = value;
		poolNode->bIsInUsed = TRUE;
		poolNode->client = client;
		poolNode->next = NULL;
	}
	return poolNode;
}

/**
* @brief	Initialize an empty linked list.
* @return	Return a pointer to the linked list.
*/
LPLList LList_Init()
{
	LPLList lpLList = (LPLList)malloc(sizeof(LList));
	if (lpLList != NULL)
	{
		lpLList->head = NULL;
		lpLList->tail = NULL;
		lpLList->size = 0;
	}

	return lpLList;
}