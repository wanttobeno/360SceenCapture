// Loader360SceenCapture.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <stdio.h>
#include <time.h>
#include <shlwapi.h>
#include <shlobj.h>
#include "ResHelper.h"
#include "resource.h"
#pragma comment(lib,"shlwapi.lib")


wchar_t g_path[MAX_PATH*2] = L"C:\\Program Files (x86)\\360\\360safe\\Utils\\360ScreenCapture.exe";

BOOL Is360ScreenCaptureExist()
{
	wchar_t szDisk[] = L"CDEFGH";
	
	BOOL bFileExist = false;
	// 
	for (int i=0;i< sizeof(szDisk) /sizeof(szDisk[0]);i++)
	{
		g_path[0] = szDisk[i];
		bFileExist = PathFileExists(g_path);
		if (bFileExist)
		{
			break;
		}
	}
	return bFileExist;
}



int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.

    BOOL bFileExist = FALSE;// Is360ScreenCaptureExist();
	if (!bFileExist)
	{
		std::wstring dir = MakePathFromAppDataW(L"\\SceenCapture\\");
		CreateDirectory(dir.c_str(), NULL);
		std::wstring fulPath = dir;
		fulPath.append(L"360ScreenCapture.exe");
		if (!PathFileExists(fulPath.c_str()))
		{
			bFileExist = LoadSourceToDir(IDR_BIN1,dir.c_str(),L"360ScreenCapture.exe",L"bin");
		}
		else
		{
			bFileExist = TRUE;
		}
		if (bFileExist)
		{
			wcscpy(g_path,fulPath.c_str());
		}
	}

	if (!bFileExist)
	{
			MessageBox(NULL,L"360ScreenCapture.exe 文件不存在",L"提示",MB_OK|MB_ICONERROR);
			return -1;
	}

	STARTUPINFO  startInfo;
	PROCESS_INFORMATION stProcessInfo;
	::memset(&startInfo,0,sizeof(STARTUPINFO));
	::memset(&stProcessInfo,0,sizeof(stProcessInfo));
	startInfo.cb = sizeof(STARTUPINFO);
	

	TCHAR szPath[MAX_PATH] ={0};
	::SHGetSpecialFolderPath(NULL, szPath, 0, FALSE);


	SYSTEMTIME sysnow;
    GetSystemTime(&sysnow);

	wchar_t szTime[24] = {0};
	swprintf(szTime,L"%4d%02d%02d%02d%02d%02d",sysnow.wYear,sysnow.wMonth,sysnow.wDay,sysnow.wHour,sysnow.wMinute,sysnow.wSecond);

	wchar_t szParam[MAX_PATH*2] = {0};
	swprintf(szParam,L" \"-file\" \"%s\\%s.jpg\" \"-format\" \"jpg\"",szPath,szTime);


	BOOL bRet = CreateProcess(g_path,
		szParam,
		//L" \"-file\" \"C:\\Users\\myPc\\AppData\\Roaming\\360safe\\360Feedback\\Snap_7913921.jpg\" \"-format\" \"jpg\"",
		//L" -file C:\\Users\\myPc\\AppData\\Roaming\\360safe\\360Feedback\\Snap_7913921.jpg -format jpg",
		NULL,NULL,FALSE,0,NULL,NULL,&startInfo,&stProcessInfo);

	if (bRet)
	{
		WaitForSingleObject(stProcessInfo.hProcess,INFINITE);
		::CloseHandle(stProcessInfo.hProcess);
		::CloseHandle(stProcessInfo.hThread);
		stProcessInfo.hProcess = NULL;
		stProcessInfo.hThread = NULL;
		stProcessInfo.dwProcessId = 0;
		stProcessInfo.dwThreadId = 0;
	}
	else
	{
		wchar_t buf[128] = {0};
		DWORD dwErrCode = GetLastError();
		swprintf(buf,L"ErrCode : %d\n",dwErrCode);
		MessageBox(NULL,buf,L"错误提示",MB_OK|MB_ICONERROR);
	}
	return 0;
}



