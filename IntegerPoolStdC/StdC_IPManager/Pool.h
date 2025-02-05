#pragma once
#include <Windows.h>

typedef struct ClientNode 
{
	int id;
	struct ClientNode *next;
} ClientNode, *LPClientNode;

typedef struct PoolNode
{
	int value;
	BOOL bIsInUsed;
	ClientNode* client;
	struct PoolNode* next;
} PoolNode, *LPPoolNode;

typedef struct LList
{
	LPVOID head;
	LPVOID tail;
	size_t size;
} LList, *LPLList;

PoolNode* CreatePoolNode(int value, ClientNode *client);
LPLList LList_Init();