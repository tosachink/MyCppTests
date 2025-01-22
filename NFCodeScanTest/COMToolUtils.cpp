#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <Windows.h>


typedef unsigned long uint32;

static bool tcharHexDigits(uint32& i, const int n, const TCHAR* s);
LPCTSTR GetRegKey(LPCTSTR key, LPCTSTR name = NULL, HKEY hKey = HKEY_CLASSES_ROOT);

void dprintf(char* format, ...)
{
	va_list args;
	char    buffer[2048 + 255];

	va_start(args, format);

	// using secure version to replace wvsprintf
	int bSize = vsprintf_s(buffer, sizeof(buffer), format, args);
	if (bSize > 0) {
		strcpy_s(buffer + bSize, sizeof(buffer) / sizeof(char) - bSize, "\r\n");
		printf("%s", buffer);
	}
}

#ifdef _DEBUG
#define DEBUGONLY(x) x
#else
#define DEBUGONLY(x)
#endif

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


LPCTSTR GetEXEPath() {
	static TCHAR exePath[_MAX_PATH + 2] = "";

	if (!exePath[0]) {

		::GetModuleFileName(0, exePath, sizeof(exePath) / sizeof(TCHAR));
		int i = 0;
		int pos = 0;
		while (exePath[i] != 0 && i <= _MAX_PATH + 1) {
			if (exePath[i] == _T('\\')) {
				pos = i;
			}
			i++;
		}
		exePath[pos] = 0;

	}

	return exePath;
}


//////////////////////////////////////////////////////////////////
// TCHAR

//#define space _T(' ')
//#define tab _T('\t')
//#define minus _T('-')
//#define plus _T('+')
#define nc _T('\0')
#define c0 _T('0')
#define c9 _T('9')
#define cA _T('A')
#define cF _T('F')
#define ca _T('a')
#define cf _T('f')
//#define slash _T('/')
#define dash _T('-')
#define cob _T('{')
#define ccb _T('}')

bool tcharHexDigits(uint32& i, const int n, const TCHAR* s)
{
	i = 0;
	for (int j = 0; j < n; j++, s++)
	{
		TCHAR c = *s;
		if ((c >= c0) && (c <= c9))
			i = (i << 4) + (c - c0);
		else if ((c >= ca) && (c <= cf))
			i = (i << 4) + (c - ca) + 10;
		else if ((c >= cA) && (c <= cF))
			i = (i << 4) + (c - cA) + 10;
		else
			return false;
	}
	return true;
}

bool tcharToGUID(GUID& g, const TCHAR* s)
{
	GUID gg;
	uint32 i;

	while ((*s != 0) && isspace(*s))
		s++;
	if (*s == nc)
		return false;
	if (*s == cob) {	// '{'
		s++;
	}

	if (!tcharHexDigits(*(uint32*)&gg.Data1, 8, s))
		return false;
	s += 8;
	if (*s != dash)	// '-'
		return false;
	s++;

	if (!tcharHexDigits(i, 4, s))
		return false;
	s += 4;
	gg.Data2 = (WORD)i;
	if (*s != dash)	// '-'
		return false;
	s++;

	if (!tcharHexDigits(i, 4, s))
		return false;
	s += 4;
	gg.Data3 = (WORD)i;
	if (*s != dash)	// '-'
		return false;
	s++;

	for (int j = 0; j < 8; j++) // bytes
	{
		if (*s == dash) s++;
		if (!tcharHexDigits(i, 2, s)) // two digits at a time
			return false;
		s += 2;
		gg.Data4[j] = (char)i;
	}

	g = gg;
	return true;
}

//////////////////////////////////////////////////////////////////
// WCHAR

#define wnc L'\0'
#define wc0 L'0'
#define wc9 L'9'
#define wcA L'A'
#define wcF L'F'
#define wca L'a'
#define wcf L'f'
#define wdash L'-'
#define wcob L'{'
#define wccb L'}'

bool wcharHexDigits(uint32& i, const int n, const wchar_t* s)
{
	i = 0;
	for (int j = 0; j < n; j++, s++)
	{
		wchar_t c = *s;
		if ((c >= wc0) && (c <= wc9))
			i = (i << 4) + (c - wc0);
		else if ((c >= wca) && (c <= wcf))
			i = (i << 4) + (c - wca) + 10;
		else if ((c >= wcA) && (c <= wcF))
			i = (i << 4) + (c - wcA) + 10;
		else
			return false;
	}
	return true;
}

bool wcharToGUID(GUID& g, const wchar_t* s)
{
	GUID gg;
	uint32 i;

	while ((*s != 0) && iswspace(*s))
		s++;
	if (*s == wnc)
		return false;
	if (*s == wcob) {	// '{'
		s++;
	}

	if (!wcharHexDigits(*(uint32*)&gg.Data1, 8, s))
		return false;
	s += 8;
	if (*s != wdash)	// '-'
		return false;
	s++;

	if (!wcharHexDigits(i, 4, s))
		return false;
	s += 4;
	gg.Data2 = (WORD)i;
	if (*s != wdash)	// '-'
		return false;
	s++;

	if (!wcharHexDigits(i, 4, s))
		return false;
	s += 4;
	gg.Data3 = (WORD)i;
	if (*s != wdash)	// '-'
		return false;
	s++;

	for (int j = 0; j < 8; j++) // bytes
	{
		if (*s == wdash) s++;
		if (!wcharHexDigits(i, 2, s)) // two digits at a time
			return false;
		s += 2;
		gg.Data4[j] = (char)i;
	}

	g = gg;
	return true;
}


bool SetRegKey(LPCTSTR key, LPCTSTR value, LPCTSTR name, HKEY rootKey) {

	HKEY hKey;
	LONG hr;

	hr = RegCreateKey(rootKey, key, &hKey);

	if (hr == ERROR_SUCCESS)
	{
		//hr = RegSetValue(hKey, name, REG_SZ, value, QBDTDataTypes::SizetToDWordConverter(_tcslen(value) * sizeof(TCHAR)));
		::RegCloseKey(hKey);
	}

	return hr == ERROR_SUCCESS;
}

/**
LONG RegQueryValueEx(
  HKEY hKey,            // handle to key
  LPCTSTR lpValueName,  // value name
  LPDWORD lpReserved,   // reserved
  LPDWORD lpType,       // type buffer
  LPBYTE lpData,        // data buffer
  LPDWORD lpcbData      // size of data buffer
);
**/

LPCTSTR GetRegKey(LPCTSTR key, LPCTSTR name, HKEY rootKey) {

	static TCHAR value[4 * 1024];

	HKEY hKey;
	LONG hr;

	value[0] = 0;
	unsigned long valSize = sizeof(value);

	hr = ::RegOpenKey(rootKey, key, &hKey);

	if (hr == ERROR_SUCCESS) {
		DWORD type;
		hr = ::RegQueryValueEx(hKey, name, NULL, &type, (unsigned char*)value, &valSize);
		::RegCloseKey(hKey);
	}

	return value;
}

// JZhu 2/08, added buf size for using secure CRT version.
void PathAdd(LPTSTR path, const size_t pathSize, LPCTSTR name) {

	if (!path) { // null path
		return;
	}

	size_t len = _tcslen(path);
	if (len >= pathSize) { // the len is already hits the limit
		return;
	}

	if (len && path[len - 1] != '\\' && path[len - 1] != '/' && path[len - 1] != ':') {
		path[len++] = '\\';
	}

	// using secure CRT version
	_tcscpy_s(&path[len], pathSize - len, name);

}

bool fileExists(LPCTSTR filePath) {
	DWORD attrib = GetFileAttributes(filePath);
	if (attrib == 0xffffffff || attrib == FILE_ATTRIBUTE_DIRECTORY) {
		return false;
	}
	else {
		return true;
	}
}


LPCTSTR GetCommonPath() {

	static TCHAR comPath[_MAX_PATH];

	LPCTSTR pCommon = GetRegKey(_T("Applications"), _T("Path"));
	if (pCommon && pCommon[0]) {
		_tfullpath(comPath, pCommon, sizeof(comPath) / sizeof(TCHAR));
	}
	else {

		// setup the path to the common folder (where colocator is)
		LPCTSTR pStr = GetRegKey(_T("CLSID\\{E53C7263-F6D9-8492-A623-AAAAAAAAAAAA}\\InprocServer32"));

		// find the last back slash in the colocator path.
		if (pStr) {
			_tcscpy(comPath, pStr);
			int i = 0;
			int pos = 0;
			while (comPath[i] != 0 && i < _MAX_PATH) {
				if (comPath[i] == _T('\\')) { // avoid buffer overrun
					pos = i;
				}
				i++;
			}
			// no slashes
			if (!pos) {
				pStr = 0;
			}
			else {
				// truncate filename part
				comPath[pos] = 0;
			}
		}
	}

	return comPath;
}
