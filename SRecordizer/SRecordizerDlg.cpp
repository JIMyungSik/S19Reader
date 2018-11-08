
// SRecordizerDlg.cpp : ���� ����
//
#include "stdafx.h"
#include "SRecordizer.h"
#include "SRecordizerDlg.h"
#include "afxdialogex.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	// �����Դϴ�.
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

// CSRecordizerDlg ��ȭ ����

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

// CSRecordizerDlg �޽��� ó����
BOOL CSRecordizerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.
	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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
	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);   // ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);  // ���� �������� �����մϴ�.
	ShowWindow(SW_NORMAL);
	DragAcceptFiles(TRUE);
	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_ListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ListCtrl.InsertColumn(0, "#", 0, 30);
	m_ListCtrl.InsertColumn(1, "Sx", 0, 60);
	m_ListCtrl.InsertColumn(2, "Size", 0, 70);
	m_ListCtrl.InsertColumn(3, "Address", 0, 70);
	m_ListCtrl.InsertColumn(4, "Data", 0, 600);
	m_ListCtrl.InsertColumn(5, "Csum", 0, 70);

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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
// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.
void CSRecordizerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}
// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
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
			MessageBox("Check Sum�� ������ �Ұ��մϴ�.");
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
		AfxMessageBox(_T("������ �����Ͱ� �����ϴ�."));
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
	CString strTemp = "���忡 �����߽��ϴ�. \n ���� ��ġ�� " + strFilePath + " �Դϴ�.";
	MessageBox(strTemp);
	rfile.Close();
}


void CSRecordizerDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CString strCount = "";
	count = 0;
	int nFiles = 0;
	char szPathName[MAX_PATH] = "";
	DragQueryFile(hDropInfo, 0xffffffff, szPathName, MAX_PATH);
	nFiles = ::DragQueryFile(hDropInfo, 0, szPathName, MAX_PATH);
	nFiles = ::DragQueryFile(hDropInfo, 1, szPathName, MAX_PATH);

	if (nFiles > 1)
	{
		MessageBox("1���� ���ϸ� �־��ּ���.");
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
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	CWnd* pWnd = GetFocus();

	if (_GetEditHwnd() == pWnd->GetSafeHwnd() ||
		_GetEditHwnd() == m_hFocus)
	{
		// EditCtrl�� ���� Text�� ���´�.
		CString data = "";
		GetDlgItemText(IDC_EDIT_MOD, data);

		// ���� �ؽ�Ʈ�� ListCtrl �� �����Ų��  
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

		// EditCtrl�� Focus�� ���δ�.  
		::SendMessage(_GetEditHwnd(), WM_KILLFOCUS, 0, 0);
		::ShowWindow(_GetEditHwnd(), SW_HIDE);
		::SetFocus(pWnd->GetSafeHwnd());
		m_EditMod.ShowWindow(SW_HIDE);

		// ListCtrl�� SelectionMark�� �����Ѵ�.  
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

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
		printf("���� [%d:%s]\n", errno, strerror(errno));
		MessageBox("HexView���࿡ �����Ͽ����ϴ�.");
		//exit(0);
	}
	state = pclose(fp);

	command = "hexview.exe " + strFilePath;
	fp = popen(command, "r");
	if (fp == NULL)
	{
		perror("erro : ");
		printf("���� [%d:%s]\n", errno, strerror(errno));
		MessageBox("HexView���࿡ �����Ͽ����ϴ�.");
		//exit(0);
	}

	state = pclose(fp);
	//int i = WinExec("C:\\Users\\user\\Documents\\Hexview\\hexview.exe", SW_SHOW);// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
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
		AfxMessageBox(_T("������ �����Ͱ� �����ϴ�."));
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
		CString strTemp = "���忡 �����߽��ϴ�. \n ���� ��ġ�� " + dlg.GetPathName() + " �Դϴ�.";
		MessageBox(strTemp);
		rfile.Close();
	}

}
