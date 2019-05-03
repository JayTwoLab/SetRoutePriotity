// SetRoutePriotityDlg.h : header file
//

#pragma once
#include "afxwin.h"



// CSetRoutePriotityDlg dialog
class CSetRoutePriotityDlg : public CDialog
{
// Construction
public:
	CSetRoutePriotityDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SETROUTEPRIOTITY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CListBox m_lbIP;

	afx_msg void OnBnClickedOk();

private:
	BOOL DeleteRoute(); 
	BOOL SetRoute(CString strIP); 

};
