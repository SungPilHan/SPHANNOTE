#pragma once
#include "afxdialogex.h"

struct memory {
	char* response;
	size_t size;
};
static struct memory chunk = { 0 };
static size_t write_buffer_callback(char* contents, size_t size, size_t nmemb, std::string* response);

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
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()
public:
	// LICENSE 코드
	CEdit LicenseData;
	afx_msg void OnClickedEnrollButton();
	BOOL DoEnroll();
	CEdit LicenseStatus;
	afx_msg void OnBnClickedCancel();
};
