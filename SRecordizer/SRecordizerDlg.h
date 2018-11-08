
// SRecordizerDlg.h : ��� ����
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include <algorithm>
#include <list>
#include <string>
#include "string" 
#include "list" 
#include "iostream" 
#include "sstream" 
#include "iterator" 
#include "Conversion.h"

#define popen _popen
#define pclose _pclose
// CSRecordizerDlg ��ȭ ����
class CSRecordizerDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CSRecordizerDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SRECORDIZER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	HWND _GetEditHwnd(void);
	HWND _GetListHwnd(void);
	HWND _GetParentHwnd(void);
private:
	CToolBar *m_toolbar;
	CStdioFile rfile;
	CString strBufferLine;
	int count;
	int iSavedItem, iSavedSubitem;
	CString strFilePath;
public:
	CListCtrl m_ListCtrl;
	afx_msg void OnFileOpen32774();
	afx_msg void OnFileSave32772();
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	virtual void OnOK();
	//BOOL SetText(CString _val, int _row, int _col);
	// ���� ��Ŀ���� ����� Ȯ���ϴ� ����  
	HWND m_hFocus;

	bool m_bInit;
	// List ���� �ٲ۴�.  
	BOOL SetText(CString _val, int _row, int _col);
	//virtual BOOL PreTranslateMessage(MSG* pMsg);
	CEdit m_EditMod;
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	CString* Chunk(CString str, int chunkSize);
	void Chunk(CString str, int chunkSize, CString* result);
	CString ChangeCSum(CString data, int dataLength);
	CConversion conv;
	int DEC2BIN(int num);
	afx_msg void OnFileOpenwithhexaview();
	afx_msg void OnFileExit();
	afx_msg void OnFileSaveas();
};
