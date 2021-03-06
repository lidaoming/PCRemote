
// PCRemoteDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "TrueColorToolBar.h"
#include <conio.h>
#include "include/IOCPServer.h"

// CPCRemoteDlg 对话框
class CPCRemoteDlg : public CDialogEx
{
// 构造
public:
	CPCRemoteDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_PCREMOTE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CStatusBar  m_wndStatusBar; //程序状态条
	//当前有几个客户端上线
	int iCount;
	//工具栏
	CTrueColorToolBar m_ToolBar;
	//系统托盘
	NOTIFYICONDATA nid;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	//IOCP回调函数
	static void CALLBACK NotifyProc(LPVOID lpParam, ClientContext* pContext, UINT nCode);
	//启动IOCP监听端口
	void Activate(UINT nPort, UINT nMaxConnections);
public:
	CListCtrl m_CList_Online;
	CListCtrl m_CList_Message;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	// 初始化计算机上线的列表内容
	int InitList();
	// 插入上线列表的方法
	void AddList(CString strIP, CString strAddr, CString strPCName, CString strOS, CString strCPU, CString strVideo, CString strPing);
	// 消息列表插入函数
	void ShowMessage(bool bIsOK, CString strMsg);
	// 测试用
	void Test();
	afx_msg void OnNMRClickOnline(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnOnlineCmd();
	afx_msg void OnOnlineDesktop();
	afx_msg void OnOnlineFile();
	afx_msg void OnOnlineProcess();
	afx_msg void OnOnlineReg();
	afx_msg void OnOnlineService();
	afx_msg void OnOnlineVideo();
	afx_msg void OnOnlineVoice();
	afx_msg void OnOnlineWindow();
	afx_msg void OnOnlineDelete();
	afx_msg void OnClose();
	afx_msg void OnMainAbout();
	afx_msg void OnMainBuild();
	afx_msg void OnMainSet();
	//以下是我自己的消息处理回调函数
	//处理托盘消息回调函数
	afx_msg void OnIconNotify(WPARAM wParam, LPARAM lParam);

	// 创建状态栏
	void CreatStatusBar();
	afx_msg void OnLvnItemchangedMessage(NMHDR *pNMHDR, LRESULT *pResult);
	// 添加工具栏
	void CreateToolBar();
	afx_msg void OnNotifyClose();
	afx_msg void OnNotifyShow();
	// 开启监听端口
	void ListenPort();
};
