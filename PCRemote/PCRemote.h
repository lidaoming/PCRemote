
// PCRemote.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "IniFile.h"

// CPCRemoteApp: 
// �йش����ʵ�֣������ PCRemote.cpp
//

class CPCRemoteApp : public CWinApp
{
public:
	CPCRemoteApp();

// ��д
public:
	virtual BOOL InitInstance();

//�����ļ�
public:
	CIniFile m_IniFile;
// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CPCRemoteApp theApp;