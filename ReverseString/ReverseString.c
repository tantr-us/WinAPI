#include <windows.h>
#include <tchar.h>

#define BUFFER_SIZE 64


VOID PrintErrorMessage(DWORD dwErrorCode);
VOID ReverseString();

int _tmain()
{
	HANDLE hConsoleInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD dwNumberOfByteToRead;
	BOOL bReadResult = FALSE;

	TCHAR sExit[5] = _T("exit");

	while (TRUE)
	{
		TCHAR lpBuffer[BUFFER_SIZE] = { 0 };
		_tprintf(_T("Enter a string: "));
		bReadResult  = ReadConsole(hConsoleInput, (LPVOID)lpBuffer, BUFFER_SIZE, &dwNumberOfByteToRead, NULL);

		if (!bReadResult)
		{
			PrintErrorMessage(GetLastError());
		}
		else
		{
			TCHAR* token = _tcstok(lpBuffer, _T("\r\n"));
			if (_tcscmp(token, sExit) == 0)
			{
				_tprintf(_T("\n >> Goodbye! <<\n"));
				break;
			}
			else
			{
				_tprintf(_T("\n > Your string: %s\n\n"), token);
			}
		}
	}

	CloseHandle(hConsoleInput);
	return 0;
}

/**
 *  @brief      Retrieve the system error message for the last-error code
 *
 *  @param      dwErrorCode    Error code returned from GetLastError().
 */
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


void ReverseString()
{
	// placeholder
}