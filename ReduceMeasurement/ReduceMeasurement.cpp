// ReduceMeasurement.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "ReduceMeasurement.h"
#include "ReduceMeasurementDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CReduceMeasurementApp

BEGIN_MESSAGE_MAP(CReduceMeasurementApp, CWinApp)
END_MESSAGE_MAP()


// CReduceMeasurementApp ����
CReduceMeasurementApp::CReduceMeasurementApp()
	: CWinApp()
	, AppFilePath(_T(""))
	, AppFileContent(_T(""))
	, AppStandardContent(_T(""))
	, AppParameterContent(_T(""))
	, AppIdentification(_T(""))
	, AppTurnoutNumber(_T(""))
	, AppMeasurementType(_T(""))
	, AppMeasurementPos(_T(""))
	, AppStandardVal(_T(""))
	, AppMeasurementVal(_T(""))
	, AppDifferenceVal(_T(""))
	, AppPosStart(0)
	, AppPosFinish(0)
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CReduceMeasurementApp ����
CReduceMeasurementApp theApp;

// CReduceMeasurementApp ��ʼ��

BOOL CReduceMeasurementApp::InitInstance()
{

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CReduceMeasurementDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}
