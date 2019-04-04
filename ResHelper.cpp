// ResHelper.cpp: implementation of the CResHelper class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ResHelper.h"
#include <shlobj.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CResHelper::CResHelper(void)
{
}

CResHelper::~CResHelper(void)
{
}

std::wstring MakePathFromAppDataW(const wchar_t * szSub)
{
	wchar_t buf[MAX_PATH] = {0};
	SHGetSpecialFolderPathW(NULL, buf, CSIDL_APPDATA, 0);
	std::wstring strResult = buf;
	strResult += szSub;
	return strResult;
}

BOOL LoadSourceToDir(int nSourceId, std::wstring wstrDir, std::wstring wstrFileName, LPCWSTR strType)
{
	FILE* hPubKeyFile = NULL;
	std::string strDir = "";
	HRSRC hrc = NULL; 
	DWORD dwSize = 0; 
	HGLOBAL hGlobal = NULL; 
	
	hrc = FindResource(NULL, MAKEINTRESOURCE(nSourceId), strType);
	dwSize = SizeofResource(NULL, hrc);
	hGlobal = LoadResource(NULL, hrc);
	if (hGlobal && dwSize)
	{
		LPVOID pBuffer = LockResource(hGlobal);
		_wmkdir(wstrDir.c_str());
		wstrDir += wstrFileName;
		//strDir = WideByte2Acsi(wstrDir);
		if (pBuffer)
		{
			hPubKeyFile = _wfopen(wstrDir.c_str(),L"wb");
			//fopen_s(&hPubKeyFile, strDir.c_str(), "w+");
			fwrite(pBuffer, dwSize, sizeof(char), hPubKeyFile);
			fclose(hPubKeyFile);
		}
		FreeResource(hGlobal);
		return TRUE;
	}
	else
	{
		FreeResource(hGlobal);
		return FALSE;
	}
}