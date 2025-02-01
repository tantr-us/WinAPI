#include <windows.h>
#include <tchar.h>

#define BUFFER_SIZE 64

<<<<<<< HEAD
VOID PrintErrorMessage(DWORD dwErrorCode);
=======

VOID PrintErrorMessage(DWORD dwErrorCode);
VOID ReverseString();
>>>>>>> e8fa74dea4ed808d5b556d50f806b2361b2eaed1

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
<<<<<<< HEAD
			if (token != NULL) {
				if (_tcscmp(token, sExit) == 0)
				{
					_tprintf(_T("\n >> Goodbye! <<\n"));
					break;
				}
				else
				{
					_tprintf(_T("\n > Your string: %s\n"), token);

					TCHAR lpReveredBuffer[BUFFER_SIZE] = { 0 };

					for (int i = (_tcslen(token)-1), j = 0; i >= 0; i--, j++)
					{
						lpReveredBuffer[j] = token[i];
					}

					_tprintf(_T(" > Reversed string: %s\n\n"), lpReveredBuffer);
				}
=======
			if (_tcscmp(token, sExit) == 0)
			{
				_tprintf(_T("\n >> Goodbye! <<\n"));
				break;
			}
			else
			{
				_tprintf(_T("\n > Your string: %s\n\n"), token);
>>>>>>> e8fa74dea4ed808d5b556d50f806b2361b2eaed1
			}
		}
	}

	CloseHandle(hConsoleInput);
	return 0;
}

/**
 *  @brief      Retrieve the system error message for the last-error code
 *
<<<<<<< HEAD
 *  @param      
 *		DWORD dwErrorCode    Error code returned from GetLastError().
=======
 *  @param      dwErrorCode    Error code returned from GetLastError().
>>>>>>> e8fa74dea4ed808d5b556d50f806b2361b2eaed1
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
<<<<<<< HEAD
=======


void ReverseString()
{
	// placeholder
}
>>>>>>> e8fa74dea4ed808d5b556d50f806b2361b2eaed1
