// ReduceMessageDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ReduceMeasurement.h"
#include "ReduceMessageDlg.h"


// CReduceMessageDlg �Ի���

IMPLEMENT_DYNAMIC(CReduceMessageDlg, CDialog)

CReduceMessageDlg::CReduceMessageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReduceMessageDlg::IDD, pParent)
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
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	ON_WM_SIZE()
#endif
	ON_BN_CLICKED(IDOK, &CReduceMessageDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CReduceMessageDlg::OnBnClickedCancel)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_COMBO2, &CReduceMessageDlg::OnCbnSelchangeCombo2)
	ON_CBN_DROPDOWN(IDC_COMBO2, &CReduceMessageDlg::OnCbnDropdownCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CReduceMessageDlg::OnCbnSelchangeCombo3)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CReduceMessageDlg::OnCbnSelchangeCombo1)
	ON_CBN_DROPDOWN(IDC_COMBO3, &CReduceMessageDlg::OnCbnDropdownCombo3)
	ON_CBN_SELCHANGE(IDC_COMBO4, &CReduceMessageDlg::OnCbnSelchangeCombo4)
	ON_CBN_DROPDOWN(IDC_COMBO4, &CReduceMessageDlg::OnCbnDropdownCombo4)
	ON_CBN_CLOSEUP(IDC_COMBO4, &CReduceMessageDlg::OnCbnCloseupCombo4)
END_MESSAGE_MAP()

BOOL CReduceMessageDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
int ret=0;
	CString strTmp;

	
	//ret=FileRead(_T("\\ResidentFlash2\\GUI\\xishu.txt"),&strTmp);

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
	Split(theApp.AppParameterContent,souce,_T("}"));
//AfxExtractSubString
	CString strTemp;
	((CComboBox*)GetDlgItem(IDC_COMBO1))->ResetContent();//����������������
	

int Count = souce.GetSize();
int nCount;
//MessageBox(dest[0], _T(""), MB_OK);
//strTemp.Format(_T("%d"),nCount);
//MessageBox(strTemp, _T(""), MB_OK);

CString sTmp;
int pos=0;
for(int i=0;i<Count-1;i++)
{

//MessageBox(NULL, souce[i], _T(""), MB_OK);
	Split(souce[i],dest,_T(","));
	nCount = dest.GetSize();
	pos=dest[0].FindOneOf(_T("{"));
	if(pos==-1) pos=1;
	((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(dest[0].Mid(pos+1));
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
	((CButton*)GetDlgItem(IDC_BUT_SAVE))->EnableWindow(false);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
void CReduceMeasurementDlg::OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/)
{
	if (AfxIsDRAEnabled())
	{
		DRA::RelayoutDialog(
			AfxGetResourceHandle(), 
			this->m_hWnd, 
			DRA::GetDisplayMode() != DRA::Portrait ? 
			MAKEINTRESOURCE(IDD_REDUCEMEASUREMENT_DIALOG_WIDE) : 
			MAKEINTRESOURCE(IDD_REDUCEMEASUREMENT_DIALOG));
	}
}
#endif

// CReduceMessageDlg ��Ϣ�������

void CReduceMessageDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SYSTEMTIME st;
	CString strDate,strTime;
	GetLocalTime(&st);
	strDate.Format(_T("%4d%02d%02d"),st.wYear,st.wMonth,st.wDay);

	//CString strTemp_01,strTemp_02,strTemp_03,strTemp_04,strTemp_05,strTemp_06;
	//((CComboBox*)GetDlgItem(IDC_COMBO1))->GetWindowTextW(strTemp_01);
	//((CComboBox*)GetDlgItem(IDC_COMBO2))->GetWindowTextW(strTemp_02);
	//((CComboBox*)GetDlgItem(IDC_COMBO3))->GetWindowTextW(strTemp_03);
	//((CComboBox*)GetDlgItem(IDC_COMBO4))->GetWindowTextW(strTemp_04);
	//strTemp_05.Format(_T("%.3f"),theApp.Val);
	theApp.AppFilePath= _T("\\Ӳ��\\") +strDate +_T(".txt");
	if(::GetFileAttributes(theApp.AppFilePath) == 0xFFFFFFFF){
		
		m_Temp=_T("λ�ñ�ʶ\t������\t����λ��(m)\t��׼ֵ(mm)\t����ֵ(mm)\t��ֵ(mm)\r\n");
	}
	//else{
	//	m_Temp=_T("");
	//}
	////		λ�ñ�ʶ			������			����λ��			��׼ֵ				����ֵ				��ֵ
	//m_Temp+=strTemp_01+_T("\t")+strTemp_02+_T("\t")+strTemp_03+_T("\t")+strTemp_04+_T("\t")+strTemp_05+_T("\t")+strTemp_06+_T("\r\n");
	////FileWrite(_T("\\ResidentFlash2\\GUI\\") +strDate +_T(".txt"),m_Temp);
	FileWrite(theApp.AppFilePath,m_Temp);

	CString str;
	//str.Format(L"��׼ֵ��%s\n����ֵ��%s\n",theApp.AppStandardVal,theApp.AppMeasurementVal);
	str.Format(L"��׼ֵ��%s\n����ֵ��0.0\n",theApp.AppStandardVal);
	this->GetParent()->GetDlgItem(IDC_STC_CONTENT)->SetWindowTextW(str);
	OnOK();
}

void CReduceMessageDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnCancel();
}

int CReduceMessageDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	return 0;
}

void CReduceMessageDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
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
	Split(theApp.AppParameterContent,souce,_T("}"));

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
		for(int j=1;j<nCount;j+=2)
		{
		//((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(dest[j].Mid(1));
			((CComboBox*)GetDlgItem(IDC_COMBO2))->AddString(dest[j]);
		}
	}

}

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
void CReduceMessageDlg::OnCbnSelchangeCombo3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CReduceMessageDlg::OnCbnSelchangeCombo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CReduceMessageDlg::OnCbnDropdownCombo3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

}

void CReduceMessageDlg::OnCbnSelchangeCombo4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CReduceMessageDlg::OnCbnDropdownCombo4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CStringArray souce;
	CStringArray dest;
	CStringArray soucest;
	CStringArray destst;
	CString str;
	int pos=0;
	Split(theApp.AppParameterContent,souce,_T("}"));
	Split(theApp.AppStandardContent,soucest,_T("}"));
	CString strTemp;
	CString strValue;
	int Count = souce.GetSize();
	int nCount;
	int Num=soucest.GetSize();
	int nNum;
	for(int i=0;i<Count;i++)
	{
		Split(souce[i],dest,_T(","));
		nCount = dest.GetSize();

		if(i==((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel())
		{
			pos=dest[0].FindOneOf(_T("{"));
			if(pos==-1) pos=1;
			TRACE(_T("%s\n"),dest[0].Mid(pos+1));
			theApp.AppIdentification= dest[0].Mid(pos+1);
			for(int j=0;j<nCount;j++)
			{
				if(j==((CComboBox*)GetDlgItem(IDC_COMBO2))->GetCurSel())
				{
					TRACE(_T("%s\n"),dest[j*2+1]);
					theApp.AppTurnoutNumber= dest[j*2+1];
					for(int k=0;k<2;k++)
					{
						if(k==((CComboBox*)GetDlgItem(IDC_COMBO3))->GetCurSel())
						{
							((CComboBox*)GetDlgItem(IDC_COMBO3))->GetLBText(k,strValue);
							TRACE(_T("%s\n"),strValue);
							theApp.AppMeasurementType=strValue;
							for(int m=0;m<Num-1;m++)
							{
								TRACE(_T("Souce:%s\n"),soucest[m]);
								TRACE(_T("Dest:%s\n"),dest[j*2+2]);
								if(soucest[m].Find(dest[j*2+2])>0)
								{
									Split(soucest[m],destst,_T(";"));
									Split(destst[k+1],deststr,_T(","));
									nNum = deststr.GetSize();
									((CComboBox*)GetDlgItem(IDC_COMBO4))->ResetContent();//����������������
									for(int n=0;n<nNum;n+=2)
									{
										((CComboBox*)GetDlgItem(IDC_COMBO4))->AddString(deststr[n]);

									}

								}
							}
							break;
						}
					}	
				}
			}
		}

	}
}

void CReduceMessageDlg::OnCbnCloseupCombo4()
{
	int index;

	//	CReduceMeasurementApp();
	//CString AppFileContent;
	//CString AppStandardContent;
	//CString AppParameterContent;
	//CString AppIdentification;
	//CString AppTurnoutNumber;
	//CString AppMeasurementPos;
	//CString AppStandardVal;
	//CString AppMeasurementVal;
	//CString AppDifferenceVal;

	if(((CComboBox*)GetDlgItem(IDC_COMBO4))->GetCurSel()>-1)
	{	index=((CComboBox*)GetDlgItem(IDC_COMBO4))->GetCurSel();
		theApp.AppMeasurementPos=deststr[index*2];
		TRACE(_T("%s\n"),deststr[index*2]);
		theApp.AppStandardVal=deststr[index*2+1];
		TRACE(_T("%s\n"),deststr[index*2+1]);
	}
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	TRACE0( "����\n"  );
}
