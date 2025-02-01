#include <windows.h>
#include <tchar.h>
#include <stdlib.h>

#define HEAP_INIT_SIZE 16
#define HEAP_MAX_SIZE 32
#define BUFFER_SIZE 8
#define CHOICE_BUFFER_SIZE 4

#define LINE_BREAK_DELIMITER _T("\r\n")

// function prototype
int PrintMainMenu();
void GetStringInput(TCHAR *lpInputString);
void ViewSavedString();
void PrintErrorMessage(DWORD dwErrorCode);


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
					TCHAR *lpInputString = { 0 };
					GetStringInput(lpInputString);

					_tprintf(_T("Your string: %s\n"), lpInputString);

				}
				else if (iMenuChoice == 2)
				{
					ViewSavedString();
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
	int choice = -1;
	_tprintf(_T("1. Create New String\n2. View Saved String\n3. Delete Saved String\n4. Exit\n\nChoice: "));
	_tscanf_s(_T(" %d"), &choice);
	return choice;
}


void GetStringInput(TCHAR *lpInputString)
{
	HANDLE hConsoleInput = GetStdHandle(STD_INPUT_HANDLE);
	TCHAR lpBuffer[BUFFER_SIZE] = { 0 };
	DWORD dwNumOfByteToRead = 0;
	BOOL bReadConsoleResult = ReadConsole(hConsoleInput, (LPVOID)lpBuffer, BUFFER_SIZE, &dwNumOfByteToRead, NULL);
	if (!bReadConsoleResult)
	{
		PrintErrorMessage(GetLastError());
	}
	else
	{
		lpInputString = _tcstok_s(lpBuffer, _T("\r\n"), lpInputString);
	}
	CloseHandle(hConsoleInput);
}

void ViewSavedString()
{
	_tprintf(_T("View Saved String\n"));
}

void PrintErrorMessage(DWORD dwErrorCode)
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