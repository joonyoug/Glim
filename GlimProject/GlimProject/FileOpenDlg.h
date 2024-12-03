#pragma once


// FileOpenDlg

class FileOpenDlg : public CFileDialog
{
	DECLARE_DYNAMIC(FileOpenDlg)

public:
	FileOpenDlg(BOOL bOpenFileDialog, // FileOpen은 TRUE, FileSaveAs는 FALSE입니다.
		LPCTSTR lpszDefExt = nullptr,
		LPCTSTR lpszFileName = nullptr,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = nullptr,
		CWnd* pParentWnd = nullptr);
	virtual ~FileOpenDlg();

protected:
	DECLARE_MESSAGE_MAP()
};


