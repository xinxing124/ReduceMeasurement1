// ReduceMeasurement.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#ifdef STANDARDSHELL_UI_MODEL
#include "resource.h"
#endif

// CReduceMeasurementApp:
// �йش����ʵ�֣������ ReduceMeasurement.cpp
//

class CReduceMeasurementApp : public CWinApp
{
public:
	CReduceMeasurementApp();
	CString AppFilePath;
	CString AppFileContent;
	CString AppStandardContent;
	CString AppParameterContent;
	CString AppIdentification;
	CString AppTurnoutNumber;
	CString AppMeasurementType;
	CString AppMeasurementPos;
	CString AppStandardVal;
	CString AppMeasurementVal;
	CString AppDifferenceVal;
	double Val;
	int AppPosStart;
	int AppPosFinish;

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()

};

extern CReduceMeasurementApp theApp;
