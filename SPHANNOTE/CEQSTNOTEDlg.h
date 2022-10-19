#pragma once
#include "afxdialogex.h"


// CEQSTNOTEDlg 대화 상자
class CEQSTNOTEDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEQSTNOTEDlg)

public:
	CEQSTNOTEDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CEQSTNOTEDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ENROLL_LICENSE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	// LICENSE 코드
	CEdit LicenseData;
	afx_msg void OnClickedEnrollButton();
};
