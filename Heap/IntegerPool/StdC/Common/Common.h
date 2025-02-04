#ifndef COMMON_H
#define COMMON_H

#include <windows.h>

#define NUMBER_LIST_SIZE 5
#define TRUE 1
#define FALSE 0

// Request type
#define REQUEST_NUMBER 1
#define RELEASE_NUMBER 2
#define EXIT 3

typedef struct Request
{
    DWORD process_id;
    int request_type;
    int value;
} Request;

#endif