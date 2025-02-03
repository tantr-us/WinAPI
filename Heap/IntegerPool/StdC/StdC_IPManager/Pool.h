#pragma once
#include <Windows.h>

typedef struct ClientNode 
{
	int id;
	struct ClientNode *next;
} ClientNode;

typedef struct PoolNode
{
	int value;
	BOOL bIsInUsed;
	ClientNode* client;
	struct PoolNode* next;
} PoolNode;


PoolNode* CreatePoolNode(int value, ClientNode *client);
