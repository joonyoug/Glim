// FileOpenDlg.cpp: 구현 파일
//

#include "pch.h"
#include "GlimProject.h"
#include "FileOpenDlg.h"


// FileOpenDlg

IMPLEMENT_DYNAMIC(FileOpenDlg, CFileDialog)

FileOpenDlg::FileOpenDlg(BOOL bOpenFileDialog, LPCTSTR lpszDefExt, LPCTSTR lpszFileName,
		DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd) :
		CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd)
{

}

FileOpenDlg::~FileOpenDlg()
{
}


BEGIN_MESSAGE_MAP(FileOpenDlg, CFileDialog)
END_MESSAGE_MAP()



// FileOpenDlg 메시지 처리기


