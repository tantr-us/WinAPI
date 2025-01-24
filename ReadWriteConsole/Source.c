#ifdef UNICODE
#define _UNICODE
#endif
#include <windows.h>
#include <tchar.h>

int _tmain()
{
	HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	LPCTSTR lpBuffer = _T("Hello World");
	DWORD lpCharWritten;

	if (!WriteConsole(hConsoleOut, lpBuffer, _tcslen(lpBuffer), &lpCharWritten, NULL))
	{
		_tprintf(_T("Failed to write to console\n"));
	}

	return 0;
}