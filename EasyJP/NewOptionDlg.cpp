// NewOptionDlg.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "EasyToon.h"
#include "NewOptionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewOptionDlg �_�C�A���O


CNewOptionDlg::CNewOptionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNewOptionDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewOptionDlg)
	m_nFrameHeight = 0;
	m_nFrameWidth = 0;
	//}}AFX_DATA_INIT
}


void CNewOptionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewOptionDlg)
	DDX_Text(pDX, IDC_EDIT_HEIGHT, m_nFrameHeight);
	DDV_MinMaxInt(pDX, m_nFrameHeight, 8, 1024);
	DDX_Text(pDX, IDC_EDIT_WIDTH, m_nFrameWidth);
	DDV_MinMaxInt(pDX, m_nFrameWidth, 8, 1024);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewOptionDlg, CDialog)
	//{{AFX_MSG_MAP(CNewOptionDlg)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewOptionDlg ���b�Z�[�W �n���h��
