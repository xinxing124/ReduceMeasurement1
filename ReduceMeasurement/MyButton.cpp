// MyButton.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ReduceMeasurement.h"
#include "MyButton.h"


// CMyButton

IMPLEMENT_DYNAMIC(CMyButton, CButton)

CMyButton::CMyButton()
{

}

CMyButton::~CMyButton()
{
}


BEGIN_MESSAGE_MAP(CMyButton, CButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



// CMyButton ��Ϣ�������



void CMyButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
// TODO: Add your message handler code here and/or call default


	CButton::OnLButtonDown(nFlags, point);
	WPARAM wParam = (((DWORD)WM_LBUTTONDOWN) << 16) + ((DWORD)GetDlgCtrlID());
	::SendMessage(this->GetParent()->GetSafeHwnd(),WM_COMMAND, wParam, 0);
}

void CMyButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CButton::OnLButtonUp(nFlags, point);
}
