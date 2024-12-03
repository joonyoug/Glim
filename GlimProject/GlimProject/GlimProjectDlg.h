
// GlimProjectDlg.h: 헤더 파일
//
#include <iostream>
#include <string>
#include <vector>
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#pragma once

using namespace std;

// CGlimProjectDlg 대화 상자
class CGlimProjectDlg : public CDialogEx
{
// 생성입니다.
public:
	CGlimProjectDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	CImage m_image;
	int m_height=0;
	int m_width=0;
	int m_radius=0;
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GLIMPROJECT_DIALOG };
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

	void drawInitial();    //처음 화면 검정색으로 나타내는 기능 
	void onUpdate();      //화면에 그려주는 기능 
	void makeCircle(int inputX1, int inputY1);  // 원을 그리는 기능  
	BOOL checkValidation(int x, int y, int xCenter, int yCentrt, int radius);  //해당 죄표에 반지름이 타당한지 검사 하는기능
	void drawCircleLine(int xCenter, int yCenter, int radisu);
	afx_msg void OnBnClickedBtnDraw();  // Draw 버튼 동작 
	vector<string> split(string input, string delimiter); //문자열 split 기능
	afx_msg void OnBnClickedBtnAction();   // Action 버튼 동작
	void moveCircle(int x1, int y1, int x2, int y2);  //원을 움직이는 기능 
	BOOL checkPosition(int x, int y); // 해당 좌표가 타당하진 검사 기능 
	void writeRadius(int radius);
	void checkRedius();
	afx_msg void OnBnClickedBtnLoad();
};
