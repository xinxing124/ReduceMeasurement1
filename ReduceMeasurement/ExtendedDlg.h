#pragma once


// ExtendedDlg �Ի���

class ExtendedDlg : public CDialog
{
	DECLARE_DYNAMIC(ExtendedDlg)

public:
	ExtendedDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ExtendedDlg();

// �Ի�������
	enum { IDD = IDD_EXTENDED_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
