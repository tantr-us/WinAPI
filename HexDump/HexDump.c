#include <windows.h>
#include <tchar.h>

void dumpBinary(LPCTSTR lpBinaryFile)
{
	
}

int _tmain(int argc, TCHAR *argv[])
{

	if (argc < 2)
	{
		_tprintf(_T("\n Usage: HexDump.exe [binary file]\n\n"));
	}
	else
	{
		LPCTSTR lpBinaryFile = argv[1];
		_tprintf(_T("\n Open binary file: %s\n\n"), lpBinaryFile);
	}

	return 0;
}