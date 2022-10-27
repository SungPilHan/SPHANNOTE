
// SPHANNOTEDlg.h: 헤더 파일
//

#pragma once


// CSPHANNOTEDlg 대화 상자
class CSPHANNOTEDlg : public CDialogEx
{
// 생성입니다.
public:
	CSPHANNOTEDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SPHANNOTE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnHelpInfo();
	afx_msg void OnEditUndo();
	afx_msg void OnEditCut();
	afx_msg void OnEditCopy();
	afx_msg void OnEditPaste();
	afx_msg void OnEditSelectAll();
	afx_msg void OnEditClear();
	afx_msg void OnFileNew();
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveAs();
	afx_msg void OnFileClose();
	afx_msg void OnAcceleratorSave();

	CString strPath = NULL;
	BOOL mod = FALSE;
	void OpenFile();
	void SaveFile(BOOL* mod);

	// 메모장 Edit Control
	CEdit Edit_main;

	//단추키
	HACCEL hAccel = NULL;
	BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnEnrollLicense();
	afx_msg void OnAntidebugOne();
	afx_msg void OnAntidebugTwo();
	afx_msg void OnAntidebugThree();
	afx_msg void OnAntidebugFour();
	afx_msg void OnAntidebugFive();
	afx_msg void OnAntidebugSix();
};
