// ResHelper.h: interface for the CResHelper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RESHELPER_H__CEAF81B2_8D3A_4F96_8C7F_4674528C5781__INCLUDED_)
#define AFX_RESHELPER_H__CEAF81B2_8D3A_4F96_8C7F_4674528C5781__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>

class CResHelper
{
public:
	CResHelper(void);
	~CResHelper(void);
};

std::wstring MakePathFromAppDataW(const wchar_t * szSub);

BOOL LoadSourceToDir(int nSourceId, std::wstring wstrDir, std::wstring wstrFileName, LPCWSTR strType);

#endif // !defined(AFX_RESHELPER_H__CEAF81B2_8D3A_4F96_8C7F_4674528C5781__INCLUDED_)
