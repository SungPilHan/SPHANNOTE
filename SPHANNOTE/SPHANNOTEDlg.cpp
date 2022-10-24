
// SPHANNOTEDlg.cpp: 구현 파일
//
#include "pch.h"
#include "framework.h"
#include "SPHANNOTE.h"
#include "SPHANNOTEDlg.h"
#include "afxdialogex.h"
#include "CEQSTNOTEDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

typedef int(*DLLFUNC43)(int, int);
typedef std::string(*AESENC)(std::string, std::string);
typedef std::string(*AESSTR)(std::string);

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:	
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};
CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

BOOL CAboutDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();
	MoveWindow(0, 0, 400, 240);
	return TRUE;
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}
BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CSPHANNOTEDlg 대화 상자
CSPHANNOTEDlg::CSPHANNOTEDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SPHANNOTE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
void CSPHANNOTEDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_MAIN, Edit_main);
}
BEGIN_MESSAGE_MAP(CSPHANNOTEDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_GETMINMAXINFO()
	ON_COMMAND(ID_HELP_INFO, &CSPHANNOTEDlg::OnHelpInfo)
	ON_COMMAND(ID_EDIT_UNDO, &CSPHANNOTEDlg::OnEditUndo)
	ON_COMMAND(ID_EDIT_CUT, &CSPHANNOTEDlg::OnEditCut)
	ON_COMMAND(ID_EDIT_COPY, &CSPHANNOTEDlg::OnEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, &CSPHANNOTEDlg::OnEditPaste)
	ON_COMMAND(ID_EDIT_SELECT_ALL, &CSPHANNOTEDlg::OnEditSelectAll)
	ON_COMMAND(ID_EDIT_CLEAR, &CSPHANNOTEDlg::OnEditClear)
	ON_COMMAND(ID_FILE_NEW, &CSPHANNOTEDlg::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CSPHANNOTEDlg::OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, &CSPHANNOTEDlg::OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, &CSPHANNOTEDlg::OnFileSaveAs)
	ON_COMMAND(ID_FILE_CLOSE, &CSPHANNOTEDlg::OnFileClose)
	ON_COMMAND(ID_ACCELERATOR_SAVE, &CSPHANNOTEDlg::OnAcceleratorSave)
	ON_WM_SIZE()
	ON_COMMAND(ID_ENROLL_LICENSE, &CSPHANNOTEDlg::OnEnrollLicense)
	ON_COMMAND(ID_HOOKING_ONE, &CSPHANNOTEDlg::OnHookingOne)
	ON_COMMAND(ID_HOOKING_TWO, &CSPHANNOTEDlg::OnHookingTwo)
	ON_COMMAND(ID_HOOKING_THREE, &CSPHANNOTEDlg::OnHookingThree)
	ON_COMMAND(ID_HOOKING_FOUR, &CSPHANNOTEDlg::OnHookingFour)
	ON_COMMAND(ID_HOOKING_FIVE, &CSPHANNOTEDlg::OnHookingFive)
END_MESSAGE_MAP()

// CSPHANNOTEDlg 메시지 처리기
BOOL CSPHANNOTEDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//라이선스 검증
	CEQSTNOTEDlg eqstNote;
	if (eqstNote.DoModal() != IDOK) {
		AfxGetMainWnd()->PostMessageW(WM_CLOSE);
	}

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	hAccel = ::LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_ACCELERATOR1));

	MoveWindow(0, 0, 960, 680);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}
void CSPHANNOTEDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	//X버튼(창닫기) 눌렀을 때 처리
	else if (nID == SC_CLOSE) {
		CSPHANNOTEDlg::OnFileClose();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.
void CSPHANNOTEDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
		
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CSPHANNOTEDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//창 최소 크기 설정
void CSPHANNOTEDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	lpMMI->ptMinTrackSize.x = 480;
	lpMMI->ptMinTrackSize.y = 320;
	CDialogEx::OnGetMinMaxInfo(lpMMI);
}

//도움말 메뉴
void CSPHANNOTEDlg::OnHelpInfo()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CDialog aboutDlg(IDD_ABOUTBOX);
	INT_PTR nRet = -1;

	nRet = aboutDlg.DoModal();
}
void CSPHANNOTEDlg::OnEnrollLicense()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CEQSTNOTEDlg enrollDlg;
	INT_PTR nRet = -1;

	nRet = enrollDlg.DoModal();

	if (nRet == IDOK) {
		::MessageBox(NULL, L"인증되었습니다.", L"License Checked", MB_OK);
	}
}

//편집 메뉴
void CSPHANNOTEDlg::OnEditUndo()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	::SendMessage(Edit_main.m_hWnd, WM_UNDO, 0, 0);
}
void CSPHANNOTEDlg::OnEditCut()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	::SendMessage(Edit_main.m_hWnd, WM_CUT, 0, 0);
}
void CSPHANNOTEDlg::OnEditCopy()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	::SendMessage(Edit_main.m_hWnd, WM_COPY, 0, 0);
}
void CSPHANNOTEDlg::OnEditPaste()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	::SendMessage(Edit_main.m_hWnd, WM_PASTE, 0, 0);
}
void CSPHANNOTEDlg::OnEditClear()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	::SendMessage(Edit_main.m_hWnd, WM_CLEAR, 0, 0);
}
void CSPHANNOTEDlg::OnEditSelectAll()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	::SendMessage(Edit_main.m_hWnd, EM_SETSEL, 0, -1);
}
//파일 메뉴
void CSPHANNOTEDlg::OnFileNew()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (::SendMessage(Edit_main.m_hWnd, EM_GETMODIFY, 0, 0)) {
		if (::MessageBox(NULL, L"변경 내용을 저장하시겠습니까? ", L"Save File", MB_YESNO) == 6) {
			CSPHANNOTEDlg::SaveFile(&mod);
			::SendMessage(Edit_main.m_hWnd, WM_SETTEXT, 0, 0);
		}
		else {
			::SendMessage(Edit_main.m_hWnd, WM_SETTEXT, 0, 0);
		}
	}
	else {
		::SendMessage(Edit_main.m_hWnd, WM_SETTEXT, 0, 0);
	}
}
void CSPHANNOTEDlg::OnFileOpen()
{
	
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (::SendMessage(Edit_main.m_hWnd, EM_GETMODIFY, 0, 0)) {
		if (::MessageBox(NULL, L"변경 내용을 저장하시겠습니까? ", L"Save File", MB_YESNO) == 6) {
			CSPHANNOTEDlg::SaveFile(&mod);
			::SendMessage(Edit_main.m_hWnd, WM_SETTEXT, 0, 0);
			CSPHANNOTEDlg::OpenFile();
		}
		else {
			CSPHANNOTEDlg::OpenFile();
		}
	}
	else {
		CSPHANNOTEDlg::OpenFile();
	}
}
void CSPHANNOTEDlg::OnFileSave()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CSPHANNOTEDlg::SaveFile(&mod);
}
void CSPHANNOTEDlg::OnFileSaveAs()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	BOOL FALSE_DATA = FALSE;
	CSPHANNOTEDlg::SaveFile(&FALSE_DATA);
}
void CSPHANNOTEDlg::OnFileClose()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (::SendMessage(Edit_main.m_hWnd, EM_GETMODIFY, 0, 0)) {
		if (::MessageBox(NULL, L"변경 내용을 저장하시겠습니까? ", L"Save File", MB_YESNO) == 6) {
			CSPHANNOTEDlg::SaveFile(&mod);
			::SendMessage(Edit_main.m_hWnd, WM_SETTEXT, 0, 0);
			AfxGetMainWnd()->PostMessageW(WM_CLOSE);
		}
		else {
			AfxGetMainWnd()->PostMessageW(WM_CLOSE);
		}
	}
	else {
		AfxGetMainWnd()->PostMessageW(WM_CLOSE);
	}
}

//메뉴에 사용될 파일 열기 및 저장 함수
void CSPHANNOTEDlg::OpenFile() {
	CString str, getFileString = NULL;
	CStdioFile rFile;
	CFileException ex;
	CFileDialog dlg(TRUE, _T("*.txt"), NULL, OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT
		, _T("TXT Files(*.txt) |*.txt| ALL Files(*.*) |*.*|"), NULL);
	if (dlg.DoModal() == IDOK) {
		strPath = dlg.GetPathName();
		rFile.Open(strPath, CFile::modeRead | CFile::typeText, &ex);
		while (rFile.ReadString(str)) {
			getFileString += (str + _T("\r\n"));
		}
		rFile.Close();
		mod = TRUE;
		Edit_main.SetWindowTextW(getFileString);
	}
}
void CSPHANNOTEDlg::SaveFile(BOOL* mod) {
	CString str = NULL;
	CStdioFile wFile;
	CFileException ex;
	CFileDialog dlg(FALSE, _T("*.txt"), NULL, OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT
		, _T("TXT Files(*.txt) |*.txt| ALL Files(*.*) |*.*|"), NULL);
	if (*mod) {
		wFile.Open(strPath, CFile::modeCreate | CFile::modeWrite, &ex);
		Edit_main.GetWindowTextW(str);
		str.Replace(_T("\r\n"), _T("\n"));
		wFile.WriteString(str);
		wFile.Close();
	}
	else {
		if (dlg.DoModal() == IDOK) {
			strPath = dlg.GetPathName();
			if (strPath.Right(4) != ".txt") {
				strPath += ".txt";
			}
			wFile.Open(strPath, CFile::modeCreate | CFile::modeWrite, &ex);
			Edit_main.GetWindowTextW(str);
			str.Replace(_T("\r\n"), _T("\n"));
			wFile.WriteString(str);
			wFile.Close();
			*mod = TRUE;
		}
	}
	::SendMessage(Edit_main.m_hWnd, EM_SETMODIFY, 0, 0);
}

//단축키
void CSPHANNOTEDlg::OnAcceleratorSave()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CSPHANNOTEDlg::SaveFile(&mod);
}
BOOL CSPHANNOTEDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 구현 코드 추가.
	if (::TranslateAccelerator(this->m_hWnd, hAccel, pMsg)) {
		return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CSPHANNOTEDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CRect rect(0, 0, cx, cy);
	if (Edit_main.GetSafeHwnd()) {
		Edit_main.MoveWindow(rect);
	}
}

// Hooking 문제 메뉴
void CSPHANNOTEDlg::OnHookingOne()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	::MessageBox(NULL, L"함께 첨부된 HookingQuestion.dll 파일을 EQSTNOTE.exe에 Injection하고\
 메뉴 > Hooking > 문제 1번을 클릭해 FLAG를 획득하세요.\n\
(실행파일과 같은 경로에서 DLL파일을 Injection하지 마세요.)", L"Hooking", MB_OK);
	
	std::ifstream fin;
	fin.open("HookingQuestion.dll");
	if (fin.is_open()) {
		fin.close();
		::MessageBox(NULL, L"실행파일과 같은 경로에서 DLL파일을 Injection하지 마세요.", L"DLL TEST", MB_OK);
		return;
	}

	DLLFUNC43 Question = (DLLFUNC43)GetProcAddress(GetModuleHandle(L"HookingQuestion.dll"), "Question");
	if (Question == NULL) {
		::MessageBox(NULL, L"함수 로드 실패", L"DLL TEST", MB_OK);
		return;
	}

	HINSTANCE hInst = LoadLibrary(L"EssentialNote.dll");
	if (hInst == NULL) {
		::MessageBox(NULL, L"DLL 로드 실패", L"DLL TEST", MB_OK);
		return;
	}

	AESENC DecFunc = (AESENC)GetProcAddress(hInst, "AESDecryptWithKey");
	AESENC EncFunc = (AESENC)GetProcAddress(hInst, "AESEncryptWithKey");

	if (DecFunc == NULL || EncFunc == NULL) {
		::MessageBox(NULL, L"함수 로드 실패", L"DLL TEST", MB_OK);
		FreeLibrary(hInst);
		return;
	}

	
	std::string data = "8046EF1C8D6FAC08EE8395A8DF60C6F03ED15DEBDFBF669BD9473F737BCDC09E6074812690C044AA632B16C82A9CF24D";
	data = DecFunc(data, "E19E3A81862BAD7910CB6B2083E22812610D8066AB0CDCE876BC0C0CB85947B3D1C51CECEBDD75945119FC96C1CE57ED");

	FreeLibrary(hInst);

	CString cstr(data.c_str());
	::MessageBox(NULL, cstr, L"DLL TEST", MB_OK);
}


void CSPHANNOTEDlg::OnHookingTwo()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	::MessageBox(NULL, L"암호화 API를 호출하여 데이터를 암호화하고 메시지 박스에 보여주고 있습니다.\
해당 API를 후킹하여 평문 데이터를 탈취하고 FLAG를 획득하세요.", L"Hooking", MB_OK);

	HINSTANCE hInst = LoadLibrary(L"EssentialNote.dll");
	if (hInst == NULL) {
		::MessageBox(NULL, L"DLL 로드 실패", L"DLL TEST", MB_OK);
		return;
	}

	AESENC DecFunc = (AESENC)GetProcAddress(hInst, "AESDecryptWithKey");
	AESENC EncFunc = (AESENC)GetProcAddress(hInst, "AESEncryptWithKey");

	if (DecFunc == NULL || EncFunc == NULL) {
		::MessageBox(NULL, L"함수 로드 실패", L"DLL TEST", MB_OK);
		FreeLibrary(hInst);
		return;
	}

	std::string data = "F302F834FC189C69643FD90C567E42D61F5955034454591C30FB08C70A08FA4E067D23F36962AC4B496AA242C5B2863B";
	data = DecFunc(data, "E19E3A81862BAD7910CB6B2083E22812610D8066AB0CDCE876BC0C0CB85947B3D1C51CECEBDD75945119FC96C1CE57ED");
	data = EncFunc(data, "E19E3A81862BAD7910CB6B2083E22812610D8066AB0CDCE876BC0C0CB85947B3D1C51CECEBDD75945119FC96C1CE57ED");
	CString cstr(data.c_str());
	::MessageBox(NULL, cstr, L"Hooking", MB_OK);
}


void CSPHANNOTEDlg::OnHookingThree()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	::MessageBox(NULL, L"암호화 API에서 Export 된 복호화 함수를 후킹하고 다음의 암호문을 복호화하세요.\n\
(복호화할 데이터 = \
\"2BF5A9AC8191BC6F73565046074A1F029E6B22DA0E2B5C1F3B21FB81E2130DDEDCDBCE6BE7F752E20092C5278C6FFE4B\"\
)", L"Hooking", MB_OK);
}


void CSPHANNOTEDlg::OnHookingFour()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	::MessageBox(NULL, L"암호화 API 내부에서 사용되는 함수 중 전달 받은 Key Seed를 복호화하는 복호화 함수를 찾아 \
Key Seed의 평문값을 탈취하세요.\n\
(데이터 암복호화시에 전달되는 Key Seed 값 = \
\"E19E3A81862BAD7910CB6B2083E22812610D8066AB0CDCE876BC0C0CB85947B3D1C51CECEBDD75945119FC96C1CE57ED\")", L"Hooking", MB_OK);
}


void CSPHANNOTEDlg::OnHookingFive()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	::MessageBox(NULL, L"암호화 API 내부에서 사용되는 함수 중 Key Seed를 복호화하는 함수를 찾아 다음 값을 복호화하세요.\n\
(복호화할 데이터 = \
\"1C31EF44A5981264BD8D5FD615D60091941FA9D2BCBD0B154034EB8F2E7F7487F1C0C61361DC566DDD0B9F5217296C92\")", L"Hooking", MB_OK);

}
