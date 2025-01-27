#include <windows.h>
#include <tchar.h>
#include <stdlib.h>

#define HEAP_INIT_SIZE 16
#define HEAP_MAX_SIZE 32
#define BUFFER_SIZE 8
#define CHOICE_BUFFER_SIZE 4

// function prototype
int PrintMainMenu();
VOID PrintErrorMessage(DWORD dwErrorCode);

int _tmain()
{
	int iMenuChoice;
	HANDLE hHeap = NULL;

	// create heap
	__try
	{
		hHeap = HeapCreate(HEAP_GENERATE_EXCEPTIONS | HEAP_NO_SERIALIZE, HEAP_INIT_SIZE, HEAP_MAX_SIZE);
		
		// allocate heap
		if (hHeap != NULL)
		{
			LPVOID lpHeapBlock = HeapAlloc(hHeap, HEAP_ZERO_MEMORY, HEAP_INIT_SIZE);

			while (TRUE)
			{
				// prompt main menu
				iMenuChoice = PrintMainMenu();

				if (iMenuChoice == 1)
				{
					HANDLE hConsoleIn = GetStdHandle(STD_INPUT_HANDLE);
					TCHAR lpBuffer[BUFFER_SIZE] = { 0 };
					DWORD dwNumberOfByteToRead = 0;

					_tprintf(_T("New String: "));
					BOOL bReadResult = ReadConsole(hConsoleIn, (LPVOID)lpBuffer, BUFFER_SIZE, &dwNumberOfByteToRead, 0);
					FlushConsoleInputBuffer(hConsoleIn);
					if (!bReadResult)
					{
						PrintErrorMessage(GetLastError());
					}
					else
					{

					}
					CloseHandle(hConsoleIn);
				}
				else if (iMenuChoice == 4)
				{
					break;
				}
				else
				{
					_tprintf(_T(" *** Invalid value.\n"));
				}
				// create new string
					// prompt for entering a new string

					// check if heap block has enough memory

					// yes
						// save new string to allocated heap

					// no
						// prompt for clearing the allocated heap
						// yes
						// clear out allocated heap data
						// write current input string to the allocated heap
						// no
						// clear input string from the buffer, return to main menu
				// view saved string
					// list out all saved string ( each string is separated by a NULL '\0' char)

				// delete save string
					// list out saved string
					// enter the string index
					// delete the string from the heap

				_tprintf(_T("\n-----------------------------------------\n\n"));
			}

			// Destroy heap
			if (hHeap != NULL) HeapDestroy(hHeap);
		}
	}
	__except (GetExceptionCode() == STATUS_NO_MEMORY ? EXCEPTION_EXECUTE_HANDLER: EXCEPTION_CONTINUE_SEARCH)
	{
		_tprintf(_T(" *** Exception Raised: Failed to create heap handle.\n"));
		return -1;
	}
	return 0;
}

int PrintMainMenu()
{
	_tprintf(_T("1. Create New String\n2. View Saved String\n3. Delete Saved String\n4. Exit\n\nChoice: "));

	int choice = -1;
	HANDLE hConsoleIn = GetStdHandle(STD_INPUT_HANDLE);
	TCHAR cChoice[CHOICE_BUFFER_SIZE] = { 0 };
	DWORD dwNumberOfByteToRead = 0;
	BOOL bReadResult = ReadConsole(hConsoleIn, (LPVOID)cChoice, CHOICE_BUFFER_SIZE, &dwNumberOfByteToRead, 0);
	cChoice[_tcslen(cChoice)-1] = '\0';
	if (!bReadResult)
	{
		PrintErrorMessage(GetLastError());
	}
	else
	{
		choice = _tstoi(cChoice);
		_tprintf(_T("choice: %d\n"), choice);
	}
	if (!FlushConsoleInputBuffer(hConsoleIn))
	{
		PrintErrorMessage(GetLastError());
	}
	CloseHandle(hConsoleIn);
	return choice;
}

VOID PrintErrorMessage(DWORD dwErrorCode)
{
	// Retrieve the system error message for the last-error code

	LPVOID lpMsgBuf; // Error message

	if (FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dwErrorCode,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0, NULL) == 0)
	{
		_tprintf(_T("FormatMessage failed. Error: %d\n"), GetLastError());
		ExitProcess(dwErrorCode);
	}

	_tprintf(_T("  > Error %d: %s\n"), dwErrorCode, (LPTSTR)lpMsgBuf);

	LocalFree(lpMsgBuf);
	ExitProcess(dwErrorCode);
}