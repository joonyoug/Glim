
// GlimProjectDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "GlimProject.h"
#include "GlimProjectDlg.h"
#include "afxdialogex.h"
#include "FileOpenDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif



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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CGlimProjectDlg 대화 상자



CGlimProjectDlg::CGlimProjectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GLIMPROJECT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGlimProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGlimProjectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	
	ON_BN_CLICKED(IDC_BTN_DRAW, &CGlimProjectDlg::OnBnClickedBtnDraw)
	ON_BN_CLICKED(IDC_BTN_ACTION, &CGlimProjectDlg::OnBnClickedBtnAction)
	ON_BN_CLICKED(IDC_BTN_LOAD, &CGlimProjectDlg::OnBnClickedBtnLoad)
END_MESSAGE_MAP()


// CGlimProjectDlg 메시지 처리기

BOOL CGlimProjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CGlimProjectDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CGlimProjectDlg::OnPaint()
{	
	drawInitial();
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
HCURSOR CGlimProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





void CGlimProjectDlg::drawInitial()
{

	CRect rect;
	GetClientRect(&rect);

	m_height = rect.Height() - 10;
	m_width = rect.Width();
	//cout << m_height << endl;
	//cout << m_width << endl;
	int nBpp = 8;


	m_image.Create(m_width, -m_height, nBpp);


	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0;i < 256;i++) {         
			rgb[i].rgbRed = rgb[i].rgbBlue = rgb[i].rgbGreen = i;
		}
		m_image.SetColorTable(0, 256, rgb);
	}

	int nPitch = m_image.GetPitch();

	unsigned char* fm = (unsigned char*)m_image.GetBits();

	memset(fm, 0x00, m_width * m_height);  //검정으로 m_image 

	onUpdate();

}
void CGlimProjectDlg::onUpdate()
{
	CClientDC dc(this);
	m_image.Draw(dc, 0, 50);

}

void CGlimProjectDlg::makeCircle(int inputX1, int inputY1)
{

	int nBpp = 8;
	int nPitch = m_image.GetPitch();
	CString input2;

	GetDlgItemText(IDC_EDIT_INPUT2, input2);

	unsigned char* fm = (unsigned char*)m_image.GetBits();

	memset(fm, 0x00, m_height * m_width);

	int radius = m_radius;

	if (input2.IsEmpty()) {
		radius = rand() % 50 + 1;
		m_radius = radius;
	}

	std::cout << "(X,Y):=" << inputX1 << "," << inputY1 << " radius:" << radius << std::endl;

	for (int i = 0;i < m_height;i++) {
		for (int j = 0;j < m_width;j++) {
			if (checkValidation(j, i, inputX1, inputY1, radius)) {
				fm[i * nPitch + j] = 0xff;   
			}
		}
	}
	onUpdate();
}

BOOL CGlimProjectDlg::checkValidation(int x, int y, int xCenter, int yCenter, int radius) {
	//반지름 유효성 체크
	double dX = x - xCenter;
	double dY = y - yCenter;
	double dDist = dX * dX + dY * dY;
	return dDist <= radius * radius;

}
void CGlimProjectDlg::checkRedius() {

	int first[2] = { -1, -1 };
	int last[2] = { -1, -1 };
	int cnt = 0;
	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();  // 이미지의 비트맵 데이터

	// 첫 번째와 마지막 픽셀을 찾음
	for (int i = 0; i < m_height; i++) {
		for (int j = 0; j < m_width; j++) {
			if (fm[i * nPitch + j] == 0xff) {
				if (cnt == 0) {
					first[0] = j;
					first[1] = i;
				}
				cnt++;
				last[0] = j;
				last[1] = i;
			}
		}
	}

	// 픽셀이 하나도 발견되지 않으면 처리 종료
	if (first[0] == -1 || last[0] == -1) {
		return;  // 첫 번째와 마지막 픽셀이 없으면 더 이상 진행하지 않음
	}

	// 중심 좌표와 반지름 계산
	int dX = first[0] - last[0];
	int dY = first[1] - last[1];

	int dDist = dX * dX + dY * dY;
	double radius = sqrt(dDist) / 2;  // 원의 반지름

	int xCenter = (first[0] + last[0]) / 2;  // 원의 중심 x좌표
	int yCenter = (first[1] + last[1]) / 2;  // 원의 중심 y좌표

	// 디버깅 정보 출력
	cout << "Center: (" << xCenter << ", " << yCenter << ")" << endl;
	cout << "Radius: " << radius << endl;

	drawCircleLine(xCenter, yCenter, radius );
	writeRadius(radius / 2);
	

}



void CGlimProjectDlg::drawCircleLine(int xCenter,int yCenter,int radius)
{
	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();
	// X 모양 그리기
	int len = 10;  // X 모양의 선 길이

	// 대각선 1: 왼쪽 위에서 오른쪽 아래로
	for (int i = 0; i < len; i++) {
		int px1 = xCenter - i;
		int py1 = yCenter - i;
		int px2 = xCenter + i;
		int py2 = yCenter + i;

		if (px1 >= 0 && px1 < m_width && py1 >= 0 && py1 < m_height) {
			fm[py1 * nPitch + px1] = 80;  // 대각선 선 그리기 (왼쪽 위에서 오른쪽 아래)
		}
		if (px2 >= 0 && px2 < m_width && py2 >= 0 && py2 < m_height) {
			fm[py2 * nPitch + px2] = 80;  // 대각선 선 그리기 (오른쪽 아래에서 왼쪽 위)
		}
	}

	// 대각선 2: 왼쪽 아래에서 오른쪽 위로
	for (int i = 0; i < len; i++) {
		int px1 = xCenter - i;
		int py1 = yCenter + i;
		int px2 = xCenter + i;
		int py2 = yCenter - i;

		if (px1 >= 0 && px1 < m_width && py1 >= 0 && py1 < m_height) {
			fm[py1 * nPitch + px1] = 80;  // 대각선 선 그리기 (왼쪽 아래에서 오른쪽 위)
		}
		if (px2 >= 0 && px2 < m_width && py2 >= 0 && py2 < m_height) {
			fm[py2 * nPitch + px2] = 80;  // 대각선 선 그리기 (오른쪽 위에서 왼쪽 아래)
		}
	}


	onUpdate();	
	
}

void CGlimProjectDlg::writeRadius(int radius) {


	CString strRadius;
	strRadius.Format(_T("Radius: %d"), radius);

	CDC* pDC = GetDC();  
	CFont font;

	pDC->SelectObject(&font);  // 폰트 적용
	font.CreatePointFont(200, _T("Arial"));
	pDC->SetTextColor(RGB(255, 0, 0));  

	// m_image의 중앙 좌표 구하기
	int centerX = m_width / 2;
	int centerY = m_height / 2;


	// 중앙에 텍스트 출력 (약간의 오프셋을 주어 정확한 중앙에 표시)
	pDC->TextOut(centerX - 100, centerY - 30, strRadius);

	ReleaseDC(pDC);
	UpdateWindow();

}





void CGlimProjectDlg::OnBnClickedBtnDraw()
{
	CString input;
	vector<string> inputXY;

	GetDlgItemText(IDC_EDIT_INPUT1, input);

	if (input.IsEmpty()) {
		AfxMessageBox(_T("x1,y1의값을 입력해주세요(  , 로구분)"));
		return;
	}
	inputXY = split(string(CT2A(input)), ",");

	if (inputXY.size() != 2) {
		AfxMessageBox(_T("잘못입력하셨습니다."));
		return;
	}

	makeCircle(stoi(inputXY[0]), stoi(inputXY[1]));
	//std::cout << inputXY[0] << " " << inputXY[1] << std::endl;

	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_INPUT2);  // 읽기전용에서 쓰기 가능하게 
	pEdit->SetReadOnly(FALSE);

}
vector<string> CGlimProjectDlg::split(string input, string delimiter)
{
	// x,y -> x y 로 나누기 위해 구현 
	vector<string> str;
	long long pos = 0;
	string front = "";

	while ((pos = input.find(delimiter)) != string::npos)
	{
		front = input.substr(0, pos);
		str.push_back(front);
		input = input.erase(0, pos + delimiter.length());

	}
	if (!input.empty()) {
		str.push_back(input);
	}

	return str;
}


void CGlimProjectDlg::moveCircle(int x1, int y1, int x2, int y2)
{

	int stepSize = 10;   //한번에 이동할 픽셀수

	// x, y 방향 이동 거리 계산
	int dX = x2 - x1;
	int dY = y2 - y1;

	// 이동 루프
	while (x1 != x2 || y1 != y2) {
		// 한 번에 이동할 x, y 값 계산

		if (x1 != x2) {
			x1 += stepSize * (dX != 0 ? dX / abs(dX) : 0);
		}
		if (y1 != y2) {
			y1 += stepSize * (dY != 0 ? dY / abs(dY) : 0);
		}

		makeCircle(x1, y1);
		Sleep(100);

		CString fileName;

		fileName.Format(_T("C:\\Users\\epgis\\Desktop\\glim\\GlimProject\\GlimProject\\rescircle_%d_%d.bmp"), x1, y1); 
	
		m_image.Save(fileName); 
	}
	SetDlgItemText(IDC_EDIT_INPUT2, _T(""));
}



BOOL CGlimProjectDlg::checkPosition(int x, int y)
{
	if (x<0 || y<0 || x>m_height || y>m_height) {
		return false;   // 좌표값이 유효한지 검사
	}
	return true;
}



void CGlimProjectDlg::OnBnClickedBtnAction()
{
	CString start, end;

	GetDlgItemText(IDC_EDIT_INPUT1, start);  //시작 좌표
	GetDlgItemText(IDC_EDIT_INPUT2, end);    // 끝 좌표

	vector<string> startPos = split(string(CT2A(start)), ",");  //startPos[0] ->x1 , startPos[1] -> y1 의 좌표
	vector<string> endPos = split(string(CT2A(end)), ",");   //endPos[0] ->x2 , endPos[1] ->y2 의 좌표


	if (startPos.size() != 2 || endPos.size() != 2) {
		AfxMessageBox(_T("잘못입력하셨습니다."));
		return;
	}
	bool checkInput1 = checkPosition(stoi(startPos[0]), stoi(startPos[1]));
	bool checkInput2 = checkPosition(stoi(endPos[0]), stoi(endPos[1]));
	if (!checkInput1 || !checkInput2) {

		AfxMessageBox(_T("죄표값을 잘못입력하셨습니다"));
		SetDlgItemText(IDC_EDIT_INPUT1, _T(""));
		SetDlgItemText(IDC_EDIT_INPUT2, _T(""));
		return;
	}
	moveCircle(stoi(startPos[0]), stoi(startPos[1]), stoi(endPos[0]), stoi(endPos[1]));

}


void CGlimProjectDlg::OnBnClickedBtnLoad()
{
		FileOpenDlg fileDlg(TRUE, _T(""), _T(""),
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST,
		_T("Image Files (*.bmp;*.jpg;*.png)|*.bmp;*.jpg;*.png|All Files (*.*)|*.*||"), this);

	if (fileDlg.DoModal() == IDOK)
	{
		CImage image;

		CString filePath = fileDlg.GetPathName();

		HRESULT hr = image.Load(filePath);

		if (hr != S_OK) {
			AfxMessageBox(_T("이미지 로드 실패"));
			return;
		}

		CDC* pDC = GetDC();  

		image.Draw(pDC->GetSafeHdc(), 0, 50); 

		m_image=image;   // 

		checkRedius();

		ReleaseDC(pDC);  // DC 해제

	}

}