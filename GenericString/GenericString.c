// Tell the compiler to use Unicode functions and treat all
// defined string as Unicode
#define UNICODE
#define _UNICODE

#include <windows.h>
#include <tchar.h>		// For using standard C lirary in generic version

int _tmain()
{
	// Using generic string pointer
	LPTSTR str1 = _T("Hello World from LPTSTR");
	_tprintf(_T("%s\n"), str1);

	// Using char pointer
	TCHAR* str2 = _T("Another message using TCHAR");
	_ftprintf(stdout, _T("%s\n"), str2);

	// Print string constant using Unicode function
	LPCTSTR const_str = _T("This message is blocked from modifying");
	wprintf(L"%s\n", const_str);

	// Read/Write Console



	return 0;
}
