#include <windows.h>
#include <tchar.h>

#define EXECUTE_FAILED -1
#define EXECUTE_SUCCESSED 0
#define BUFFER_SIZE 4096 // 4 kb
#define ASCII_ARR_SIZE 16

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

/**
 *  @brief      Retrieve the system error message for the last-error code
 *
 *  @param      dwErrorCode    Error code returned from GetLastError().
 */
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

/**
 *  @brief      Dump binary from a provided file.
 *
 *  @param      lpBinaryFilePath    path to the binary file.
 */
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

/**
 *  @brief      Print the binary in hexadecimal and ASCII.
 *
 *  @param      lpBuffer    A byte array.
 */
VOID printBinaryInHex(BYTE* lpBuffer)
{
	INT iByteIndex = 1, iAsciiIndex = 0;
	const INT iBytePerRow = 16;
	BYTE asciiArray[ASCII_ARR_SIZE];

	for (INT i = 0; i < BUFFER_SIZE; i++)
	{
		if (iByteIndex < iBytePerRow)
		{
			_tprintf(_T("%02X "), (BYTE)lpBuffer[i]);
			asciiArray[iAsciiIndex] = (BYTE)lpBuffer[i];
			iByteIndex++;
			iAsciiIndex++;
		}
		else
		{
			_tprintf(_T("%02X\t\t | \t"), (BYTE)lpBuffer[i]);
			asciiArray[iAsciiIndex] = (BYTE)lpBuffer[i];

			for (INT j = 0; j < ASCII_ARR_SIZE; j++)
			{
				CHAR c = asciiArray[j];
				if (0 <= (INT)c && (INT)c <= 32)
				{
					_tprintf(_T("."));
				}
				else
				{
					_tprintf(_T("%c"), asciiArray[j]);
				}
			}
			_tprintf(_T("\n"));

			iByteIndex = 1;
			iAsciiIndex = 0;
		}
	}
}
