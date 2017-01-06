// ViewOptionDlg.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "EasyToon.h"
#include "ViewOptionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewOptionDlg �_�C�A���O


CViewOptionDlg::CViewOptionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CViewOptionDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CViewOptionDlg)
	m_nZoomMagnify = 0;
	//}}AFX_DATA_INIT
}


void CViewOptionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CViewOptionDlg)
	DDX_Text(pDX, IDC_EDIT_ZOOM, m_nZoomMagnify);
	DDV_MinMaxInt(pDX, m_nZoomMagnify, 1, FRAMEVIEW_MAXMAGNIFY);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CViewOptionDlg, CDialog)
	//{{AFX_MSG_MAP(CViewOptionDlg)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewOptionDlg ���b�Z�[�W �n���h��
