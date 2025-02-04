#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>

#include "Common.h"

// prototype
INT PrintMenu();
VOID RequestNumber(LPINT lpNumberList);
VOID ReleaseNumber(LPINT lpNumberList);

INT _tmain()
{
	INT aNumberList[NUMBER_LIST_SIZE];
	INT iChoice;
	while (TRUE)
	{
		iChoice = PrintMenu();
		switch (iChoice)
		{
		case REQUEST_NUMBER:
			RequestNumber(aNumberList); break;
		case RELEASE_NUMBER:
			ReleaseNumber(aNumberList); break;
		case EXIT:
			break;
		default:
			_tprintf(_T(" *** Invalid choice\n")); break;
		}

		if (iChoice == EXIT)
			break;
	}

	return 0;
}

INT PrintMenu()
{
	INT iChoice;
	_tprintf(_T("\n---------------------------------\n"));
	_tprintf(_T("     INTEGER POOL - CLIENT\n"));
	_tprintf(_T("---------------------------------\n"));
	_tprintf(_T("1. Request a number\n"));
	_tprintf(_T("2. Release a number\n"));
	_tprintf(_T("3. Exit\n"));
	_tprintf(_T("\nChoice: "));
	_tscanf_s(_T("%d"), &iChoice);
	return iChoice;
}

VOID RequestNumber(LPINT lpNumberList)
{
	INT iNumber;
	_tprintf(_T("\n---------------------------------\n"));
	_tprintf(_T("  REQUEST A NUMBER\n"));
	_tprintf(_T("---------------------------------\n"));
	_tprintf(_T("Number: "));
	_tscanf_s(_T("%d"), &iNumber);

	// create a request
	Request request;
	request.process_id = GetCurrentProcessId();
	request.request_type = REQUEST_NUMBER;
	request.value = iNumber;

	// send the request to the IPManager

	// update the number list
}

VOID ReleaseNumber(LPINT lpNumberList)
{
	INT iNumberIndex;
	_tprintf(_T("\n---------------------------------\n"));
	_tprintf(_T("  RELEASE A NUMBER\n"));
	_tprintf(_T("---------------------------------\n"));
	for (INT i = 0; i < NUMBER_LIST_SIZE; i++)
	{
		_tprintf(_T("%d - %d\n"), i, lpNumberList[i]);
	}
	_tprintf(_T("\nIndex: "));
	_tscanf_s(_T("%d"), &iNumberIndex);

	// create a release request
	Request request;
	request.process_id = GetCurrentProcessId();
	request.request_type = RELEASE_NUMBER;
	request.value = lpNumberList[iNumberIndex];

	// send request to the server

	// remove number from the number list
}