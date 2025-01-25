#include <windows.h>
#include <tchar.h>

#define EXECUTE_FAILED -1
#define EXECUTE_SUCCESSED 0
#define BUFFER_SIZE 4096 // 4 kb

// Prototype
VOID printErrorMessage(DWORD dwErrorCode);
DWORD dumpBinary(LPCTSTR lpBinaryFilePath);
VOID printBinaryInHex(BYTE *lpBuffer);

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
		dumpBinary(lpBinaryFilePath);
	}

	return 0;
}

VOID printErrorMessage(DWORD dwErrorCode)
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

DWORD dumpBinary(LPCTSTR lpBinaryFilePath)
{
	// Open the binary file from the file path
	HANDLE hFile = CreateFile(
		lpBinaryFilePath,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		printErrorMessage(GetLastError());
		return EXECUTE_FAILED;
	}

	BYTE lpBuffer[BUFFER_SIZE];
	DWORD dwNumOfBytesRead = -1;
	// do
		// Read N byte from the file
		// Print byte in hex
		// Print byte in ASCII
	// while (lpNumberOfBytesRead != 0);
	do
	{
		if (ReadFile(
			hFile,
			(LPVOID)lpBuffer,
			BUFFER_SIZE,
			&dwNumOfBytesRead,
			NULL))
		{
			printBinaryInHex(lpBuffer);
		}
	} while (dwNumOfBytesRead != 0);

	CloseHandle(hFile);
	return EXECUTE_SUCCESSED;
}

VOID printBinaryInHex(BYTE *lpBuffer)
{
	INT iColumn = 0;
	const INT iMaxColumn = 10;
	for (INT i = 0; i < BUFFER_SIZE; i++)
	{
		if (iColumn < iMaxColumn)
		{
			_tprintf(_T("%02X "), (BYTE)lpBuffer[i]);
			iColumn++;
		}
		else
		{
			_tprintf(_T("%02X\n"), (BYTE)lpBuffer[i]);
			iColumn = 0;
		}
	}
}