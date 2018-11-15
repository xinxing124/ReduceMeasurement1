// ReduceMeasurementDlg.h : ͷ�ļ�
//

#pragma once
#include "ceseries.h"
#include "afxwin.h"

// CReduceMeasurementDlg �Ի���
class CReduceMeasurementDlg : public CDialog
{
// ����
public:
	CReduceMeasurementDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_REDUCEMEASUREMENT_DIALOG };


	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	afx_msg void OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/);
#endif
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButExit();
	afx_msg void OnBnClickedButSave();
	afx_msg void OnPaint();
	int intExitFlag;
	afx_msg void OnStnClickedStcTitle();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClose();
private:
	//�̺߳���
    static  DWORD WINAPI ThreadFunc(LPVOID lparam);
	//�رն��߳�
	void CloseThread();
private:
	//���߳̾��
	HANDLE m_hThread;
	//���߳�ID��ʶ
	DWORD m_dwThreadID;
	//����ֹͣ��ʶ
	DWORD m_dwRunFlag;
public:
	CCESeries *m_pSerial;
	int m_Pulse;
	unsigned long FlagCount;
	int iNUM;
	int RunFlag;
	int m_DIR;

	double GetValue(void);
	afx_msg void OnStnClickedStcImage();
	// �����ȫ�ֵġ��ŵ�include������Ϳ�����
	CFont cfont;
	CFont ccfont;
	afx_msg void OnBnClickedButTest();
	afx_msg void OnBnClickedButExtended();
	int FileWrite(CString filename, CString content);
	int FileRead(CString filename,CString* content);
	void Split(CString source, CStringArray& dest, CString division);
	CString ReturnPath(void);
	afx_msg void OnDestroy();
	unsigned long m_SendCout;
	double GetMaxValue(CArray <double> *data, int dstart, int dfinish);
	//int GetStandardPos(CArray <double> * data, int * start,int * middle, int * finish);
	int GetStandardPos(CArray <double> * data, int * start, int * finish);
};
