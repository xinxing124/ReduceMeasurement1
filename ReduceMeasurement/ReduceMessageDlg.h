#pragma once
#include "resource.h"

// CReduceMessageDlg �Ի���

class CReduceMessageDlg : public CDialog
{
	DECLARE_DYNAMIC(CReduceMessageDlg)

public:
	CReduceMessageDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CReduceMessageDlg();

// �Ի�������
	enum { IDD = IDD_REDUCEMESSAGE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
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
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnCbnDropdownCombo2();
public:
	CString m_Temp;
	int FileWrite(CString filename,CString content);
	int FileRead(CString filename,CString* content);
	void Split(CString source, CStringArray& dest, CString division);
	afx_msg void OnCbnSelchangeCombo3();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnDropdownCombo3();
	afx_msg void OnCbnSelchangeCombo4();
	afx_msg void OnCbnDropdownCombo4();
	afx_msg void OnCbnCloseupCombo4();
	CStringArray deststr;
};
