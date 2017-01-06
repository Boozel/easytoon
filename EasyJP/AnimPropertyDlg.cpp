// AnimPropertyDlg.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "EasyToon.h"
#include "AnimPropertyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAnimPropertyDlg �_�C�A���O


CAnimPropertyDlg::CAnimPropertyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAnimPropertyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAnimPropertyDlg)
	m_nDefaultDelay = 10;
	//}}AFX_DATA_INIT
}


void CAnimPropertyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAnimPropertyDlg)
	DDX_Text(pDX, IDC_EDIT_DEFAULTDELAY, m_nDefaultDelay);
	DDV_MinMaxInt(pDX, m_nDefaultDelay, 1, 65535);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAnimPropertyDlg, CDialog)
	//{{AFX_MSG_MAP(CAnimPropertyDlg)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnimPropertyDlg ���b�Z�[�W �n���h��
