
// PCRemoteDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"


// CPCRemoteDlg �Ի���
class CPCRemoteDlg : public CDialogEx
{
// ����
public:
	CPCRemoteDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PCREMOTE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	CStatusBar  m_wndStatusBar; //����״̬��
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_CList_Online;
	CListCtrl m_CList_Message;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	// ��ʼ����������ߵ��б�����
	int InitList();
	// ���������б�ķ���
	void AddList(CString strIP, CString strAddr, CString strPCName, CString strOS, CString strCPU, CString strVideo, CString strPing);
	// ��Ϣ�б���뺯��
	void ShowMessage(bool bIsOK, CString strMsg);
	// ������
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
	// ����״̬��
	void CreatStatusBar();
	afx_msg void OnLvnItemchangedMessage(NMHDR *pNMHDR, LRESULT *pResult);
};
