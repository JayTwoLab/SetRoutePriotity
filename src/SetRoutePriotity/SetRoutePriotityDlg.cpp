// SetRoutePriotityDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SetRoutePriotity.h"
#include "SetRoutePriotityDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSetRoutePriotityDlg dialog




CSetRoutePriotityDlg::CSetRoutePriotityDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetRoutePriotityDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSetRoutePriotityDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IP_LIST, m_lbIP);
}

BEGIN_MESSAGE_MAP(CSetRoutePriotityDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CSetRoutePriotityDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSetRoutePriotityDlg message handlers

BOOL CSetRoutePriotityDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	//////////////////////////////////////////////////////////////////////////

	try
	{
		CRouteIPEnum ipEnum; 
		ipEnum.m_pSetRoutePriotityDlg = this; 
		ipEnum.Enumerate();
	}
	catch(CNotSupportedException*)
	{
		OutputDebugString(_T("An error occurred while trying to detect the IP address\n"));
		OutputDebugString(_T("You should check to see to make sure TCPIP is installed correctly\n"));
	}

	//////////////////////////////////////////////////////////////////////////

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSetRoutePriotityDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSetRoutePriotityDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//---------------------------------------------------------------------------

void CSetRoutePriotityDlg::OnBnClickedOk()
{

	int nSel = m_lbIP.GetCurSel();
	if ( LB_ERR != nSel )
	{
		CString strIP;
		int n = m_lbIP.GetTextLen( nSel ); 
		m_lbIP.GetText( nSel, strIP.GetBuffer(n) );  

		BOOL bR1 = FALSE;
		BOOL bR2 = FALSE;
		bR1 = DeleteRoute();
		bR2 = SetRoute( strIP ); 
	
		strIP.ReleaseBuffer();

		if ( TRUE == bR1 &&
			 TRUE == bR2 )
		{
			AfxMessageBox( _T("Success to setting network priority") ); 
		}
	}
	
	OnOK();
}

//---------------------------------------------------------------------------

BOOL CSetRoutePriotityDlg::DeleteRoute()
{
	CString strCommand;
	strCommand.Format( _T("route.exe delete 224.0.0.0") ); 

	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory( &si, sizeof(si) );
	si.cb = sizeof(si);
	ZeroMemory( &pi, sizeof(pi) );

	// Start the child process. 
	if( !CreateProcess( 
		NULL,   // module name (use command line). 
		strCommand.GetBuffer(strCommand.GetLength()), // Command line. 
		NULL,             // Process handle not inheritable. 
		NULL,             // Thread handle not inheritable. 
		FALSE,            // Set handle inheritance to FALSE. 
		0,                // No creation flags. 
		NULL,             // Use parent's environment block. 
		NULL,             // Use parent's starting directory. 
		&si,              // Pointer to STARTUPINFO structure.
		&pi )             // Pointer to PROCESS_INFORMATION structure.
		) 
	{
		TRACE( "CreateProcess failed (%d).\n", GetLastError() );
		return FALSE;
	}

	// Wait until child process exits.
	WaitForSingleObject( pi.hProcess, INFINITE );

	// Close process and thread handles. 
	CloseHandle( pi.hProcess );
	CloseHandle( pi.hThread );

	return TRUE; 
}

//---------------------------------------------------------------------------

BOOL CSetRoutePriotityDlg::SetRoute(CString strIP)
{
	CString strCommand;
	strCommand.Format( 
		_T("route.exe ADD 224.0.0.0 MASK 240.0.0.0 %s METRIC 1 -p"), 
		strIP ); 

	STARTUPINFO si; 
	PROCESS_INFORMATION pi;

	ZeroMemory( &si, sizeof(si) );
	si.cb = sizeof(si);
	ZeroMemory( &pi, sizeof(pi) );

	// Start the child process. 
	if( !CreateProcess( 
		NULL,   // module name (use command line). 
		strCommand.GetBuffer(strCommand.GetLength()), // Command line. 
		NULL,             // Process handle not inheritable. 
		NULL,             // Thread handle not inheritable. 
		FALSE,            // Set handle inheritance to FALSE. 
		0,                // No creation flags. 
		NULL,             // Use parent's environment block. 
		NULL,             // Use parent's starting directory. 
		&si,              // Pointer to STARTUPINFO structure.
		&pi )             // Pointer to PROCESS_INFORMATION structure.
		) 
	{
		TRACE( "CreateProcess failed (%d).\n", GetLastError() ); 
		return FALSE;
	}

	// Wait until child process exits.
	WaitForSingleObject( pi.hProcess, INFINITE );

	// Close process and thread handles. 
	CloseHandle( pi.hProcess );
	CloseHandle( pi.hThread );
		
	return TRUE; 
}

//---------------------------------------------------------------------------


