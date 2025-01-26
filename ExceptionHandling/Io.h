#pragma once
#include <windows.h>
#include <tchar.h>

// define Exception code
#define START_WITH_DIGIT 0xE0000001		// input string start with an number
#define RESERVED_KEYWORD 0xE0000002		// input string match a certain keyword

#define BUFFER_SIZE 32

INT ReadInputString();
VOID ValidateInputString(TCHAR* lpBuffer);
DWORD ExceptionFilter(DWORD dwExceptionCode, LPDWORD lpError);