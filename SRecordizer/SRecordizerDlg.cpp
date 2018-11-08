
// SRecordizerDlg.cpp : 구현 파일
//
#include "stdafx.h"
#include "SRecordizer.h"
#include "SRecordizerDlg.h"
#include "afxdialogex.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
	// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:
};
CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}
void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}
BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)

END_MESSAGE_MAP()

// CSRecordizerDlg 대화 상자

CSRecordizerDlg::CSRecordizerDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CSRecordizerDlg::IDD, pParent)
, m_bInit(false)
, m_hFocus((HWND)0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
void CSRecordizerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
	DDX_Control(pDX, IDC_EDIT_MOD, m_EditMod);
}
BEGIN_MESSAGE_MAP(CSRecordizerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_FILE_OPEN32774, &CSRecordizerDlg::OnFileOpen32774)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CSRecordizerDlg::OnNMClickList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CSRecordizerDlg::OnNMDblclkList1)
	ON_COMMAND(ID_FILE_SAVE32772, &CSRecordizerDlg::OnFileSave32772)
	ON_WM_DROPFILES()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_FILE_OPENWITHHEXAVIEW, &CSRecordizerDlg::OnFileOpenwithhexaview)
	ON_COMMAND(ID_FILE_EXIT, &CSRecordizerDlg::OnFileExit)
	ON_COMMAND(ID_FILE_SAVEAS, &CSRecordizerDlg::OnFileSaveas)
END_MESSAGE_MAP()

// CSRecordizerDlg 메시지 처리기
BOOL CSRecordizerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.
	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	/*m_toolbar = new CToolBar();
	DWORD style = WS_CHILD | WS_VISIBLE | CBRS_TOOLTIPS;
	style |= (CBRS_ALIGN_TOP & CBRS_ALIGN_ANY);
	m_toolbar->CreateEx(this, TBSTYLE_FLAT, style);
	m_toolbar->LoadToolBar(IDR_TOOLBAR1);*/
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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
	SetIcon(m_hIcon, TRUE);   // 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);  // 작은 아이콘을 설정합니다.
	ShowWindow(SW_NORMAL);
	DragAcceptFiles(TRUE);
	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_ListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ListCtrl.InsertColumn(0, "#", 0, 30);
	m_ListCtrl.InsertColumn(1, "Sx", 0, 60);
	m_ListCtrl.InsertColumn(2, "Size", 0, 70);
	m_ListCtrl.InsertColumn(3, "Address", 0, 70);
	m_ListCtrl.InsertColumn(4, "Data", 0, 600);
	m_ListCtrl.InsertColumn(5, "Csum", 0, 70);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}
void CSRecordizerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.
void CSRecordizerDlg::OnPaint()
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
HCURSOR CSRecordizerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSRecordizerDlg::OnFileOpen32774()
{
	CString strCount = "";
	count = 0;
	static TCHAR BASED_CODE szFilter[] = _T("S-Record Files|*.s19;*.mhx|All Files (*.*)|*.*");
	CFileDialog dlg(TRUE, _T("*.s19"), _T("s19"), OFN_HIDEREADONLY, szFilter);
	if (IDOK == dlg.DoModal())
	{
		strFilePath = "";
		strFilePath = dlg.GetPathName();
		strBufferLine = "";
		if (!rfile.Open(dlg.GetPathName(), CFile::modeRead))
		{
			MessageBox("Can't Open File!!", "Warning", MB_OK);
			return;
		}
		while (rfile.ReadString(strBufferLine))
		{
			strCount.Format("%d", count);
			m_ListCtrl.InsertItem(count, strCount);
			//m_ListCtrl.SetItem(count, 1, LVIF_TEXT, strCount, 0, 0, 0, NULL);
			m_ListCtrl.SetItem(count, 1, LVIF_TEXT, strBufferLine.Left(2), 0, 0, 0, NULL);
			m_ListCtrl.SetItem(count, 2, LVIF_TEXT, strBufferLine.Mid(2, 2), 0, 0, 0, NULL);
			m_ListCtrl.SetItem(count, 3, LVIF_TEXT, strBufferLine.Mid(4, 6), 0, 0, 0, NULL);
			m_ListCtrl.SetItem(count, 4, LVIF_TEXT, strBufferLine.Mid(10, strBufferLine.GetLength() - 12), 0, 0, 0, NULL);
			//m_ListCtrl.SetItem(count, 5, LVIF_TEXT, strBufferLine.Mid(6. (strBifferLine.GetLegth() - 2)), 0, 0, 0, NULL);
			m_ListCtrl.SetItem(count, 5, LVIF_TEXT, strBufferLine.Right(2), 0, 0, 0, NULL);
			count++;
		}
		rfile.Close();
	}
}

void CSRecordizerDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	*pResult = 0;
}

void CSRecordizerDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMITEM = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	//LPNMITEMACTIVATE pNMITEM = (LPNMITEMACTIVATE)pNMHDR;
	iSavedItem = pNMITEM->iItem;
	iSavedSubitem = pNMITEM->iSubItem;
	if (pNMITEM->iItem != -1)
	{
		if (pNMITEM->iSubItem == 5)
		{
			MessageBox("Check Sum은 수정이 불가합니다.");
			return;
		}
		CRect rect;
		if (pNMITEM->iSubItem == 0)
		{
			m_ListCtrl.GetItemRect(pNMITEM->iItem, rect, LVIR_BOUNDS);
			rect.right = rect.left + m_ListCtrl.GetColumnWidth(0);
		}
		else
		{
			m_ListCtrl.GetSubItemRect(pNMITEM->iItem, pNMITEM->iSubItem, LVIR_BOUNDS, rect);
		}
		m_ListCtrl.ClientToScreen(rect);
		this->ScreenToClient(rect);
		GetDlgItem(IDC_EDIT_MOD)->SetWindowText(m_ListCtrl.GetItemText(pNMITEM->iItem, pNMITEM->iSubItem));
		GetDlgItem(IDC_EDIT_MOD)->SetWindowPos(NULL, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_SHOWWINDOW);
		GetDlgItem(IDC_EDIT_MOD)->SetFocus();
	}
	*pResult = 0;
}

void CSRecordizerDlg::OnFileSave32772()
{
	CString strBufferLine = "";
	count = 0;
	CFileException ex;
	OnOK();
	count = m_ListCtrl.GetItemCount();
	
	if (-1 == count || 0 == count)
	{
		AfxMessageBox(_T("저장할 데이터가 없습니다."));
		return;
	}

	if (!rfile.Open(strFilePath, CFile::modeCreate | CFile::modeReadWrite, &ex))
	{
		MessageBox("Can't Open File!!", "Warning", MB_OK);
		return;
	}
	
	UpdateData(TRUE);
	
	for (int i = 0; i<count; i++)
	{
		strBufferLine = m_ListCtrl.GetItemText(i, 1) + m_ListCtrl.GetItemText(i, 2) + m_ListCtrl.GetItemText(i, 3) + m_ListCtrl.GetItemText(i, 4) + m_ListCtrl.GetItemText(i, 5) + m_ListCtrl.GetItemText(i, 6) + "\n";
		rfile.WriteString(strBufferLine);
	}
	strBufferLine = "";
	CString strTemp = "저장에 성공했습니다. \n 저장 위치는 " + strFilePath + " 입니다.";
	MessageBox(strTemp);
	rfile.Close();
}


void CSRecordizerDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CString strCount = "";
	count = 0;
	int nFiles = 0;
	char szPathName[MAX_PATH] = "";
	DragQueryFile(hDropInfo, 0xffffffff, szPathName, MAX_PATH);
	nFiles = ::DragQueryFile(hDropInfo, 0, szPathName, MAX_PATH);
	nFiles = ::DragQueryFile(hDropInfo, 1, szPathName, MAX_PATH);

	if (nFiles > 1)
	{
		MessageBox("1개의 파일만 넣어주세요.");
		return;
	}

	::DragQueryFile(hDropInfo, 0xFFFFFFFF, szPathName, MAX_PATH);
	strFilePath = szPathName;

	if (!rfile.Open(strFilePath, CFile::modeRead))
	{
		MessageBox("Can't Open File!!", "Warning", MB_OK);
		return;
	}
	while (rfile.ReadString(strBufferLine))
	{
		strCount.Format("%d", count);
		m_ListCtrl.InsertItem(count, strCount);
		m_ListCtrl.SetItem(count, 1, LVIF_TEXT, strBufferLine.Left(2), 0, 0, 0, NULL);
		m_ListCtrl.SetItem(count, 2, LVIF_TEXT, strBufferLine.Mid(2, 2), 0, 0, 0, NULL);
		m_ListCtrl.SetItem(count, 3, LVIF_TEXT, strBufferLine.Mid(4, 6), 0, 0, 0, NULL);
		m_ListCtrl.SetItem(count, 4, LVIF_TEXT, strBufferLine.Mid(6, strBufferLine.GetLength() - 12), 0, 0, 0, NULL);
		m_ListCtrl.SetItem(count, 5, LVIF_TEXT, strBufferLine.Right(2), 0, 0, 0, NULL);
		count++;
	}
	CDialogEx::OnDropFiles(hDropInfo);
}


void CSRecordizerDlg::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CWnd* pWnd = GetFocus();

	if (_GetEditHwnd() == pWnd->GetSafeHwnd() ||
		_GetEditHwnd() == m_hFocus)
	{
		// EditCtrl로 부터 Text를 얻어온다.
		CString data = "";
		GetDlgItemText(IDC_EDIT_MOD, data);

		// 얻어온 텍스트를 ListCtrl 에 적용시킨다  
		if (SetText(data, iSavedItem, iSavedSubitem) == FALSE)
			return;

		int decData = 0, binData = 0;
		int strLength = 0;
		
		data = "";
		data = m_ListCtrl.GetItemText(iSavedItem, 2) + m_ListCtrl.GetItemText(iSavedItem, 3) + m_ListCtrl.GetItemText(iSavedItem, 4);
		strLength = data.GetLength();
		if (strLength < 2)
		{
			decData += conv.hextoDec(data);
		}
		else
		{
			for (int i = 0; i < strLength+1; i += 2)
			{
				decData += conv.hextoDec(data.Mid(i, 2));
			}
		}
		decData = ~decData & 0xFF;
		CString strCSum = "";
		strCSum.Format("%X", decData);

		if (SetText(strCSum, iSavedItem, 5) == FALSE)
			return;

		// EditCtrl의 Focus를 죽인다.  
		::SendMessage(_GetEditHwnd(), WM_KILLFOCUS, 0, 0);
		::ShowWindow(_GetEditHwnd(), SW_HIDE);
		::SetFocus(pWnd->GetSafeHwnd());
		m_EditMod.ShowWindow(SW_HIDE);

		// ListCtrl의 SelectionMark를 지정한다.  
		//SetSelectionMark(m_nItem);
	}

	m_hFocus = (HWND)0;
}



HWND CSRecordizerDlg::_GetEditHwnd(void)
{
	return ::GetDlgItem(GetParent()->GetSafeHwnd(), IDC_EDIT_MOD);
}

HWND CSRecordizerDlg::_GetListHwnd(void)
{
	return GetSafeHwnd();
}

HWND CSRecordizerDlg::_GetParentHwnd(void)
{
	return GetParent()->GetSafeHwnd();
}

BOOL CSRecordizerDlg::SetText(CString _val, int _row, int _col)
{  
    return m_ListCtrl.SetItemText(_row, _col, _val);  
}  


void CSRecordizerDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnLButtonUp(nFlags, point);
}

void CSRecordizerDlg::OnFileOpenwithhexaview()
{
	FILE *fp;
	int state;
	CString command = "";

	command = "cd C:\\Users\\user\\Documents\\Hexview";
	fp = popen(command, "r");
	if (fp == NULL)
	{
		perror("erro : ");
		printf("오류 [%d:%s]\n", errno, strerror(errno));
		MessageBox("HexView실행에 실패하였습니다.");
		//exit(0);
	}
	state = pclose(fp);

	command = "hexview.exe " + strFilePath;
	fp = popen(command, "r");
	if (fp == NULL)
	{
		perror("erro : ");
		printf("오류 [%d:%s]\n", errno, strerror(errno));
		MessageBox("HexView실행에 실패하였습니다.");
		//exit(0);
	}

	state = pclose(fp);
	//int i = WinExec("C:\\Users\\user\\Documents\\Hexview\\hexview.exe", SW_SHOW);// TODO: 여기에 명령 처리기 코드를 추가합니다.
	//if ()
}


void CSRecordizerDlg::OnFileExit()
{
	OnCancel();
}


void CSRecordizerDlg::OnFileSaveas()
{
	CString strBufferLine = "";
	count = 0;
	CFileException ex;
	OnOK();
	count = m_ListCtrl.GetItemCount();

	if (-1 == count || 0 == count)
	{
		AfxMessageBox(_T("저장할 데이터가 없습니다."));
		return;
	}

	static TCHAR BASED_CODE szFilter[] = _T("S-Record Files|*.s19;*.mhx|All Files (*.*)|*.*");
	CFileDialog dlg(TRUE, _T("*.s19"), _T("s19"), OFN_HIDEREADONLY, szFilter);
	if (IDOK == dlg.DoModal())
	{
		if (!rfile.Open(dlg.GetPathName(), CFile::modeCreate | CFile::modeReadWrite, &ex))
		{
			MessageBox("Can't Open File!!", "Warning", MB_OK);
			return;
		}

		UpdateData(TRUE);

		for (int i = 0; i<count; i++)
		{
			strBufferLine = m_ListCtrl.GetItemText(i, 1) + m_ListCtrl.GetItemText(i, 2) + m_ListCtrl.GetItemText(i, 3) + m_ListCtrl.GetItemText(i, 4) + m_ListCtrl.GetItemText(i, 5) + m_ListCtrl.GetItemText(i, 6) + "\n";
			rfile.WriteString(strBufferLine);
		}
		strBufferLine = "";
		CString strTemp = "저장에 성공했습니다. \n 저장 위치는 " + dlg.GetPathName() + " 입니다.";
		MessageBox(strTemp);
		rfile.Close();
	}

}
