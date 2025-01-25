#include <windows.h>
#include <tchar.h>

#define EXECUTE_FAILED -1

void printErrorMessage(DWORD dwErrorCode)
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

int _tmain(int argc, TCHAR *argv[])
{

	if (argc < 2)
	{
		_tprintf(_T("\n Usage: HexDump.exe [binary file]\n\n"));
	}
	else
	{
		LPCTSTR lpBinaryFilePath = argv[1];
		_tprintf(_T("\n Open binary file: %s\n\n"), lpBinaryFilePath);
	}

	return 0;
}