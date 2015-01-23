#pragma once


// ShareMemDlg dialog

class ShareMemDlg : public CDialog
{
	DECLARE_DYNAMIC(ShareMemDlg)

public:
	ShareMemDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~ShareMemDlg();

// Dialog Data
	enum { IDD = IDD_SHAREMEM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
