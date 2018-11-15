// ReduceMeasurementDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HDI_API.h"
#include "ReduceMessageDlg.h"
#include "ReduceMeasurement.h"
#include "ReduceMeasurementDlg.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CReduceMeasurementDlg �Ի���
#define pi 3.1415926535898
//���߳��˳��¼�
HANDLE g_hDetIOEvent;
CArray <double> m_Array;

extern BYTE* pRecvBuf;
extern long pRecvLen;

CDC MemDC; //���ȶ���һ����ʾ�豸����
CBitmap MemBitmap;//����һ��λͼ����
CBitmap *pOldBit;

CReduceMeasurementDlg::CReduceMeasurementDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReduceMeasurementDlg::IDD, pParent)
	, m_pSerial(NULL)
	, intExitFlag(0)
	, m_Pulse(0)
	,m_dwRunFlag(0)
	, FlagCount(0)
	, iNUM(0)
	, RunFlag(0)
	,m_DIR(0)
	, m_SendCout(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CReduceMeasurementDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CReduceMeasurementDlg, CDialog)
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	ON_WM_SIZE()
#endif
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUT_EXIT, &CReduceMeasurementDlg::OnBnClickedButExit)
	ON_BN_CLICKED(IDC_BUT_SAVE, &CReduceMeasurementDlg::OnBnClickedButSave)
	ON_WM_PAINT()
	ON_STN_CLICKED(IDC_STC_TITLE, &CReduceMeasurementDlg::OnStnClickedStcTitle)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUT_TEST, &CReduceMeasurementDlg::OnBnClickedButTest)
	ON_BN_CLICKED(IDC_BUT_EXTENDED, &CReduceMeasurementDlg::OnBnClickedButExtended)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

//�رն��߳�
void CReduceMeasurementDlg::CloseThread()
{
	SetEvent(g_hDetIOEvent);
    //�ȴ�4�룬������߳�û���˳�����ǿ���˳�
    if (WaitForSingleObject(m_hThread,4000) == WAIT_TIMEOUT)
	{
		TerminateThread(m_hThread,0);
	}
	m_hThread = NULL;
}

// CReduceMeasurementDlg ��Ϣ�������
DWORD CReduceMeasurementDlg::ThreadFunc(LPVOID lparam)
{
	CReduceMeasurementDlg *hDlg = (CReduceMeasurementDlg*)lparam;
	CCESeries *pSerial=hDlg->m_pSerial;
	BYTE buf[]={0x02,0x43,0xB0,0x01,0x03,0xF2};
	BYTE *revbuf=NULL;
	DWORD revlen=0;
	DWORD errlen=0;
	double data=0.0;
	double temp=0.0;
	DWORD dwRet;
	UINT8 Level;
	CString ss;
	CString str;
	int CW=0;
	bool DropFlag=false;
	int Num=0;
	hDlg->FlagCount=0;
	while (TRUE)
	{   	
		//����յ����߳��˳��źţ����˳��߳�
		dwRet=WaitForSingleObject(g_hDetIOEvent,50);
		if (dwRet== WAIT_OBJECT_0)//����ģʽ
		{
			//::AfxMessageBox(_T("1"));
			break;
		}
		if ( dwRet== WAIT_TIMEOUT)//�޷��س�ʱ
		{
			break;
		}
		//if(hDlg->RunFlag==1)
		//{
		//	Sleep(500);
		//	hDlg->RunFlag=2;
		//}
		if(hDlg->RunFlag==2)
		{
			CW=1;
			//API_GPIO_Input(2,&Level);//��ֹͣ�ź�
			//if(Level==1)
			//{       
			//	Sleep(100);
			//	hDlg->RunFlag=0;
			//	//API_GPIO_Output(2, 0);
			//	API_GPIO_Output(0,0);
			//	API_GPIO_Output(1,0);
			//	CW=0;
			//	str.Format(L"�ɼ�������%d\n����������%d",hDlg->FlagCount,Num);
			//	TRACE(_T("%s"),str);
			//	hDlg->FlagCount=0;
			//	hDlg->Invalidate();
			//	//str="";
			//	//for(int i=0;i<(int)m_Array.GetSize();i++)
			//	//{
			//	//	ss.Format(_T("%d:%f;\n"),i,m_Array.GetAt(i));
			//	//	TRACE(_T("%s"),ss);
			//	//	//str.Append(ss);
			//	//}
			//	//str1.append (str2);   //��str2���ӵ�str1��
			//	//TRACE(_T("%s"),str);
			//	TRACE0( "ֹͣ�źš���\n"  );

			//}
			//API_GPIO_Input(1,&Level);//�������ź�
			//if(Level==1)
			//{
			//	revbuf=pSerial->Command((BYTE*)buf,sizeof(buf),&revlen);
			//	Sleep(100);
			//	//CW=CW!=0?0:1;
			//	CW=1;
			//	//API_GPIO_Output(1,CW);
			//	API_GPIO_Output(0,0);
			//	API_GPIO_Output(1,1);
			//	hDlg->FlagCount=0;
			//	m_Array.RemoveAll();  //ɾ������Ԫ��
			//	//hDlg->Invalidate();
			//	hDlg->m_SendCout=0;
			//	TRACE0( "�����źš���\n"  );
			//}
			if(CW==1)
			{
				Sleep(0);
				API_GPIO_Input(0,&Level);//���ɼ��ź�
				if(Level==0 && DropFlag==true)
				{
					DropFlag=false;
					//data=rand()%50;

					//TRACE0( "Start Dump of MyClass members:\n"  );
					//hDlg->FlagCount++;
					hDlg->FlagCount++;
					
					revbuf=pSerial->Command((BYTE*)buf,sizeof(buf),&revlen);
					if(revlen==6)
					{
					if(revbuf[0] == 0x02&&revbuf[1] == 0x06&&revbuf[4] == 0x03)
						data=(revbuf[2]*256+revbuf[3])/100.0;
						if(data>327.67) data=data-655.35;
						temp=data;
						hDlg->m_SendCout++;
					}
					else
					{
						data=temp;
					}
					data=data*(-1.0);
					m_Array.Add(data);

					////data=hDlg->GetValue();
					////if(CW==1)
					////{
					//
					////str.Format(L"�ɼ���ţ�%d\n",hDlg->FlagCount);
					////TRACE(_T("%s"),str);
					//m_Array.Add(data);
					//hDlg->Invalidate();
					//}
					//double x,y;
					//CListBox *plist=(CListBox*)GetDlgItem(IDC_LIST1);
					//CString str;
					//str.Format(L"%lf",data);
					//plist->AddString((LPCTSTR)str); 
					//CWnd   *pWnd   =   ReduceMeasurementDlg->GetDlgItem(IDC_STC_IMAGE);     

					//pWnd->Invalidate();  
					//pWnd->UpdateWindow();
					//hDlg->Invalidate();
				}
				else if(Level==1)
				{
					DropFlag=true;
				}
			}
		}
		else
		{
			Sleep(1);
		}

		//if(CW==0) Sleep(1);
	}
	return 0;
}

BOOL CReduceMeasurementDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	CWnd*  pWnd=NULL;
	cfont.CreateFont(36,        //������־��������С��
		  0,0,0,FW_NORMAL,  
		  FALSE,FALSE,  
		  0,  
		  ANSI_CHARSET,              // nCharSet
		  OUT_DEFAULT_PRECIS,        // nOutPrecision
		  CLIP_DEFAULT_PRECIS,       // nClipPrecision
		  DEFAULT_QUALITY,           // nQuality
		  DEFAULT_PITCH | FF_SWISS, L"Arial");
		pWnd = GetDlgItem(IDC_STC_TITLE);
		pWnd->SetFont(&cfont);

 
	ccfont.CreateFont(24,        //������־��������С��
	  0,0,0,FW_NORMAL,  
	  FALSE,FALSE,  
	  0,  
	  ANSI_CHARSET,              // nCharSet
	  OUT_DEFAULT_PRECIS,        // nOutPrecision
	  CLIP_DEFAULT_PRECIS,       // nClipPrecision
	  DEFAULT_QUALITY,           // nQuality
	  DEFAULT_PITCH | FF_SWISS, L"����");//Arial
	pWnd = GetDlgItem(IDC_STC_CONTENT);
	pWnd->SetFont(&ccfont);


	//m_Array.Add(0.1);
	//m_Array.Add(0.2);
	//m_Array.Add(0.5);
	//m_Array.Add(0.6);
	//int s1,s2;
	//double sc=GetMaxValue(&m_Array,2,4); 
	//GetStandardPos(&m_Array,&s1,&s2);
//m_Array.Add(-327.67);
//m_Array.Add(-327.67);
//m_Array.Add(-327.67);
//m_Array.Add(-327.67);
//m_Array.Add(-327.67);
//m_Array.Add(-327.67);
//m_Array.Add(-327.67);
//m_Array.Add(-327.67);
//m_Array.Add(-327.67);
//m_Array.Add(-327.67);
//
//m_Array.Add(-28.06);
//m_Array.Add(-27.65);
//m_Array.Add(-27.45);
//m_Array.Add(-27.15);
//m_Array.Add(-26.69);
//m_Array.Add(-26.47);
//m_Array.Add(-26.03);
//m_Array.Add(-25.8);
//m_Array.Add(-25.44);
//m_Array.Add(-25.04);
//m_Array.Add(-24.88);
//m_Array.Add(-24.65);
//m_Array.Add(-24.42);
//m_Array.Add(-24.07);
//m_Array.Add(-23.87);
//m_Array.Add(-23.67);
//m_Array.Add(-23.3);
//m_Array.Add(-22.96);
//m_Array.Add(-22.65);
//m_Array.Add(-22.25);
//m_Array.Add(-22.01);
//m_Array.Add(-21.74);
//m_Array.Add(-21.38);
//m_Array.Add(-21.08);
//m_Array.Add(-20.79);
//m_Array.Add(-20.5);
//m_Array.Add(-20.25);
//m_Array.Add(-20.04);
//m_Array.Add(-19.86);
//m_Array.Add(-19.48);
//m_Array.Add(-19.26);
//m_Array.Add(-19.1);
//m_Array.Add(-18.72);
//m_Array.Add(-18.38);
//m_Array.Add(-18.1);
//m_Array.Add(-17.67);
//m_Array.Add(-17.37);
//m_Array.Add(-16.98);
//m_Array.Add(-16.68);
//m_Array.Add(-16.38);
//m_Array.Add(-16.1);
//m_Array.Add(-15.85);
//m_Array.Add(-15.65);
//m_Array.Add(-15.37);
//m_Array.Add(-15.05);
//m_Array.Add(-14.79);
//m_Array.Add(-14.54);
//m_Array.Add(-14.27);
//m_Array.Add(-14.05);
//m_Array.Add(-13.69);
//m_Array.Add(-13.41);
//m_Array.Add(-13.17);
//m_Array.Add(-12.71);
//m_Array.Add(-12.45);
//m_Array.Add(-12.17);
//m_Array.Add(-11.84);
//m_Array.Add(-11.6);
//m_Array.Add(-11.26);
//m_Array.Add(-11.05);
//m_Array.Add(-10.84);
//m_Array.Add(-10.54);
//m_Array.Add(-10.29);
//m_Array.Add(-10.01);
//m_Array.Add(-9.77);
//m_Array.Add(-9.47);
//m_Array.Add(-9.15);
//m_Array.Add(-8.84);
//m_Array.Add(-8.59);
//m_Array.Add(-8.26);
//m_Array.Add(-8.03);
//m_Array.Add(-7.75);
//m_Array.Add(-7.43);
//m_Array.Add(-7.14);
//m_Array.Add(-6.79);
//m_Array.Add(-6.52);
//m_Array.Add(-6.23);
//m_Array.Add(-5.99);
//m_Array.Add(-5.62);
//m_Array.Add(-327.67);
//m_Array.Add(-4.81);
//m_Array.Add(-4.55);
//m_Array.Add(-4.34);
//m_Array.Add(-4.07);
//m_Array.Add(-3.85);
//m_Array.Add(-3.63);
//m_Array.Add(-3.37);
//m_Array.Add(-3.08);
//m_Array.Add(-2.81);
//m_Array.Add(-2.47);
//m_Array.Add(-2.17);
//m_Array.Add(-1.93);
//m_Array.Add(-1.41);
//m_Array.Add(-1.14);
//m_Array.Add(-0.89);
//m_Array.Add(-0.65);
//m_Array.Add(-0.38);
//m_Array.Add(-0.09);
//m_Array.Add(0.26);
//m_Array.Add(0.4);
//m_Array.Add(0.75);
//m_Array.Add(1.03);
//m_Array.Add(1.25);
//m_Array.Add(1.68);
//m_Array.Add(2.06);
//m_Array.Add(2.39);
//m_Array.Add(2.65);
//m_Array.Add(2.81);
//m_Array.Add(3.04);
//m_Array.Add(3.23);
//m_Array.Add(3.43);
//m_Array.Add(3.68);
//m_Array.Add(3.99);
//m_Array.Add(4.31);
//m_Array.Add(4.67);
//m_Array.Add(4.92);
//m_Array.Add(5.27);
//m_Array.Add(5.59);
//m_Array.Add(5.77);
//m_Array.Add(6.04);
//m_Array.Add(6.4);
//m_Array.Add(6.81);
//m_Array.Add(7.07);
//m_Array.Add(7.29);
//m_Array.Add(7.53);
//m_Array.Add(7.85);
//m_Array.Add(8.21);
//m_Array.Add(8.48);
//m_Array.Add(8.73);
//m_Array.Add(9);
//m_Array.Add(9.32);
//m_Array.Add(9.61);
//m_Array.Add(9.87);
//m_Array.Add(10.25);
//m_Array.Add(10.59);
//m_Array.Add(10.95);
//m_Array.Add(11.31);
//m_Array.Add(11.62);
//m_Array.Add(11.99);
//m_Array.Add(12.18);
//m_Array.Add(12.36);
//m_Array.Add(12.6);
//m_Array.Add(12.9);
//m_Array.Add(13.16);
//m_Array.Add(13.45);
//m_Array.Add(13.67);
//m_Array.Add(13.89);
//m_Array.Add(14.21);
//m_Array.Add(14.57);
//m_Array.Add(14.88);
//m_Array.Add(15.14);
//m_Array.Add(15.49);
//m_Array.Add(15.79);
//m_Array.Add(16.1);
//m_Array.Add(16.43);
//m_Array.Add(16.69);
//m_Array.Add(16.98);
//m_Array.Add(17.24);
//m_Array.Add(17.58);
//m_Array.Add(17.86);
//m_Array.Add(18.12);
//m_Array.Add(18.39);
//m_Array.Add(18.72);
//m_Array.Add(18.98);
//m_Array.Add(19.24);
//m_Array.Add(19.55);
//m_Array.Add(19.79);
//m_Array.Add(20.09);
//m_Array.Add(20.39);
//m_Array.Add(20.66);
//m_Array.Add(20.94);
//m_Array.Add(21.15);
//m_Array.Add(21.47);
//m_Array.Add(21.78);
//m_Array.Add(22.33);
//m_Array.Add(22.53);
//m_Array.Add(22.75);
//m_Array.Add(23.04);
//m_Array.Add(23.34);
//m_Array.Add(23.6);
//m_Array.Add(23.83);
//m_Array.Add(24.15);
//m_Array.Add(24.42);
//m_Array.Add(24.71);
//m_Array.Add(25.06);
//m_Array.Add(25.37);
//m_Array.Add(25.69);
//m_Array.Add(25.9);
//m_Array.Add(26.1);
//m_Array.Add(26.85);
//m_Array.Add(27.07);
//m_Array.Add(27.28);
//m_Array.Add(27.49);
//m_Array.Add(27.71);
//m_Array.Add(28);
//m_Array.Add(28.25);
//m_Array.Add(28.53);
//m_Array.Add(28.82);
//m_Array.Add(29.08);
//m_Array.Add(29.36);
//m_Array.Add(29.59);
//m_Array.Add(29.85);
//m_Array.Add(30.12);
//m_Array.Add(30.34);
//m_Array.Add(30.61);
//m_Array.Add(30.88);
//m_Array.Add(31.13);
//m_Array.Add(31.4);
//m_Array.Add(31.7);
//m_Array.Add(32.02);
//m_Array.Add(32.31);
//m_Array.Add(32.56);
//m_Array.Add(32.87);
//m_Array.Add(33.19);
//m_Array.Add(33.49);
//m_Array.Add(33.77);
//m_Array.Add(34.04);
//m_Array.Add(34.29);
//m_Array.Add(34.59);
//m_Array.Add(34.87);
//m_Array.Add(35.16);
//m_Array.Add(35.5);
//m_Array.Add(35.86);
//m_Array.Add(36.16);
//m_Array.Add(36.41);
//m_Array.Add(36.74);
//m_Array.Add(37.04);
//m_Array.Add(37.3);
//m_Array.Add(37.55);
//m_Array.Add(37.83);
//m_Array.Add(38.06);
//m_Array.Add(38.35);
//m_Array.Add(38.62);
//m_Array.Add(38.9);
//m_Array.Add(39.2);
//m_Array.Add(39.47);
//m_Array.Add(39.77);
//m_Array.Add(40.11);
//m_Array.Add(40.47);
//m_Array.Add(40.8);
//m_Array.Add(41.01);
//m_Array.Add(37.65);
//m_Array.Add(38.28);
//m_Array.Add(38.94);
//m_Array.Add(39.66);
//m_Array.Add(40.34);
//m_Array.Add(40.9);
//m_Array.Add(41.44);
//m_Array.Add(42.06);
//m_Array.Add(42.66);
//m_Array.Add(43.26);
//m_Array.Add(43.71);
//m_Array.Add(44.25);
//m_Array.Add(44.71);
//m_Array.Add(45.33);
//m_Array.Add(45.8);
//m_Array.Add(46.28);
//m_Array.Add(46.81);
//m_Array.Add(47.14);
//m_Array.Add(47.38);
//m_Array.Add(47.6);
//m_Array.Add(47.77);
//m_Array.Add(47.89);
//m_Array.Add(48.07);
//m_Array.Add(48.2);
//m_Array.Add(48.34);
//m_Array.Add(48.51);
//m_Array.Add(48.65);
//m_Array.Add(48.77);
//m_Array.Add(48.92);
//m_Array.Add(49.09);
//m_Array.Add(49.21);
//m_Array.Add(49.31);
//m_Array.Add(49.41);
//m_Array.Add(49.54);
//m_Array.Add(49.66);
//m_Array.Add(49.75);
//m_Array.Add(49.88);
//m_Array.Add(49.98);
//m_Array.Add(50.11);
//m_Array.Add(50.2);
//m_Array.Add(50.32);
//m_Array.Add(50.45);
//m_Array.Add(50.57);
//m_Array.Add(50.68);
//m_Array.Add(50.78);
//m_Array.Add(50.89);
//m_Array.Add(50.97);
//m_Array.Add(51.06);
//m_Array.Add(51.16);
//m_Array.Add(51.28);
//m_Array.Add(51.37);
//m_Array.Add(51.47);
//m_Array.Add(51.55);
//m_Array.Add(51.64);
//m_Array.Add(51.74);
//m_Array.Add(51.83);
//m_Array.Add(51.95);
//m_Array.Add(52.05);
//m_Array.Add(52.15);
//m_Array.Add(52.22);
//m_Array.Add(52.3);
//m_Array.Add(52.36);
//m_Array.Add(52.44);
//m_Array.Add(52.5);
//m_Array.Add(52.57);
//m_Array.Add(52.6);
//m_Array.Add(52.68);
//m_Array.Add(52.75);
//m_Array.Add(52.85);
//m_Array.Add(52.91);
//m_Array.Add(53.02);
//m_Array.Add(53.11);
//m_Array.Add(53.17);
//m_Array.Add(53.25);
//m_Array.Add(53.33);
//m_Array.Add(53.44);
//m_Array.Add(53.5);
//m_Array.Add(53.58);
//m_Array.Add(53.69);
//m_Array.Add(53.75);
//m_Array.Add(53.79);
//m_Array.Add(53.84);
//m_Array.Add(53.96);
//m_Array.Add(54.07);
//m_Array.Add(54.13);
//m_Array.Add(54.18);
//m_Array.Add(54.21);
//m_Array.Add(54.24);
//m_Array.Add(54.31);
//m_Array.Add(54.37);
//m_Array.Add(54.41);
//m_Array.Add(54.45);
//m_Array.Add(54.56);
//m_Array.Add(54.56);
//m_Array.Add(54.58);
//m_Array.Add(54.63);
//m_Array.Add(54.62);
//m_Array.Add(54.66);
//m_Array.Add(54.72);
//m_Array.Add(54.73);
//m_Array.Add(54.77);
//m_Array.Add(54.78);
//m_Array.Add(54.78);
//m_Array.Add(54.85);
//m_Array.Add(54.85);
//m_Array.Add(54.89);
//m_Array.Add(54.92);
//m_Array.Add(54.89);
//m_Array.Add(54.91);
//m_Array.Add(54.89);
//m_Array.Add(54.91);
//m_Array.Add(54.92);
//m_Array.Add(54.91);
//m_Array.Add(54.92);
//m_Array.Add(54.91);
//m_Array.Add(54.91);
//m_Array.Add(54.93);
//m_Array.Add(54.98);
//m_Array.Add(54.99);
//m_Array.Add(54.97);
//m_Array.Add(54.92);
//m_Array.Add(54.92);
//m_Array.Add(54.88);
//m_Array.Add(54.8);
//m_Array.Add(54.74);
//m_Array.Add(54.64);
//m_Array.Add(54.55);
//m_Array.Add(54.48);
//m_Array.Add(54.36);
//m_Array.Add(54.24);
//m_Array.Add(54.16);
//m_Array.Add(54.08);
//m_Array.Add(53.93);
//m_Array.Add(53.79);
//m_Array.Add(53.62);
//m_Array.Add(53.47);
//m_Array.Add(53.35);
//m_Array.Add(53.17);
//m_Array.Add(52.95);
//m_Array.Add(52.75);
//m_Array.Add(52.55);
//m_Array.Add(52.28);
//m_Array.Add(52.08);
//m_Array.Add(51.82);
//m_Array.Add(51.55);
//m_Array.Add(51.18);
//m_Array.Add(50.93);
//m_Array.Add(50.64);
//m_Array.Add(50.29);
//m_Array.Add(41.73);
//m_Array.Add(42.3);
//m_Array.Add(42.84);
//m_Array.Add(43.64);
//m_Array.Add(44.41);
//m_Array.Add(45.22);
//m_Array.Add(46.03);
//m_Array.Add(46.77);
//m_Array.Add(47.68);
//m_Array.Add(48.45);
//m_Array.Add(49.21);
//m_Array.Add(50.12);
//m_Array.Add(50.93);
//m_Array.Add(51.62);
//m_Array.Add(52.37);
//m_Array.Add(53.23);
//m_Array.Add(53.93);
//m_Array.Add(54.73);
//m_Array.Add(55.55);
//m_Array.Add(56.34);
//m_Array.Add(57.2);
//m_Array.Add(57.95);
//m_Array.Add(58.83);
//m_Array.Add(59.55);
//m_Array.Add(60.47);
//m_Array.Add(61.29);
//m_Array.Add(62.1);
//m_Array.Add(62.94);
//m_Array.Add(-327.67);
//m_Array.Add(-327.67);
//m_Array.Add(-327.67);
//m_Array.Add(-327.67);
//m_Array.Add(-327.67);
//m_Array.Add(-327.67);
//m_Array.Add(-327.67);
//m_Array.Add(-327.67);
//m_Array.Add(-327.67);
//m_Array.Add(-327.67);
m_Array.Add(-327.67);
m_Array.Add(-327.67);
m_Array.Add(-327.67);
m_Array.Add(-327.67);
m_Array.Add(-327.67);
m_Array.Add(-327.67);
m_Array.Add(-327.67);
m_Array.Add(-327.67);
m_Array.Add(-327.67);
m_Array.Add(-327.67);
m_Array.Add(-327.67);
m_Array.Add(-327.67);
m_Array.Add(-327.67);
m_Array.Add(-327.67);
m_Array.Add(-327.67);
m_Array.Add(-327.67);
m_Array.Add(-327.67);
m_Array.Add(-327.67);
m_Array.Add(-327.67);
m_Array.Add(-327.67);
m_Array.Add(-327.67);
m_Array.Add(-327.67);
m_Array.Add(-327.67);
m_Array.Add(-327.67);
m_Array.Add(-327.67);
m_Array.Add(-327.67);
m_Array.Add(-327.67);
m_Array.Add(-327.67);
m_Array.Add(-327.67);
m_Array.Add(-327.67);
m_Array.Add(-327.67);
m_Array.Add(-327.67);
m_Array.Add(-73.76);
m_Array.Add(-72.78);
m_Array.Add(-72.71);
m_Array.Add(-71.8);
m_Array.Add(-70.99);
m_Array.Add(-70);
m_Array.Add(-69.26);
m_Array.Add(-68.6);
m_Array.Add(-67.95);
m_Array.Add(-67.3);
m_Array.Add(-66.27);
m_Array.Add(-65.32);
m_Array.Add(-64.59);
m_Array.Add(-63.77);
m_Array.Add(-62.96);
m_Array.Add(-62.26);
m_Array.Add(-61.4);
m_Array.Add(-60.49);
m_Array.Add(-59.58);
m_Array.Add(-58.98);
m_Array.Add(-58.17);
m_Array.Add(-57.42);
m_Array.Add(-56.64);
m_Array.Add(-56.01);
m_Array.Add(-55.25);
m_Array.Add(-54.36);
m_Array.Add(-53.5);
m_Array.Add(-52.82);
m_Array.Add(-51.96);
m_Array.Add(-51.13);
m_Array.Add(-50.31);
m_Array.Add(-49.64);
m_Array.Add(-48.73);
m_Array.Add(-47.95);
m_Array.Add(-47.3);
m_Array.Add(-46.58);
m_Array.Add(-45.77);
m_Array.Add(-45.1);
m_Array.Add(-44.4);
m_Array.Add(-43.53);
m_Array.Add(-42.83);
m_Array.Add(-42.07);
m_Array.Add(-41.36);
m_Array.Add(-40.52);
m_Array.Add(-39.78);
m_Array.Add(-39.08);
m_Array.Add(-38.41);
m_Array.Add(-37.55);
m_Array.Add(-36.61);
m_Array.Add(-35.83);
m_Array.Add(-35.11);
m_Array.Add(-34.42);
m_Array.Add(-33.55);
m_Array.Add(-32.86);
m_Array.Add(-32.16);
m_Array.Add(-31.51);
m_Array.Add(-30.81);
m_Array.Add(-30.03);
m_Array.Add(-29.21);
m_Array.Add(-28.26);
m_Array.Add(-27.29);
m_Array.Add(-26.37);
m_Array.Add(-26.04);
m_Array.Add(-25.99);
m_Array.Add(-25.94);
m_Array.Add(-25.93);
m_Array.Add(-25.95);
m_Array.Add(-26.01);
m_Array.Add(-26.03);
m_Array.Add(-26.01);
m_Array.Add(-25.99);
m_Array.Add(-25.98);
m_Array.Add(-25.94);
m_Array.Add(-25.83);
m_Array.Add(-25.75);
m_Array.Add(-25.66);
m_Array.Add(-25.55);
m_Array.Add(-25.41);
m_Array.Add(-25.28);
m_Array.Add(-25.16);
m_Array.Add(-25.01);
m_Array.Add(-24.85);
m_Array.Add(-24.69);
m_Array.Add(-24.5);
m_Array.Add(-24.29);
m_Array.Add(-24.15);
m_Array.Add(-23.96);
m_Array.Add(-23.68);
m_Array.Add(-23.49);
m_Array.Add(-23.24);
m_Array.Add(-22.98);
m_Array.Add(-22.68);
m_Array.Add(-22.39);
m_Array.Add(-22.12);
m_Array.Add(-21.82);
m_Array.Add(-21.54);
m_Array.Add(-21.22);
m_Array.Add(-20.84);
m_Array.Add(-20.48);
m_Array.Add(-20.11);
m_Array.Add(-19.68);
m_Array.Add(-19.35);
m_Array.Add(-18.98);
m_Array.Add(-18.58);
m_Array.Add(-18.19);
m_Array.Add(-17.75);
m_Array.Add(-17.45);
m_Array.Add(-16.98);
m_Array.Add(-16.54);
m_Array.Add(-16.04);
m_Array.Add(-15.64);
m_Array.Add(-15.12);
m_Array.Add(-14.6);
m_Array.Add(-14.27);
m_Array.Add(-13.84);
m_Array.Add(-13.32);
m_Array.Add(-12.77);
m_Array.Add(-12.25);
m_Array.Add(-11.7);
m_Array.Add(-11.12);
m_Array.Add(-10.57);
m_Array.Add(-10.13);
m_Array.Add(-9.69);
m_Array.Add(-9.13);
m_Array.Add(-8.51);
m_Array.Add(-7.86);
m_Array.Add(-7.27);
m_Array.Add(-6.64);
m_Array.Add(-6.04);
m_Array.Add(-5.41);
m_Array.Add(-4.87);
m_Array.Add(-4.25);
m_Array.Add(-3.63);
m_Array.Add(-3.09);
m_Array.Add(-2.46);
m_Array.Add(-1.78);
m_Array.Add(-1.21);
m_Array.Add(-0.65);
m_Array.Add(-0.1);
m_Array.Add(0.37);
m_Array.Add(0.92);
m_Array.Add(1.65);
m_Array.Add(2.25);
m_Array.Add(2.83);
m_Array.Add(3.43);
m_Array.Add(4.04);
m_Array.Add(4.6	);
m_Array.Add(5.07);
m_Array.Add(5.74);
m_Array.Add(6.29);
m_Array.Add(6.85);
m_Array.Add(7.43);
m_Array.Add(8.1	);
m_Array.Add(8.84);
m_Array.Add(9.32);
m_Array.Add(9.91);
m_Array.Add(10.46);
m_Array.Add(11.1);
m_Array.Add(11.76);
m_Array.Add(12.3);
m_Array.Add(12.87);
m_Array.Add(13.37);
m_Array.Add(13.79);
m_Array.Add(14.29);
m_Array.Add(14.7);
m_Array.Add(15.05);
m_Array.Add(15.41);
m_Array.Add(15.78);
m_Array.Add(16.18);
m_Array.Add(16.57);
m_Array.Add(16.92);
m_Array.Add(17.3);
m_Array.Add(17.64);
m_Array.Add(18.03);
m_Array.Add(18.36);
m_Array.Add(18.69);
m_Array.Add(18.97);
m_Array.Add(19.24);
m_Array.Add(19.5);
m_Array.Add(19.22);
m_Array.Add(18.74);
m_Array.Add(18.3);
m_Array.Add(18.63);
m_Array.Add(19.23);
m_Array.Add(19.88);
m_Array.Add(20.47);
m_Array.Add(20.96);
m_Array.Add(21.58);
m_Array.Add(22.2);
m_Array.Add(22.87);
m_Array.Add(23.41);
m_Array.Add(23.86);
m_Array.Add(24.36);
m_Array.Add(24.85);
m_Array.Add(25.28);
m_Array.Add(25.71);
m_Array.Add(26.14);
m_Array.Add(26.52);
m_Array.Add(26.91);
m_Array.Add(27.31);
m_Array.Add(27.7);
m_Array.Add(28.12);
m_Array.Add(28.46);
m_Array.Add(28.81);
m_Array.Add(29.14);
m_Array.Add(29.47);
m_Array.Add(29.79);
m_Array.Add(30.04);
m_Array.Add(30.34);
m_Array.Add(30.62);
m_Array.Add(30.84);
m_Array.Add(31.09);
m_Array.Add(31.28);
m_Array.Add(31.45);
m_Array.Add(31.65);
m_Array.Add(31.85);
m_Array.Add(32.05);
m_Array.Add(32.22);
m_Array.Add(32.36);
m_Array.Add(32.54);
m_Array.Add(32.75);
m_Array.Add(32.92);
m_Array.Add(33.04);
m_Array.Add(33.18);
m_Array.Add(33.32);
m_Array.Add(33.48);
m_Array.Add(33.59);
m_Array.Add(33.73);
m_Array.Add(33.84);
m_Array.Add(33.94);
m_Array.Add(34.06);
m_Array.Add(34.17);
m_Array.Add(34.3);
m_Array.Add(34.43);
m_Array.Add(34.49);
m_Array.Add(34.61);
m_Array.Add(34.76);
m_Array.Add(34.86);
m_Array.Add(34.95);
m_Array.Add(35.03);
m_Array.Add(35.15);
m_Array.Add(35.24);
m_Array.Add(35.31);
m_Array.Add(35.36);
m_Array.Add(35.4);
m_Array.Add(35.46);
m_Array.Add(35.55);
m_Array.Add(35.62);
m_Array.Add(35.66);
m_Array.Add(35.73);
m_Array.Add(35.78);
m_Array.Add(35.85);
m_Array.Add(35.89);
m_Array.Add(35.93);
m_Array.Add(35.94);
m_Array.Add(35.98);
m_Array.Add(36.04);
m_Array.Add(36.07);
m_Array.Add(36.1);
m_Array.Add(36.16);
m_Array.Add(36.17);
m_Array.Add(36.23);
m_Array.Add(36.26);
m_Array.Add(36.29);
m_Array.Add(36.29);
m_Array.Add(36.33);
m_Array.Add(36.37);
m_Array.Add(36.4);
m_Array.Add(36.43);
m_Array.Add(36.48);
m_Array.Add(36.41);
m_Array.Add(36.41);
m_Array.Add(36.41);
m_Array.Add(36.46);
m_Array.Add(36.44);
m_Array.Add(36.5);
m_Array.Add(36.51);
m_Array.Add(36.5);
m_Array.Add(36.53);
m_Array.Add(36.5);
m_Array.Add(36.51);
m_Array.Add(36.55);
m_Array.Add(36.55);
m_Array.Add(36.52);
m_Array.Add(36.56);
m_Array.Add(36.56);
m_Array.Add(36.54);
m_Array.Add(36.54);
m_Array.Add(36.55);
m_Array.Add(36.52);
m_Array.Add(36.49);
m_Array.Add(36.51);
m_Array.Add(36.52);
m_Array.Add(36.48);
m_Array.Add(36.46);
m_Array.Add(36.47);
m_Array.Add(36.47);
m_Array.Add(36.48);
m_Array.Add(36.45);
m_Array.Add(36.46);
m_Array.Add(36.43);
m_Array.Add(36.36);
m_Array.Add(36.36);
m_Array.Add(36.39);
m_Array.Add(36.37);
m_Array.Add(36.27);
m_Array.Add(36.26);
m_Array.Add(36.21);
m_Array.Add(36.11);
m_Array.Add(36.08);
m_Array.Add(36.03);
m_Array.Add(36.01);
m_Array.Add(36.07);
m_Array.Add(36.02);
m_Array.Add(35.93);
m_Array.Add(35.95);
m_Array.Add(36	);
m_Array.Add(35.82);
m_Array.Add(35.59);
m_Array.Add(35.51);
m_Array.Add(35.34);
m_Array.Add(35.07);
m_Array.Add(34.85);
m_Array.Add(34.66);
m_Array.Add(34.38);
m_Array.Add(34.13);
m_Array.Add(33.84);
m_Array.Add(33.6);
m_Array.Add(33.16);
m_Array.Add(32.25);
m_Array.Add(23.87);
m_Array.Add(24.42);
m_Array.Add(24.97);
m_Array.Add(25.79);
m_Array.Add(26.54);
m_Array.Add(27.28);
m_Array.Add(28.08);
m_Array.Add(28.86);
m_Array.Add(29.53);
m_Array.Add(30.28);
m_Array.Add(31.02);
m_Array.Add(31.73);
m_Array.Add(32.52);
m_Array.Add(33.24);
m_Array.Add(34);
m_Array.Add(34.79);
m_Array.Add(35.52);
m_Array.Add(36.34);
m_Array.Add(37.08);
m_Array.Add(37.93);
m_Array.Add(38.7);
m_Array.Add(39.39);
m_Array.Add(40.19);
m_Array.Add(40.95);
m_Array.Add(41.65);
m_Array.Add(42.39);
m_Array.Add(43.18);
m_Array.Add(43.89);
m_Array.Add(44.65);
m_Array.Add(45.39);
m_Array.Add(46.15);
m_Array.Add(46.96);
m_Array.Add(47.7);
m_Array.Add(48.37);
m_Array.Add(49.13);
m_Array.Add(50.09);
m_Array.Add(50.83);
m_Array.Add(51.56);
m_Array.Add(52.38);
m_Array.Add(53.18);
m_Array.Add(53.89);
m_Array.Add(54.6);
m_Array.Add(55.44);
m_Array.Add(56.13);
m_Array.Add(56.92);
m_Array.Add(57.69);
m_Array.Add(58.43);
m_Array.Add(59.25);
m_Array.Add(59.97);
m_Array.Add(60.84);
m_Array.Add(61.56);
m_Array.Add(62.49);
m_Array.Add(63.26);
m_Array.Add(-327.67);
m_Array.Add(-327.67);
m_Array.Add(-327.67);
m_Array.Add(-327.67);
m_Array.Add(-327.67);
m_Array.Add(-327.67);
m_Array.Add(-327.67);
m_Array.Add(-327.67);
m_Array.Add(-327.67);
m_Array.Add(-327.67);
m_Array.Add(-327.67);
m_Array.Add(-327.67);

int s1,s2,s3;
//GetStandardPos(&m_Array,&s1,&s2,&s3);
GetStandardPos(&m_Array,&s1,&s2);
		theApp.AppPosStart= s1;
		theApp.AppPosFinish=s2; 

		double v1,v2;
		v2=GetMaxValue(&m_Array,s1,s2);
		v1=GetMaxValue(&m_Array,s1-150,s1);

	if(::GetFileAttributes(_T("\\Ӳ��\\parameter.txt")) != 0xFFFFFFFF)
		::CopyFile(_T("\\Ӳ��\\parameter.txt"),_T("\\ResidentFlash2\\GUI\\parameter.txt"),false);
	if(::GetFileAttributes(_T("\\Ӳ��\\standard.txt")) != 0xFFFFFFFF)
		::CopyFile(_T("\\Ӳ��\\standard.txt"),_T("\\ResidentFlash2\\GUI\\standard.txt"),false);

	FileRead(_T("\\ResidentFlash2\\GUI\\parameter.txt"),&theApp.AppParameterContent);
	FileRead(_T("\\ResidentFlash2\\GUI\\standard.txt"),&theApp.AppStandardContent);

	//SetTimer(1,20,NULL);

	if (m_pSerial != NULL)
	{
		m_pSerial->ClosePort();

		delete m_pSerial;
		m_pSerial = NULL;
	}
	API_GPIO_Output(0, 0);
	API_GPIO_Output(1, 0);
	API_GPIO_Output(2, 0);
	API_GPIO_Output(3, 1);

	//�½�����ͨѶ����
	m_pSerial = new CCESeries();
	//m_pSerial->m_OnSeriesRead = OnSerialRead;

	//�򿪴���  9600
	if(m_pSerial->OpenPort(this,3,115200,0,8,0,0))
	{
		//AfxMessageBox(L"���ڴ򿪳ɹ�");
		Sleep(200);
	}
	else
	{
		AfxMessageBox(L"���ڴ�ʧ��");
	}
	
	m_hThread = CreateThread(NULL,0,ThreadFunc,this,0,&m_dwThreadID);
	

	pWnd   =   GetDlgItem(IDC_STC_IMAGE);     
	RECT   rect;  
	pWnd->GetClientRect(&rect);  
	CDC   *pDC   =   pWnd->GetDC();  
	int nWidth=rect.right;
	int nHeight=rect.bottom ;

	//���������Ļ��ʾ���ݵ��ڴ���ʾ�豸
MemDC.CreateCompatibleDC(NULL);
//��ʱ�����ܻ�ͼ����Ϊû�еط��� ^_^
//���潨��һ������Ļ��ʾ���ݵ�λͼ������λͼ�Ĵ�С������ô��ڵĴ�С
//MemBitmap.CreateCompatibleBitmap(pDC,nWidth,nHeight);
MemBitmap.CreateBitmap(nWidth*10,nHeight*10,1,16,NULL);
//MemBitmap.CreateBitmap(nWidth,nHeight,1,16,NULL);
//��λͼѡ�뵽�ڴ���ʾ�豸��
//ֻ��ѡ����λͼ���ڴ���ʾ�豸���еط���ͼ������ָ����λͼ��
pOldBit=MemDC.SelectObject(&MemBitmap);
//���ñ���ɫ��λͼ����ɾ����������õ��ǰ�ɫ��Ϊ����
//��Ҳ�������Լ�Ӧ���õ���ɫ
MemDC.FillSolidRect(0,0,nWidth*10,nHeight*10,RGB(255,255,255));

srand(GetTickCount());

	int iFullWidth = GetSystemMetrics(SM_CXSCREEN);
	int iFullHeight = GetSystemMetrics(SM_CYSCREEN); 
	::SetWindowPos(this->m_hWnd, HWND_TOPMOST, 0, 0, iFullWidth, iFullHeight, SWP_NOOWNERZORDER|SWP_SHOWWINDOW);

	::SetCursorPos(iFullHeight,iFullWidth);
	ShowCursor(FALSE);

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


void CReduceMeasurementDlg::OnBnClickedButExit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//m_Array.RemoveAll();  //ɾ������Ԫ��

	////m_hThread = CreateThread(NULL,0,ThreadFunc,this,0,&m_dwThreadID);

	//RunFlag=true;
	//m_DIR=0;
	//API_GPIO_Output(1,m_DIR);
	////SetTimer(1,100,NULL);
	//API_GPIO_Output(2, 1);
	//iNUM=0;

	//	CReduceMessageDlg dlg;
	////m_pMainWnd = &dlg;
	//INT_PTR nResponse = dlg.DoModal();
	//if (nResponse == IDOK)
	//{
	//	// TODO: �ڴ˷��ô����ʱ��
	//	//  ��ȷ�������رնԻ���Ĵ���
	//}


	CloseThread();
	this->OnOK();
	//this->OnDestroy(); 
}

void CReduceMeasurementDlg::OnBnClickedButSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CWnd   *pWnd   =   GetDlgItem(IDC_STC_IMAGE);     
	//RECT   rect;  
	//pWnd->GetClientRect(&rect);  
	//CDC   *pControlDC   =   pWnd->GetDC();  
	//pWnd->Invalidate();  
	//pWnd->UpdateWindow();  

	//pControlDC->SelectStockObject(WHITE_BRUSH);  
	//pControlDC->Rectangle(&rect);  
	//pControlDC->SelectStockObject(BLACK_BRUSH);  
	//pControlDC->MoveTo(0 ,rect.bottom/4); 
	//pControlDC->LineTo(rect.right ,rect.bottom/4);

	//pControlDC->MoveTo(rect.right/2  ,0); 
	//pControlDC->LineTo(rect.right/2 ,rect.bottom);
	 if(MessageBox(_T("�Ƿ�Ҫ���汾�����ݣ�"),_T("����"),MB_YESNO||MB_ICONQUESTION)==IDYES)
	 {
	CString m_Temp,m_Tmp=_T("");
	wchar_t   *stopstring;
	if(theApp.AppFilePath.Compare(_T(""))!=0)
	{
		//this->MessageBoxW(L"SSS");
			
			if(::GetFileAttributes(theApp.AppFilePath) == 0xFFFFFFFF){
				m_Temp=_T("λ�ñ�ʶ\t������\t����λ��(m)\t��׼ֵ(mm)\t����ֵ(mm)\t��ֵ(mm)\r\n");
			}
			else{
				m_Temp=_T("");
			}
			//		λ�ñ�ʶ			������			����λ��			��׼ֵ				����ֵ				��ֵ
			m_Tmp.Format(_T("%f"),wcstod(theApp.AppMeasurementVal,&stopstring)-wcstod(theApp.AppStandardVal,&stopstring));
			m_Temp+=theApp.AppIdentification +_T("\t")+theApp.AppTurnoutNumber +_T("\t")+theApp.AppMeasurementPos +_T("\t")+theApp.AppStandardVal +_T("\t")+theApp.AppMeasurementVal +_T("\t")+m_Tmp+_T("\r\n");
			//FileWrite(_T("\\ResidentFlash2\\GUI\\") +strDate +_T(".txt"),m_Temp);
			FileWrite(theApp.AppFilePath,m_Temp);
	}

	 }
	//double data;
	//data=GetValue();
	//CString str;
	//str.Format(L"%lf\n",data);
	////plist->AddString((LPCTSTR)str); 
	//TRACE(_T("%s"),str);
	//BYTE buf[]={0x02,0x43,0xB0,0x01,0x03,0xF2};
	//BYTE *revbuf=NULL;
	//DWORD revlen=0;
	//DWORD errlen=0;
	//double data=0.0;
	//revbuf=m_pSerial->Command((BYTE*)buf,sizeof(buf),&revlen);
	//if(revbuf[0] == 0x02&&revbuf[1] == 0x06&&revbuf[4] == 0x03)
	//	data=revbuf[2]*256+revbuf[3];
}

void CReduceMeasurementDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
	//CString str;
	//str.Format(_T("����ֵ��\n%d\n��������\n%d"),(int)m_Array.GetSize(),m_SendCout); 
	//GetDlgItem(IDC_STC_CONTENT)->SetWindowTextW(str);

	double x,y;
	CString str;
	CWnd   *pWnd   =   GetDlgItem(IDC_STC_IMAGE);     
	RECT   rect;  
	pWnd->GetClientRect(&rect);  
	CDC   *pDC   =   pWnd->GetDC();  
	pWnd->UpdateWindow();  
	int nWidth=rect.right;
	int nHeight=rect.bottom ;
	int px,py;
	px=GetDeviceCaps(pDC->m_hDC,LOGPIXELSX);
	py=GetDeviceCaps(pDC->m_hDC,LOGPIXELSY);
	//pWnd->Invalidate();  
	
//CDC MemDC; //���ȶ���һ����ʾ�豸����
//CBitmap MemBitmap;//����һ��λͼ����
////���������Ļ��ʾ���ݵ��ڴ���ʾ�豸
//MemDC.CreateCompatibleDC(NULL);
////��ʱ�����ܻ�ͼ����Ϊû�еط��� ^_^
////���潨��һ������Ļ��ʾ���ݵ�λͼ������λͼ�Ĵ�С������ô��ڵĴ�С
//MemBitmap.CreateCompatibleBitmap(pDC,nWidth,nHeight);
////��λͼѡ�뵽�ڴ���ʾ�豸��
////ֻ��ѡ����λͼ���ڴ���ʾ�豸���еط���ͼ������ָ����λͼ��
//CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);
////���ñ���ɫ��λͼ����ɾ����������õ��ǰ�ɫ��Ϊ����
////��Ҳ�������Լ�Ӧ���õ���ɫ
//MemDC.FillSolidRect(0,0,nWidth,nHeight,RGB(255,255,255));
////��ͼ
//MemDC.MoveTo(0 ,nHeight/4); 
//MemDC.LineTo(nWidth ,nHeight/4);
////���ڴ��е�ͼ��������Ļ�Ͻ�����ʾ
//pDC->BitBlt(0,0,nWidth,nHeight,&MemDC,0,0,SRCCOPY);
////��ͼ��ɺ������
//MemBitmap.DeleteObject(); 
//MemDC.SelectObject(pOldBit);
//MemDC.DeleteDC();

//		//��ͼ
//MemDC.MoveTo(0 ,nHeight/4); 
//MemDC.LineTo(nWidth ,nHeight/4);
//MemDC.MoveTo(0 ,0); 
//for(int i=0;i<100;i++)
//{
//MemDC.LineTo(i*2 ,rand()%50);
//}
////���ڴ��е�ͼ��������Ļ�Ͻ�����ʾ
//pDC->BitBlt(0,0,nWidth,nHeight,&MemDC,0,0,SRCCOPY);
////pDC->StretchBlt(0,0,nWidth,nHeight,&MemDC,0,0,nWidth,nHeight,SRCCOPY);


////	PAINTSTRUCT paintStruct;
////    pWnd->BeginPaint(&paintStruct);
////
////	CDC dcMem;                                                  //���ڻ�����ͼ���ڴ�DC
////	CBitmap bmp;                                                 //�ڴ��г�����ʱͼ���λͼ
////	dcMem.CreateCompatibleDC(pDC);               //��������DC���������ڴ�DC
////	bmp.CreateCompatibleBitmap(&dcMem,rect.right*1000,rect.bottom*1000);//��������λͼ
////	dcMem.SelectObject(&bmp);                          //��λͼѡ����ڴ�DC
////	dcMem.FillSolidRect(&rect,pDC->GetBkColor());//��ԭ���������ͻ�������Ȼ���Ǻ�ɫ
////	//for(int i=20;i>0;i--)                                          //���ڴ�DC����ͬ����ͬ��Բͼ��
////	//{
////	//	ellipseRect.SetRect(ptCenter,ptCenter);
////	//	ellipseRect.InflateRect(i*10,i*10);
////	//	dcMem.Ellipse(ellipseRect);
////	//}
////	dcMem.MoveTo(0 ,rect.bottom*1000/4); 
////	dcMem.LineTo(rect.right*1000 ,rect.bottom*1000/4);
////
////	dcMem.MoveTo(rect.right*1000/2  ,0); 
////	dcMem.LineTo(rect.right*1000/2 ,rect.bottom*1000);
////	CBrush brush,*oldbrush;
////	brush.CreateSolidBrush(RGB(255,0,0));
////	oldbrush=dcMem.SelectObject(&brush);
////
////	//pDC->Ellipse(10,10,100,100);
////	//pDC->SetPixel(10,10,RGB(255,0,0)); 
////
////	for(int i=0;i<(int)m_Array.GetSize();i++)
////	{
////		x=i*0.15*1000;y=m_Array.GetAt(i)*1000;
////		dcMem.SetPixel(int(x),int(20.0+y),RGB(255,0,0)); 
////		//x=-50.0+i*0.35;y=m_Data.GetAt(i);
////		//pDC->SetPixel(int(x+rect.right/2),int(rect.bottom/4-y),RGB(255,0,0));//rect.bottom-(pst[0].y/2.5+rect.bottom/4));  
////		//pDC->Ellipse(int((x-r)/2.5+rect.right/2),int(rect.bottom/4-(y-r)/2.5),int((x+r)/2.5+rect.right/2),int(rect.bottom/4-(y+r)/2.5));
////	}
////
////	dcMem.SelectObject(oldbrush);
////
////
////	pDC->BitBlt(0,0,rect.right ,rect.bottom ,&dcMem,0,0,SRCCOPY);//���ڴ�DC�ϵ�ͼ�󿽱���ǰ̨
////	dcMem.DeleteDC();                                       //ɾ��DC
////	bmp.DeleteObject();                                        //ɾ��λͼ
////	pWnd->ReleaseDC(pDC); 
////
////pWnd->EndPaint(&paintStruct);

	pDC->SelectStockObject(WHITE_BRUSH);  
	pDC->Rectangle(&rect);  
	pDC->SelectStockObject(BLACK_BRUSH);  
	pDC->MoveTo(0 ,rect.bottom/4); 
	pDC->LineTo(rect.right ,rect.bottom/4);

	pDC->MoveTo(rect.right/2  ,0); 
	pDC->LineTo(rect.right/2 ,rect.bottom);

	//m_Array
	CBrush brush,*oldbrush;
	brush.CreateSolidBrush(RGB(0,0,0));
	oldbrush=pDC->SelectObject(&brush);

	//pDC->Ellipse(10,10,100,100);
	//pDC->SetPixel(10,10,RGB(255,0,0)); 

	//if(theApp.AppPosStart>0&&theApp.AppPosFinish>0)
	//{
	//	//this->MessageBoxW(L"eee");
	//	TRACE(_T("%d__%d"),theApp.AppPosStart,theApp.AppPosFinish);
	//	for(int i=theApp.AppPosStart ;i<theApp.AppPosFinish;i++)
	//	{
	//	//x=i*sin(35.0*pi/180.0);y=m_Array.GetAt(i)*cos(35.0*pi/180.0);
	//	//x=i*0.15;y=m_Array.GetAt(i)*cos(35.0*pi/180.0);
	//	//pDC->SetPixel(int(10.0+x),int(20.0+y),RGB(255,0,0)); 
	//	//x=-50.0+i*5.0;y=m_Array.GetAt(i)*5.0;
	//	x=-100.0+i*sin(35.0*pi/180.0);y=m_Array.GetAt(i)*cos(35.0*pi/180.0)+20.0;
	//	if(i==0) pDC->MoveTo((x+rect.right/2),(rect.bottom/2-y));//pDC->MoveTo((x+rect.right/2),(rect.bottom/2-y));
	//	//pDC->SetPixel((x+rect.right/2),(rect.bottom/4-y),RGB(255,0,0));//rect.bottom-(pst[0].y/2.5+rect.bottom/4));  
	//	pDC->LineTo((x+rect.right/2),(rect.bottom/2-y));
	//	//pDC->LineTo((int)x,(int)y);
	//	//pDC->Ellipse(int((x-r)/2.5+rect.right/2),int(rect.bottom/4-(y-r)/2.5),int((x+r)/2.5+rect.right/2),int(rect.bottom/4-(y+r)/2.5));
	//	}
	//}
	//else
	//{
		for(int i=0;i<(int)m_Array.GetSize();i++)
		{
		//x=i*sin(35.0*pi/180.0);y=m_Array.GetAt(i)*cos(35.0*pi/180.0);
		//x=i*0.15;y=m_Array.GetAt(i)*cos(35.0*pi/180.0);
		//pDC->SetPixel(int(10.0+x),int(20.0+y),RGB(255,0,0)); 
		//x=-50.0+i*5.0;y=m_Array.GetAt(i)*5.0;
		x=-80.0+i*sin(35.0*pi/180.0);y=m_Array.GetAt(i)*cos(35.0*pi/180.0)+20.0;
		if(i==0) pDC->MoveTo((x+rect.right/2),(rect.bottom/4-y));
		//pDC->SetPixel((x+rect.right/2),(rect.bottom/4-y),RGB(255,0,0));//rect.bottom-(pst[0].y/2.5+rect.bottom/4));  
		pDC->LineTo((x+rect.right/2),(rect.bottom/4-y));
		//pDC->LineTo((int)x,(int)y);
		//pDC->Ellipse(int((x-r)/2.5+rect.right/2),int(rect.bottom/4-(y-r)/2.5),int((x+r)/2.5+rect.right/2),int(rect.bottom/4-(y+r)/2.5));
		}
	//}
	
	//x=10.0+m_TimerNum*0.35;y=rev/1000.0;
	//pDC->Ellipse(int((x-r)/2.5+rect.right/2),int(rect.bottom/4-(y-r)/2.5),int((x+r)/2.5+rect.right/2),int(rect.bottom/4-(y+r)/2.5));

	//for (int i=0;i<2;i++)  
	//{  
	//    pDC->LineTo(int(pst[i].x/2.5+rect.right/2),int(rect.bottom/4-pst[i].y/2.5));//rect.bottom-(pst[0].y/2.5+rect.bottom/4));  
	//}

	//pDC->DrawText(_T("12.12"), &rect,DT_CENTER|DT_VCENTER);
	//DrawArc(pDC->m_hDC,100,100,200,200,300); 
	pDC->SelectObject(oldbrush);
	pWnd->ReleaseDC(pDC); 



 //long nWidth=rect.right;
 //long nHigth=rect.bottom;
 //CDC tempdc;//B����
 //CBitmap MemBitmap;//������
 //CBitmap*OldBitmap;//������

 //tempdc.CreateCompatibleDC(pDC); //ʵ�廯B����
 //MemBitmap.CreateCompatibleBitmap(pDC,nWidth,nHigth);//ʵ�廯��Bʹ�õ�����
 ////�����ǿ�����A��λͼ���Լ�����ͼƬҲ�У���Сע����
 //OldBitmap=tempdc.SelectObject(&MemBitmap);
 ////��Bʹ��
 //tempdc.FillSolidRect(0,0,nWidth,nHigth,RGB(0,255,255));
 ////Ĭ�Ϻ�ɫ���Լ�����ı�
 //	tempdc.MoveTo(0 ,rect.bottom/4); 
	//tempdc.LineTo(rect.right ,rect.bottom/4);

	//tempdc.MoveTo(rect.right/2  ,0); 
	//tempdc.LineTo(rect.right/2 ,rect.bottom);
 ////...............
 ////��B�����ϻ�����tempdc
 //pDC->BitBlt(0,0,nWidth,nHigth,&tempdc,0,0,SRCCOPY);
 ////������A
 //tempdc.SelectObject(OldBitmap);
 ////�ָ�Bԭ�е�������ϰ�߰ɣ����������ڴ��ǵ��ͷţ�
 ////ɾ����ʱ����
 //MemBitmap.DeleteObject();
 //tempdc.DeleteDC();

	 // CDC   MemDC;   //���ȶ���һ����ʾ�豸����  
  //CBitmap   MemBitmap;//����һ��λͼ����  
  // 
  ////���������Ļ��ʾ���ݵ��ڴ���ʾ�豸  
  //MemDC.CreateCompatibleDC(NULL);  
  ////��ʱ�����ܻ�ͼ����Ϊû�еط���   ^_^  
  ////���潨��һ������Ļ��ʾ���ݵ�λͼ������λͼ�Ĵ�С������ô��ڵĴ�С  
  //MemBitmap.CreateCompatibleBitmap(pDC,nWidth,nHeight);  
  //   
  ////��λͼѡ�뵽�ڴ���ʾ�豸��  
  ////ֻ��ѡ����λͼ���ڴ���ʾ�豸���еط���ͼ������ָ����λͼ��  
  //CBitmap   *pOldBit=MemDC.SelectObject(&MemBitmap);  
  // 
  ////���ñ���ɫ��λͼ����ɾ����������õ��ǰ�ɫ��Ϊ����  
  ////��Ҳ�������Լ�Ӧ���õ���ɫ  
  //MemDC.FillSolidRect(0,0,nWidth,nHeight,RGB(255,255,255));  
  // 
  ////��ͼ  
  //MemDC.MoveTo(����);  
  //MemDC.LineTo(����);  
  // 
  ////���ڴ��е�ͼ��������Ļ�Ͻ�����ʾ  
  //pDC->BitBlt(0,0,nWidth,nHeight,&MemDC,0,0,SRCCOPY);  
  // 
  ////��ͼ��ɺ������  
  //MemBitmap.DeleteObject();  
  //MemDC.DeleteDC();  
   
}

void CReduceMeasurementDlg::OnStnClickedStcTitle()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������


	intExitFlag++;
	if(intExitFlag>9) this->OnOK();
}
void CReduceMeasurementDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	double data=0.0;
//	CWnd   *pWnd   =  GetDlgItem(IDC_STC_IMAGE);  
//RECT   rect;  
//					pWnd->GetClientRect(&rect);  
//					CDC   *pControlDC   =   pWnd->GetDC();  

	switch(nIDEvent)
	{
	case 1:
	//	//OnPaint();
	//	//intExitFlag=0;

	//	//FlagCount++;
	//	//if(FlagCount==200)
	//	//{
	//	//	//FlagCount=0;
	//	//	m_DIR=m_DIR!=0?0:1;
	//	//	API_GPIO_Output(1, m_DIR);
	//	//	m_Array.RemoveAll();  //ɾ������Ԫ��	
	//	//}
	//	//else if(FlagCount>200&&FlagCount<400)
	//	//{
	//		//data=GetValue();
	//		//m_Array.Add(data);
	//		//double x,y;
	//		
	//		//CListBox *plist=(CListBox*)GetDlgItem(IDC_LIST1);
	//		//CString str;
	//		//str.Format(L"%lf",data);
	//		//plist->AddString((LPCTSTR)str); 
	//		//CWnd   *pWnd   =   ReduceMeasurementDlg->GetDlgItem(IDC_STC_IMAGE);     

	//		//pWnd->Invalidate();  
	//		//pWnd->UpdateWindow();
	//	//	Invalidate();
	//	//}
	//	//else if(FlagCount==400)
	//	//{
	//	//		API_GPIO_Output(2, 0);
	//	//		FlagCount=0;
	//	//		KillTimer(1);
	//	//}
	//		BYTE buf[]={0x02,0x43,0xB0,0x01,0x03,0xF2};
	//BYTE *revbuf=NULL;
	//DWORD revlen=0;
	//DWORD errlen=0;
	//double data=0.0;
	//double temp=0.0;
	//DWORD dwRet;
	//UINT8 Level;
	//CString ss;
	//CString str;
	//int CW=0;
	//bool DropFlag=false;

	//	if(RunFlag)
	//	{
	//		API_GPIO_Input(2,&Level);//��ֹͣ�ź�
	//		if(Level==0)
	//		{       
	//			RunFlag=false;
	//			API_GPIO_Output(2, 0);
	//			CW=0;
	//			str.Format(L"�ɼ�������%d\n",FlagCount);
	//			TRACE(_T("%s"),str);
	//			FlagCount=0;
	//			Invalidate();
	//			//str="";
	//			//for(int i=0;i<(int)m_Array.GetSize();i++)
	//			//{
	//			//	ss.Format(_T("%d:%f;\n"),i,m_Array.GetAt(i));
	//			//	TRACE(_T("%s"),ss);
	//			//	//str.Append(ss);
	//			//}
	//			//str1.append (str2);   //��str2���ӵ�str1��
	//			//TRACE(_T("%s"),str);
	//			TRACE0( "ֹͣ�źš���\n"  );

	//		}
	//		API_GPIO_Input(1,&Level);//�������ź�
	//		if(Level==0)
	//		{
	//			revbuf=m_pSerial->Command((BYTE*)buf,sizeof(buf),&revlen);
	//			Sleep(100);
	//			//CW=CW!=0?0:1;
	//			CW=1;
	//			//API_GPIO_Output(1,CW);
	//			//API_GPIO_Output(1,1);
	//			FlagCount=0;
	//			m_Array.RemoveAll();  //ɾ������Ԫ��
	//			//hDlg->Invalidate();
	//			TRACE0( "�����źš���\n"  );
	//		}
	//		if(CW==1)
	//		{
	//			API_GPIO_Input(0,&Level);//���ɼ��ź�
	//			if(Level==0 && DropFlag==true)
	//			{
	//				DropFlag=false;
	//				//data=rand()%50;

	//				//TRACE0( "Start Dump of MyClass members:\n"  );
	//				//hDlg->FlagCount++;
	//				FlagCount++;
	//				revbuf=m_pSerial->Command((BYTE*)buf,sizeof(buf),&revlen);
	//				if(revlen==6)
	//				{
	//				if(revbuf[0] == 0x02&&revbuf[1] == 0x06&&revbuf[4] == 0x03)
	//					data=(revbuf[2]*256+revbuf[3])/100.0;
	//					if(data>327.67) data=data-655.35;
	//					temp=data;
	//				}
	//				else
	//				{
	//					data=temp;
	//				}
	//				////data=hDlg->GetValue();
	//				////if(CW==1)
	//				////{
	//				//
	//				////str.Format(L"�ɼ���ţ�%d\n",hDlg->FlagCount);
	//				////TRACE(_T("%s"),str);
	//				m_Array.Add(data);
	//				//hDlg->Invalidate();
	//				//}
	//				//double x,y;
	//				//CListBox *plist=(CListBox*)GetDlgItem(IDC_LIST1);
	//				//CString str;
	//				//str.Format(L"%lf",data);
	//				//plist->AddString((LPCTSTR)str); 
	//				//CWnd   *pWnd   =   ReduceMeasurementDlg->GetDlgItem(IDC_STC_IMAGE);     

	//				//pWnd->Invalidate();  
	//				//pWnd->UpdateWindow();
	//				//hDlg->Invalidate();
	//			}
	//			else if(Level==1)
	//			{
	//				DropFlag=true;
	//			}
	//		}
	//	}
		break;
	case 2:
		RunFlag=0;
		CString str;
		int s1,s2,s3;
		//GetStandardPos(&m_Array,&s1,&s2,&s3);
		GetStandardPos(&m_Array,&s1,&s2);
		double v1,v2,v3,v4;
		v2=GetMaxValue(&m_Array,s1+5,s2-5);
		v1=GetMaxValue(&m_Array,s1-150,s1-5);
		theApp.AppPosStart= s1;
		theApp.AppPosFinish=s2; 
		v3=fabs(v2-v1);
		wchar_t   *stopstring;
		v4=wcstod(theApp.AppStandardVal,&stopstring);
		theApp.AppMeasurementVal.Format(L"%.3f",v3);
		theApp.AppDifferenceVal.Format(L"%.3f",v3-v4);

		str.Format(L"��׼ֵ��%s\n����ֵ��%s\n�ɼ�������%d\n����������%d\n",theApp.AppStandardVal,theApp.AppMeasurementVal ,FlagCount,m_SendCout);
		GetDlgItem(IDC_STC_CONTENT)->SetWindowTextW(str);
		TRACE(_T("%s"),str);
		Invalidate();
		((CButton*)GetDlgItem(IDC_BUT_TEST))->EnableWindow(true);
		((CButton*)GetDlgItem(IDC_BUT_SAVE))->EnableWindow(true);
		
		API_GPIO_Output(0,0);
		Sleep(1);
		API_GPIO_Output(1,1);
		KillTimer(2);
		break;
	//default:
	//	break;
	}
	CDialog::OnTimer(nIDEvent);
}

void CReduceMeasurementDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	

	CDialog::OnClose();
}

double CReduceMeasurementDlg::GetValue(void)
{
	long revlen=0;
	short rev=0;

	BYTE* bufdata=NULL;
	//�����յĻ�����������pRecvBuf��
	DWORD dwStart = GetTickCount();
	DWORD dwEnd = 0;
	

	BYTE buf[]={0x02,0x43,0xB0,0x01,0x03,0xF2};
	m_pSerial->WriteSyncPort((BYTE*)buf,sizeof(buf));
	//CopyMemory(buf,pRecvBuf,pRecvLen);
	do
	{
		if(pRecvLen>0)
		{
			bufdata = new BYTE[pRecvLen];
			CopyMemory(bufdata,pRecvBuf,pRecvLen);
			if(pRecvLen>0)
				rev=bufdata[2]*256+bufdata[3];
			if(rev>32767) rev=rev-65535;
			return rev/100.0;
		}
	 dwEnd = GetTickCount();
	 
	} while((dwEnd - dwStart) <= 1000); 
	
	return 0.0;

	//BYTE *revbuf=NULL;
	//revbuf=m_pSerial->ReadSyncPort(&revlen);
	//if(revlen>0)
	//	rev=revbuf[2]*256+revbuf[3];
	//return rev/100.0;
}

void CReduceMeasurementDlg::OnBnClickedButTest()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//m_Array.RemoveAll();  //ɾ������Ԫ��
	//m_DIR=0;
	//API_GPIO_Output(1,m_DIR);
	//SetTimer(1,100,NULL);
	//API_GPIO_Output(2, 1);
	//iNUM=0;
	CReduceMessageDlg dlg;
	//m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
		((CButton*)GetDlgItem(IDC_BUT_TEST))->EnableWindow(false);
		TRACE0( "��ʼ�źš���\n"  );
		//RunFlag=1;
		//m_dwRunFlag=1;

		RunFlag=2;
		FlagCount=0;
		m_SendCout=0;
		SetTimer(2,10000,NULL);
		API_GPIO_Output(0,1);
		Sleep(1);
		API_GPIO_Output(1,0);
		m_Array.RemoveAll();  //ɾ������Ԫ��
		//API_GPIO_Output(2, 1);
		//m_hThread = CreateThread(NULL,0,ThreadFunc,this,0,&m_dwThreadID);
	}
}

void CReduceMeasurementDlg::OnBnClickedButExtended()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->MessageBoxW(L"dddd");
	    int Num;
	CString str;
	CString  m_Temp=_T("");
	SYSTEMTIME st;
	CString strDate,strTime;
	GetLocalTime(&st);
	strDate.Format(_T("%4d%02d%02d%02d%02d%02d"),st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);
	
	Num=m_Array.GetCount();
	for(int i=0;i<Num;i++)
	{
	str.Format(_T("%lf"),m_Array.GetAt(i)); 
	m_Temp+=str+_T("\r\n");//+_T(";");
	}

	//FileWrite(_T("\\ResidentFlash2\\GUI\\") +strDate +_T(".txt"),m_Temp);
	
	FileWrite(ReturnPath() +strDate +_T(".txt"),m_Temp);
	//FileWrite(_T("\\Ӳ��\\") +strDate +_T(".txt"),m_Temp);


}

int CReduceMeasurementDlg::FileWrite(CString filename, CString content)
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
	return 0;
}


int CReduceMeasurementDlg::FileRead(CString filename,CString* content)
{
	int lRet;
	HANDLE hFile = INVALID_HANDLE_VALUE;	// �ļ���� 
	if(::GetFileAttributes(filename)==0xFFFFFFFF)
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

void CReduceMeasurementDlg::Split(CString source, CStringArray& dest, CString division)
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

CString CReduceMeasurementDlg::ReturnPath(void)
{
	  CString    sPath;   
	  GetModuleFileName(NULL,sPath.GetBufferSetLength(MAX_PATH+1),MAX_PATH);   
	  sPath.ReleaseBuffer();   
	  int    nPos;   
	  nPos=sPath.ReverseFind('\\');   
	  sPath=sPath.Left(nPos+1);   
	  return    sPath;   
}

void CReduceMeasurementDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	API_GPIO_Output(0, 0);
	API_GPIO_Output(1, 0);
	API_GPIO_Output(2, 0);
	API_GPIO_Output(3, 0);

//��ͼ��ɺ������
MemBitmap.DeleteObject(); 
MemDC.SelectObject(pOldBit);
MemDC.DeleteDC();

	//KillTimer(1);

	//�رմ���
	if (m_pSerial != NULL)
	{
		//�رմ���
		m_pSerial->ClosePort();

		//�ͷŴ��ڶ���
		delete m_pSerial;
		m_pSerial = NULL;
		//AfxMessageBox(L"���ڹرճɹ�");
	}
	if (WaitForSingleObject(m_hThread,400) == WAIT_TIMEOUT)
	{
		TerminateThread(m_hThread,0);
	}
	m_hThread = NULL;
}

double CReduceMeasurementDlg::GetMaxValue(CArray <double> *data, int dstart, int dfinish)
{
	int i,j;// ѭ������  
    double dTemp;  
	if(dstart<0||dfinish<0) return 0.0;
	int dlen=(int)data->GetSize();
	double *sdata=new double(dfinish-dstart);
	if(dfinish==-1) dfinish=dlen;
	for(i=0;i<dfinish-dstart;i++)
	{
		sdata[i]=data->GetAt(dstart+i);
		//TRACE(_T("%f"),sdata[i]);
	}
	
    //TRACE(_T("\n"));
      
    // ��ð�ݷ��������������  
    for (j = 0; j < dfinish-dstart ; j ++)  
    {  
        for (i = 0; i < dfinish-dstart - j; i ++)  
        {  
			if (sdata[i] < sdata[i+1])  
            {  
                // ����  
				dTemp = sdata[i];  
				sdata[i]=sdata[i+1];
				sdata[i+1]=dTemp;

				//for(int p=0;p<dfinish-dstart;p++)
				//{
				//	TRACE(_T("%f"),sdata[p]);
				//}
				//TRACE(_T("\n"));

            }  
        }  
    } 
	dTemp=sdata[0];
	delete []sdata;
	return dTemp;
}

//int CReduceMeasurementDlg::GetStandardPos(CArray <double> * data, int * start, int *middle,int * finish)
int CReduceMeasurementDlg::GetStandardPos(CArray <double> * data, int * start,int * finish)
{
	int i,j,n=0;// ѭ������  
    double dValue,*dTemp;
	int dlen=(int)data->GetSize();
	dTemp=new double(dlen);
	//dValue=new double(dlen);

	for(i=dlen-2;i>=1;i--)
	{
		dTemp[i]=(data->GetAt(i+1)-data->GetAt(i-1))/2.0;
		TRACE(_T("%f "),dTemp[i]);
	}
	
	//for(i=dlen-4;i>=3;i--)
	//{
	//	dValue[i]=(dTemp[i-2]+dTemp[i-1]+dTemp[i]+dTemp[i+1]+dTemp[i+2])/5;
	//	TRACE(_T("%f "),dTemp[i]);
	//}

	TRACE(_T("\n"));
	for(i=dlen-4;i>=3;i--)
	{
		if(dTemp[i-2]>dTemp[i-1]&&(dTemp[i-1]-dTemp[i])>0.1&&dTemp[i+1]-dTemp[i]>0.1&&dTemp[i+1]<dTemp[i+2])
		//if(dTemp[i-2]>dTemp[i-1]&&dTemp[i-1]>dTemp[i]&&dTemp[i]<dTemp[i+1]&&dTemp[i+1]<dTemp[i+2])
		{
			if(n==0)
			{
				*finish=i;
				TRACE(_T("%d "),i);
				n=1;
			}
			else if(n==1)
			{
				*start=i;
				TRACE(_T("%d "),i);
				n=2;
			}
		}
		/*else if(n==2)
		{
			if(dTemp[i-2]<dTemp[i-1]&&(dTemp[i-1]-dTemp[i])<0.1&&dTemp[i+1]-dTemp[i]<0.1&&dTemp[i+1]>dTemp[i+2])
			{
				*start=i;
				TRACE(_T("%d "),i);
				n=3;
			}
		}*/
		//dTemp=data->GetAt(i);
		//if(dTemp!=-327.67)
		//{
		//	if(dTemp<dValue) dValue=dTemp					
		//}
		//dTemp=(data->GetAt(i)-data->GetAt(i-2))/2.0;
		

	}

	return 0;
}
