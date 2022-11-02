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

BOOL CEQSTNOTEDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	MoveWindow(0, 0, 640, 400);

	//사전에 저장된 라이센스 파일이 있으면 추가
	std::string data;
	CString license;
	std::ifstream fin("EQSTNOTE.INI");
	if (fin.is_open()) {
		while (getline(fin, data)) {
			std::size_t pos = data.find_first_of('=');
			if (0 < pos && pos < 10) {
				if (data.substr(0, pos) == "data") {
					license = CString::CStringT(CA2CT(data.substr(pos + 1).c_str()));
					LicenseData.SetWindowTextW(license);
					break;
				}
			}
		}
		fin.close();		
	}
	if (CEQSTNOTEDlg::DoEnroll()) {
		CEQSTNOTEDlg::EndDialog(IDOK);
	}

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CEQSTNOTEDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_LICENSE, LicenseData);
	DDX_Control(pDX, IDC_EROLL_STATUS, LicenseStatus);
}


BEGIN_MESSAGE_MAP(CEQSTNOTEDlg, CDialogEx)
	ON_BN_CLICKED(IDC_ENROLL_BUTTON, &CEQSTNOTEDlg::OnClickedEnrollButton)
	ON_BN_CLICKED(IDC_CANCEL, &CEQSTNOTEDlg::OnBnClickedCancel)
	ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()


// CEQSTNOTEDlg 메시지 처리기
void CEQSTNOTEDlg::OnClickedEnrollButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (CEQSTNOTEDlg::DoEnroll())
		CEQSTNOTEDlg::EndDialog(IDOK);
}

BOOL CEQSTNOTEDlg::DoEnroll() {
	CString str;
	std::string ini = "", tmp = "";
	CURL* curl;
	CURLcode res;
	curl_slist* slist = nullptr;
	char chArray[256] = { 0 };

	std::string post_response;

	LicenseData.GetWindowTextW(str);
	str = L"data=" + str;

	CStringA strA = CStringA(str);
	int strALen = strA.GetLength();
	memcpy(chArray, strA.GetBuffer(), strALen);

	if (strALen == 53) {
		curl_global_init(CURL_GLOBAL_DEFAULT);
		curl = curl_easy_init();

		if (curl) {
			curl_easy_setopt(curl, CURLOPT_URL, "http://sphan0325.ddns.net:28080/checklicense");

			curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_buffer_callback);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &post_response);

			slist = curl_slist_append(slist, "Accept: application/json");
			slist = curl_slist_append(slist, "charset: utf-8");
			curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist);

			curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, 256L);
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, chArray);

			res = curl_easy_perform(curl);

			if (!res) {
				if (post_response != "yes") {
					//::MessageBox(NULL, L"라이센스를 확인해주세요.", L"Check License", MB_OK);
					LicenseStatus.SetWindowTextW(L"라이선스 확인이 필요합니다.");
					return FALSE;
				}

				//::MessageBox(NULL, L"인증되었습니다.", L"Check License", MB_OK);
				LicenseStatus.SetWindowTextW(L"인증되었습니다.");

				ini = std::string(CT2CA(str.operator LPCWSTR()));

				//라이센스 저장
				std::ifstream fin("EQSTNOTE.INI");
				if (fin.is_open()) {
					std::size_t posEqual = 0;
					while (getline(fin, tmp)) {
						posEqual = tmp.find_first_of('=');
						if (0 < posEqual && posEqual < 10) {
							if (tmp.substr(0, posEqual) == "data") {
								tmp = "";
							}
							ini += tmp + "\n";
						}						
					}
					fin.close();
				}
				std::ofstream fout("EQSTNOTE.INI");
				if (fout.is_open()) {
					fout << ini;
					fout.close();
				}
				curl_slist_free_all(slist);
				curl_easy_cleanup(curl);
				curl_global_cleanup();
				return TRUE;
			}
		}
		LicenseStatus.SetWindowTextW(L"서버와 통신이 불가합니다.\n인터넷을 확인해주세요!");
		curl_slist_free_all(slist);
		curl_easy_cleanup(curl);
		curl_global_cleanup();
		return FALSE;
	}
	LicenseStatus.SetWindowTextW(L"라이선스 형식이 올바르지 않습니다.");
	return FALSE;
}

size_t write_buffer_callback(char* contents, size_t size, size_t nmemb, std::string* response)
{
	size_t count = size * nmemb;
	if (response != nullptr && count > 0)
	{
		response->append(contents, count);
	}

	return count;
}

void CEQSTNOTEDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CEQSTNOTEDlg::EndDialog(IDCANCEL);
}
