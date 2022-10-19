// CEQSTNOTEDlg.cpp: 구현 파일
//

#include "pch.h"
#include "SPHANNOTE.h"
#include "afxdialogex.h"
#include "CEQSTNOTEDlg.h"


// CEQSTNOTEDlg 대화 상자

IMPLEMENT_DYNAMIC(CEQSTNOTEDlg, CDialogEx)

CEQSTNOTEDlg::CEQSTNOTEDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ENROLL_LICENSE, pParent)
{

}

CEQSTNOTEDlg::~CEQSTNOTEDlg()
{
}

void CEQSTNOTEDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_LICENSE, LicenseData);
}


BEGIN_MESSAGE_MAP(CEQSTNOTEDlg, CDialogEx)
	ON_BN_CLICKED(IDC_ENROLL_BUTTON, &CEQSTNOTEDlg::OnClickedEnrollButton)
END_MESSAGE_MAP()


// CEQSTNOTEDlg 메시지 처리기



void CEQSTNOTEDlg::OnClickedEnrollButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	LicenseData.SetWindowTextW(L"test");
}