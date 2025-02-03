#include <stdio.h>
#include <stdlib.h>

#include "Pool.h"

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