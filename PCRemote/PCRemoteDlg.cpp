
// PCRemoteDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PCRemote.h"
#include "PCRemoteDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//列的个数
int g_Column_Online_Count = 7;

//Message 列的个数
int g_Column_Count_Message = 3;

//ListControl结构体
typedef struct
{
	char	*title;           //列表的名称
	int		nWidth;   //列表的宽度
}COLUMNSTRUCT;

COLUMNSTRUCT g_Column_online_Data[] =
{
	{ "IP", 148 },
	{ "区域", 150 },
	{ "计算机名/备注", 160 },
	{ "操作系统", 128 },
	{ "CPU", 80 },
	{ "摄像头", 81 },
	{ "PING", 81 }
};

//list_Control_message 类型
COLUMNSTRUCT g_Column_Data_Message[] =
{
	{ "信息类型", 88 },
	{ "时间", 100 },
	{ "信息内容", 660 }
};

//上线列表总宽度
 int g_Column_Online_Width=0;  //列总宽度

 //消息列表总宽度
 int g_Column_Message_Width = 0;  //列总宽度






//全局变量结束=======================================================================================

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CPCRemoteDlg 对话框



CPCRemoteDlg::CPCRemoteDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPCRemoteDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
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
END_MESSAGE_MAP()


// CPCRemoteDlg 消息处理程序

BOOL CPCRemoteDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码


	//添加菜单
	HMENU hmenu;
	hmenu = LoadMenu(NULL, MAKEINTRESOURCE(IDR_MENU_MAIN));  //载入菜单资源
	::SetMenu(this->GetSafeHwnd(), hmenu);                  //为窗口设置菜单
	::DrawMenuBar(this->GetSafeHwnd());                    //显示菜单
	InitList();
	//显示状态栏
	CreatStatusBar();
	ShowMessage(true, "软件初始化成功...");
	CRect rect;
	GetWindowRect(&rect);
	rect.bottom += 20;
	MoveWindow(rect);

	//测试用
	Test();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPCRemoteDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CPCRemoteDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPCRemoteDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	double dcx = cx;     //对话框的当前总宽度
	// TODO:  在此处添加消息处理程序代码
	if (m_CList_Online.m_hWnd != NULL)
	{
		CRect rc;
		rc.left = 1;       //列表的左坐标
		rc.top = 80;       //列表的上坐标
		rc.right = cx - 1;  //列表的右坐标
		rc.bottom = cy - 160;  //列表的下坐标
		m_CList_Online.MoveWindow(rc);

		for (int i = 0; i<g_Column_Online_Count; i++)
		{                   
			//遍历每一个列
			double dd = g_Column_online_Data[i].nWidth;     //得到当前列的宽度
			dd /= g_Column_Online_Width;                    //看一看当前宽度占总长度的几分之几
			dd *= dcx;                                       //用原来的长度乘以所占的几分之几得到当前的宽度
			int lenth = dd;                                   //转换为int 类型
			m_CList_Online.SetColumnWidth(i, (lenth));        //设置当前的宽度
		}
	}
	if (m_CList_Message.m_hWnd != NULL)
	{
		CRect rc;
		rc.left = 1;        //列表的左坐标
		rc.top = cy - 156;    //列表的上坐标
		rc.right = cx - 1;    //列表的右坐标
		rc.bottom = cy - 15;  //列表的下坐标
		m_CList_Message.MoveWindow(rc);

		for (int i = 0; i<g_Column_Count_Message; i++)
		{
			//遍历每一个列
			double dd = g_Column_Data_Message[i].nWidth;     //得到当前列的宽度
			dd /= g_Column_Message_Width;                    //看一看当前宽度占总长度的几分之几
			dd *= dcx;                                       //用原来的长度乘以所占的几分之几得到当前的宽度
			int lenth = dd;                                   //转换为int 类型
			m_CList_Message.SetColumnWidth(i, (lenth));        //设置当前的宽度
		}
	}

	//状态栏
	if (m_wndStatusBar.m_hWnd != NULL){    //当对话框大小改变时 状态条大小也随之改变
		CRect rc;
		rc.top = cy - 20;
		rc.left = 0;
		rc.right = cx;
		rc.bottom = cy;
		m_wndStatusBar.MoveWindow(rc);
		m_wndStatusBar.SetPaneInfo(0, m_wndStatusBar.GetItemID(0), SBPS_POPOUT, cx - 10);
	}
}


// 初始化计算机上线以及消息的列表内容
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


// 插入上线列表的方法
void CPCRemoteDlg::AddList(CString strIP, CString strAddr, CString strPCName, CString strOS, CString strCPU, CString strVideo, CString strPing)
{
	m_CList_Online.InsertItem(0, strIP);           //默认为0行  这样所有插入的新列都在最上面
	m_CList_Online.SetItemText(0, ONLINELIST_ADDR, strAddr);      //设置列的显示字符   这里 ONLINELIST_ADDR等 为第二节课中的枚举类型 用这样的方法
	m_CList_Online.SetItemText(0, ONLINELIST_COMPUTER_NAME, strPCName); //解决问题会避免以后扩展时的冲突
	m_CList_Online.SetItemText(0, ONLINELIST_OS, strOS);
	m_CList_Online.SetItemText(0, ONLINELIST_CPU, strCPU);
	m_CList_Online.SetItemText(0, ONLINELIST_VIDEO, strVideo);
	m_CList_Online.SetItemText(0, ONLINELIST_PING, strPing);
}


// 消息列表插入函数
void CPCRemoteDlg::ShowMessage(bool bIsOK, CString strMsg)
{
	CString strIsOK, strTime;
	CTime t = CTime::GetCurrentTime();
	strTime = t.Format("%H:%M:%S");
	if (bIsOK)
	{
		strIsOK = "执行成功";
	}
	else{
		strIsOK = "执行失败";
	}
	m_CList_Message.InsertItem(0, strIsOK);
	m_CList_Message.SetItemText(0, 1, strTime);
	m_CList_Message.SetItemText(0, 2, strMsg);
}


// 测试用
void CPCRemoteDlg::Test()
{
	AddList("192.168.0.1", "本机局域网", "Lang", "Windows7", "2.2GHZ", "有", "123232");
	AddList("192.168.0.1", "本机局域网", "Lang", "Windows7", "2.2GHZ", "有", "123232");
	AddList("192.168.0.1", "本机局域网", "Lang", "Windows7", "2.2GHZ", "有", "123232");
	ShowMessage(true, "软件初始化成功...");

}


void CPCRemoteDlg::OnNMRClickOnline(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	CMenu	popup;
	popup.LoadMenu(IDR_MENU_ONLINE);
	CMenu*	pM = popup.GetSubMenu(0);
	CPoint	p; //获取位置
	GetCursorPos(&p);
	int	count = pM->GetMenuItemCount(); //获取菜单条目
	if (m_CList_Online.GetSelectedCount() == 0)       //如果没有选中
	{
		for (int i = 0; i < count; i++)
		{
			pM->EnableMenuItem(i, MF_BYPOSITION | MF_DISABLED | MF_GRAYED);          //菜单全部变灰
		}

	}
	pM->TrackPopupMenu(TPM_LEFTALIGN, p.x, p.y, this);

	*pResult = 0;
}


//执行cmd命令
void CPCRemoteDlg::OnOnlineCmd()
{
	// TODO:  在此添加命令处理程序代码
	MessageBox("命令执行");
}


//桌面管理
void CPCRemoteDlg::OnOnlineDesktop()
{
	// TODO:  在此添加命令处理程序代码
	MessageBox("桌面管理");
}


void CPCRemoteDlg::OnOnlineFile()
{
	// TODO:  在此添加命令处理程序代码
	MessageBox("文件管理");
}


void CPCRemoteDlg::OnOnlineProcess()
{
	// TODO:  在此添加命令处理程序代码
	MessageBox("进程管理");
}


void CPCRemoteDlg::OnOnlineReg()
{
	// TODO:  在此添加命令处理程序代码
	MessageBox("注册表管理");
}


void CPCRemoteDlg::OnOnlineService()
{
	// TODO:  在此添加命令处理程序代码
	MessageBox("服务管理");
}


void CPCRemoteDlg::OnOnlineVideo()
{
	// TODO:  在此添加命令处理程序代码
	MessageBox("视频管理");
}



void CPCRemoteDlg::OnOnlineVoice()
{
	// TODO:  在此添加命令处理程序代码
	MessageBox("音频管理");
}


void CPCRemoteDlg::OnOnlineWindow()
{
	// TODO:  在此添加命令处理程序代码
	MessageBox("窗口管理");
}


void CPCRemoteDlg::OnOnlineDelete()
{
	// TODO:  在此添加命令处理程序代码
	//删除ONLINE listcontrol中的条目

	//向日志列表添加消息记录
	CString strIP;
	//得到用户选定的条目
	int iSelect = m_CList_Online.GetSelectionMark();
	//得到ip
	strIP = m_CList_Online.GetItemText(iSelect, ONLINELIST_IP);
	//删除条目
	m_CList_Online.DeleteItem(iSelect);
	strIP += " 断开连接";
	ShowMessage(true, strIP);
}

//菜单文件点击退出
void CPCRemoteDlg::OnClose()
{
	// TODO:  在此添加命令处理程序代码
	PostMessage(WM_CLOSE, 0, 0);
}


void CPCRemoteDlg::OnMainAbout()
{
	// TODO:  在此添加命令处理程序代码
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}


void CPCRemoteDlg::OnMainBuild()
{
	// TODO:  在此添加命令处理程序代码
	MessageBox("服务端生成");
}


void CPCRemoteDlg::OnMainSet()
{
	// TODO:  在此添加命令处理程序代码
	MessageBox("参数设置");
}

//状态栏数组
static UINT indicators[] =
{
	IDR_STATUSBAR_STRING
};

// 创建状态栏
// create  status bar
void CPCRemoteDlg::CreatStatusBar(void)
{
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		sizeof(indicators) / sizeof(UINT)))                    //创建状态条并设置字符资源的ID
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
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
}
