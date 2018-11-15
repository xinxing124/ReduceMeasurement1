// MessageDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ReduceMessageDlg.h"
#include "ReduceMeasurement.h"


// CReduceMessageDlg �Ի���

IMPLEMENT_DYNAMIC(CReduceMessageDlg, CDialog)

CReduceMessageDlg::CReduceMessageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReduceMessageDlg::IDD, pParent)
	, existfile(false)
	, m_Temp(_T(""))
{

}

CReduceMessageDlg::~CReduceMessageDlg()
{
}

void CReduceMessageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CReduceMessageDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CReduceMessageDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CReduceMessageDlg::OnBnClickedCancel)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CReduceMessageDlg::OnCbnSelchangeCombo2)
	ON_CBN_DROPDOWN(IDC_COMBO2, &CReduceMessageDlg::OnCbnDropdownCombo2)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CReduceMessageDlg ��Ϣ�������

void CReduceMessageDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SYSTEMTIME st;
	CString strDate,strTime;
	GetLocalTime(&st);
	strDate.Format(_T("%4d%02d%02d"),st.wYear,st.wMonth,st.wDay);

	CString strTemp_01,strTemp_02,strTemp_03,strTemp_04,strTemp_05,strTemp_06;
	((CComboBox*)GetDlgItem(IDC_COMBO1))->GetWindowTextW(strTemp_01);
	((CComboBox*)GetDlgItem(IDC_COMBO2))->GetWindowTextW(strTemp_02);
	((CComboBox*)GetDlgItem(IDC_COMBO3))->GetWindowTextW(strTemp_03);
	((CComboBox*)GetDlgItem(IDC_COMBO4))->GetWindowTextW(strTemp_04);
	strTemp_05.Format(_T("%.3f"),theApp.Val);
	
	if(::GetFileAttributes(_T("\\Ӳ��\\") +strDate +_T(".txt")) == 0xFFFFFFFF){
		
		m_Temp=_T("λ�ñ�ʶ\t������\t����λ��(m)\t��׼ֵ(mm)\t����ֵ(mm)\t��ֵ(mm)\r\n");
	}
	else{
		m_Temp=_T("");
	}
	//		λ�ñ�ʶ			������			����λ��			��׼ֵ				����ֵ				��ֵ
	m_Temp+=strTemp_01+_T("\t")+strTemp_02+_T("\t")+strTemp_03+_T("\t")+strTemp_04+_T("\t")+strTemp_05+_T("\t")+strTemp_06+_T("\r\n");
	//FileWrite(_T("\\ResidentFlash2\\GUI\\") +strDate +_T(".txt"),m_Temp);
	FileWrite(_T("\\Ӳ��\\") +strDate +_T(".txt"),m_Temp);
		
	OnOK();
}

void CReduceMessageDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnCancel();
}


BOOL CReduceMessageDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SYSTEMTIME st;
	CString strDate,strTime;
	GetLocalTime(&st);
	strDate.Format(_T("%4d%02d%02d"),st.wYear,st.wMonth,st.wDay);
	//strTime.Format("%2d:%2d:2d", st.wHour,st.wMinute,st.wSecond);
	/*
	//if(::GetFileAttributes(_T("\\ResidentFlash2\\GUI\\") +strDate +_T(".txt")) == 0xFFFFFFFF){
	if(::GetFileAttributes(_T("\\Ӳ��\\") +strDate +_T(".txt")) == 0xFFFFFFFF){
		existfile=false;
		m_Temp=_T("վ��;�����;����;�����;����ֵ\r\n");
	}
	else{
		existfile=true;
		//FileRead(_T("\\ResidentFlash2\\GUI\\") +strDate +_T(".txt"),&m_Temp);
		m_Temp=_T("");
		FileRead(_T("\\Ӳ��\\") +strDate +_T(".txt"),&m_Temp);
	}
	*/
	/*
	CWnd   *pEdit   =   GetDlgItem(IDC_COMBO1);
	CFont   *pfont   =   pEdit->GetFont();
	LOGFONT   logfont;
	pfont->GetLogFont(&logfont);
	logfont.lfHeight   =   -12;
	m_font.CreateFontIndirect(&logfont);
	pEdit->SetFont(&m_font);
	
	
	GetDlgItem(IDC_STATIC01)->SetFont(&m_font);
	GetDlgItem(IDC_STATIC02)->SetFont(&m_font);
	GetDlgItem(IDC_STATIC03)->SetFont(&m_font);
	GetDlgItem(IDC_STATIC04)->SetFont(&m_font);
	
	GetDlgItem(IDOK)->SetFont(&m_font);
	GetDlgItem(IDCANCEL)->SetFont(&m_font);
	*/
	//IDC_STATIC01

	//theApp.FileContent
	//theApp.FileContent.
	CStringArray souce;
	CStringArray dest;
	Split(theApp.FileContent,souce,_T("}"));
//AfxExtractSubString
	CString strTemp;
	((CComboBox*)GetDlgItem(IDC_COMBO1))->ResetContent();//����������������
	

int Count = souce.GetSize();
int nCount;
//MessageBox(dest[0], _T(""), MB_OK);
//strTemp.Format(_T("%d"),nCount);
//MessageBox(strTemp, _T(""), MB_OK);


for(int i=0;i<Count;i++)
{

//MessageBox(NULL, souce[i], _T(""), MB_OK);

	Split(souce[i],dest,_T(","));
	nCount = dest.GetSize();
	((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(dest[0].Mid(1));
	//for(int j=0;j<nCount;j++)
	//{
		//MessageBox(dest[j].Mid(1), _T(""), MB_OK);
	//((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(dest[j].Mid(1));
	//	((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(dest[j]);
	//}
//strTemp.Format(_T("%d"),nCount);
//MessageBox(strTemp, _T(""), MB_OK);

	//((CComboBox*)GetDlgItem(IDC_COMBO2))->AddString(souce[0]);


}
//strTemp.Mid(1);

/*
	�磺 //�ؼ����ݳ�ʼ��
 CString strTemp;
 ((CComboBox*)GetDlgItem(IDC_COMBO1))->ResetContent();//����������������
 for(int i=1;i<=100;i++)
 {
  strTemp.Format("%d",i);
  ((CComboBox*)GetDlgItem(IDC_COMBO_CF))->AddString(strTemp);
 }
3��������ʱ�����
�磺 CString strTemp;
 int iCount=((CComboBox*)GetDlgItem(IDC_COMBO_CF))->GetCount();//ȡ��Ŀǰ�Ѿ��е�����
 if(iCount<1)//��ֹ�ظ�������
 {
  ((CComboBox*)GetDlgItem(IDC_COMBO_CF))->ResetContent();
  for(int i=1;i<=100;i++)
  {
   strTemp.Format("%d",i);
   ((CComboBox*)GetDlgItem(IDC_COMBO_CF))->AddString(strTemp);
  }
 }
*/
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

//д���ļ�
int CReduceMessageDlg::FileWrite(CString filename=_T(""),CString content=_T(""))
{
	HANDLE hFile = INVALID_HANDLE_VALUE;	// �ļ���� 
	// ����һ���ļ����һ���ļ�
	hFile = CreateFile(filename, GENERIC_READ | GENERIC_WRITE, 0, 
					   NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		//AfxMessageBox(_T("�����ļ�ʧ��!"));
		return -1;
	}

	DWORD len,actlen;
	char *pcharbuff;

	//len = content.GetLength();							// ȡ�������ַ����ĳ���
	len=CStringA(content).GetLength();

	pcharbuff = new char[len];
	LPTSTR pStr = content.GetBuffer(len);					// ȡ�������ַ����Ļ�����ָ��

	// �� Unicode �� CString ת��Ϊ char ��
	WideCharToMultiByte(CP_ACP, 0, pStr, len, pcharbuff, len, NULL, NULL);
	content.ReleaseBuffer();

	BOOL ret = SetFilePointer(hFile, 0, NULL, FILE_END);	// �ƶ��ļ�ָ�뵽�ļ���ͷ
	if (ret == 0xFFFFFFFF)
	{
		//AfxMessageBox(_T("���ļ�ָ�������ļ���ͷʧ��!"));
		delete[] pcharbuff;
		return -2;	
	}

	ret = WriteFile(hFile, pcharbuff, len, &actlen, NULL);	// ������д���ļ��� 
	
	if (pcharbuff != NULL) 
		delete[] pcharbuff;

	CloseHandle(hFile);
	if (ret == TRUE)
		return 0;
		//AfxMessageBox(_T("д�ļ��ɹ�!"));	
	else
		return -3;
		//AfxMessageBox(_T("д�ļ�ʧ��!"));	
}

int CReduceMessageDlg::FileRead(CString filename,CString* content)
{
	int lRet;
	HANDLE hFile = INVALID_HANDLE_VALUE;	// �ļ���� 
	if(::GetFileAttributes(filename) == 0xFFFFFFFF)
	{
	//::AfxMessageBox(_T("�ļ�������"));
		return -5;
	}
	// ����һ���ļ����һ���ļ�
	hFile = CreateFile(filename, GENERIC_READ | GENERIC_WRITE, 0, 
					   NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		//AfxMessageBox(_T("���ļ�ʧ��!"));
		return -1;
	}

	DWORD filelen,actlen;
	char *pcharbuff;
	
	filelen = GetFileSize(hFile, NULL);							// ��ȡ�ļ���С
	if (filelen == 0xFFFFFFFF)
	{
		//AfxMessageBox(_T("��ȡ�ļ���Сʧ��!"));
		return -2;	
	}

	BOOL ret = SetFilePointer(hFile, 0, NULL, FILE_BEGIN);		// �ƶ��ļ�ָ�뵽�ļ���ͷ
	if (ret == 0xFFFFFFFF)
	{
		//AfxMessageBox(_T("���ļ�ָ�������ļ���ͷʧ��!"));
		return -3;	
	}

	pcharbuff = new char[filelen];
	ret = ReadFile(hFile, pcharbuff, filelen, &actlen, NULL);	// ���ļ��ж������� 
	if (ret == TRUE)
	{
		LPTSTR pStr = content->GetBuffer(filelen);	
		// ���ֽ�ת��Ϊ Unicode �ַ���
		MultiByteToWideChar(CP_ACP, 0, pcharbuff, filelen, pStr, filelen);
		content->ReleaseBuffer();
		//AfxMessageBox(_T("���ļ��ɹ�!"));	
		lRet=0;
	}
	else
	{
		//AfxMessageBox(_T("���ļ�ʧ��!"));	
		lRet=-4;
	}

	if (pcharbuff != NULL) 
		delete[] pcharbuff;

	CloseHandle(hFile);
	return lRet;
}

void CReduceMessageDlg::Split(CString source, CStringArray& dest, CString division)
{
    dest.RemoveAll();
    int pos = 0;
    int pre_pos = 0;
    while( -1 != pos ){
        pre_pos = pos;
        pos = source.Find(division,(pos));
		if(pos<0)
			dest.Add(source.Mid(pre_pos));
		else
		{
			dest.Add(source.Mid(pre_pos,(pos-pre_pos)));
			pos++;
		}
		
    }
}

void CReduceMessageDlg::OnCbnSelchangeCombo2()
{
// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CReduceMessageDlg::OnCbnDropdownCombo2()
{
	
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CStringArray souce;
	CStringArray dest;
	Split(theApp.FileContent,souce,_T("}"));

	CString strTemp;
	

int Count = souce.GetSize();
int nCount;

for(int i=0;i<Count;i++)
{
	Split(souce[i],dest,_T(","));
	nCount = dest.GetSize();

	if(i==((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel())
	{
		((CComboBox*)GetDlgItem(IDC_COMBO2))->ResetContent();//����������������
		for(int j=1;j<nCount;j++)
		{
		//((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(dest[j].Mid(1));
			((CComboBox*)GetDlgItem(IDC_COMBO2))->AddString(dest[j]);
		}
	}

}


}

void CReduceMessageDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	//m_font.DeleteObject();
}
