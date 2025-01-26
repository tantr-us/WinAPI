#include "Io.h"

INT ReadInputString()
{
	HANDLE hConsoleIn = GetStdHandle(STD_INPUT_HANDLE);
	TCHAR lpBuffer[BUFFER_SIZE] = { 0 };
	DWORD dwNumberOfCharRead;
	DWORD dwError;

	_tprintf(_T("Enter a string: "));
	if (!ReadConsole(hConsoleIn, (LPVOID) lpBuffer, BUFFER_SIZE, &dwNumberOfCharRead, NULL))
	{
		_tprintf(_T("Failed to read input"));
		return -1;
	}
	else
	{
		__try
		{
			ValidateInputString(lpBuffer);
			_tprintf(_T("Your input: %s\n"), lpBuffer);
		}
		__except (ExceptionFilter(GetExceptionCode(), &dwError))
		{
			_tprintf(_T(" * Exception Raised: "));
			// Determine the error message
			switch (dwError)
			{
			case START_WITH_DIGIT:
				_tprintf(_T("Input string start with a digit. Error Code: %X\n"), START_WITH_DIGIT);
				break;
			default:
				_tprintf(_T("Unknown exception.\n"));
				break;
			}
		}
	}
	CloseHandle(hConsoleIn);
	_tprintf(_T("Done\n"));
	return 0;
}

VOID ValidateInputString(TCHAR *lpBuffer)
{
	if (_istdigit((INT)lpBuffer[0]) != 0)
		RaiseException(START_WITH_DIGIT, 0, 0, NULL); // Raise exception if the input string start with a digit. The exception code can be retrieved using GetExceptionCode() function.
}

// This function is a filter function that is used in the __except filter-expression
// to determine the error code and return the Windows exception value (EXCEPTION_EXECUTE_HANDLER)
DWORD ExceptionFilter(DWORD dwExceptionCode, LPDWORD lpError)
{
	if (dwExceptionCode == START_WITH_DIGIT)
	{
		*lpError = START_WITH_DIGIT;	// Assign error code to lpError which will be used in the __except block for determine error messages (switch-case)
		return EXCEPTION_EXECUTE_HANDLER;
	}
	
	return EXCEPTION_CONTINUE_SEARCH;
}