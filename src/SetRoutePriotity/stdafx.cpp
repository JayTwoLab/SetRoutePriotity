// stdafx.cpp : source file that includes just the standard includes
// SetRoutePriotity.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

//////////////////////////////////////////////////////////////////////

BOOL SetRoute(CString strIP)
{
	CString strCommand;
	strCommand.Format(
		_T("route.exe ADD 224.0.0.0 MASK 240.0.0.0 %s METRIC 1 -p"),
		strIP);

	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	// Start the child process. 
	if (!CreateProcess(
		NULL,   // module name (use command line). 
		strCommand.GetBuffer(strCommand.GetLength()), // Command line. 
		NULL,             // Process handle not inheritable. 
		NULL,             // Thread handle not inheritable. 
		FALSE,            // Set handle inheritance to FALSE. 
		0,                // No creation flags. 
		NULL,             // Use parent's environment block. 
		NULL,             // Use parent's starting directory. 
		&si,              // Pointer to STARTUPINFO structure.
		&pi)             // Pointer to PROCESS_INFORMATION structure.
		)
	{
		TRACE("CreateProcess failed (%d).\n", GetLastError());
		return FALSE;
	}

	// Wait until child process exits.
	WaitForSingleObject(pi.hProcess, INFINITE);

	// Close process and thread handles. 
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	return TRUE;
}

//////////////////////////////////////////////////////////////////////

BOOL DeleteRoute()
{
	CString strCommand;
	strCommand.Format(_T("route.exe delete 224.0.0.0"));

	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	// Start the child process. 
	if (!CreateProcess(
		NULL,   // module name (use command line). 
		strCommand.GetBuffer(strCommand.GetLength()), // Command line. 
		NULL,             // Process handle not inheritable. 
		NULL,             // Thread handle not inheritable. 
		FALSE,            // Set handle inheritance to FALSE. 
		0,                // No creation flags. 
		NULL,             // Use parent's environment block. 
		NULL,             // Use parent's starting directory. 
		&si,              // Pointer to STARTUPINFO structure.
		&pi)             // Pointer to PROCESS_INFORMATION structure.
		)
	{
		TRACE("CreateProcess failed (%d).\n", GetLastError());
		return FALSE;
	}

	// Wait until child process exits.
	WaitForSingleObject(pi.hProcess, INFINITE);

	// Close process and thread handles. 
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	return TRUE;
}
