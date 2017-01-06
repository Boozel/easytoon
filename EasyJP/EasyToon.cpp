// EasyToon.cpp : �A�v���P�[�V�����p�N���X�̋@�\��`���s���܂��B
//

#include "stdafx.h"
#include "EasyToon.h"
#include "MainFrm.h"
#include "EasyToonDoc.h"
#include "EasyToonView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEasyToonApp

BEGIN_MESSAGE_MAP(CEasyToonApp, CWinApp)
	//{{AFX_MSG_MAP(CEasyToonApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
		//    ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG_MAP
	// �W���̃t�@�C����{�h�L�������g �R�}���h
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEasyToonApp �N���X�̍\�z

CEasyToonApp::CEasyToonApp()
{
	// TODO: ���̈ʒu�ɍ\�z�p�R�[�h��ǉ����Ă��������B
	// ������ InitInstance ���̏d�v�ȏ��������������ׂċL�q���Ă��������B
	m_demarrage=true;
}

/////////////////////////////////////////////////////////////////////////////
// �B��� CEasyToonApp �I�u�W�F�N�g

CEasyToonApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CEasyToonApp �N���X�̏�����

BOOL CEasyToonApp::InitInstance()
{
	// �W���I�ȏ���������
	// ���������̋@�\���g�p�����A���s�t�@�C���̃T�C�Y��������
	//  ��������Έȉ��̓���̏��������[�`���̒�����s�K�v�Ȃ���
	//  ���폜���Ă��������B
#ifdef _AFXDLL
	Enable3dControls();			// ���L DLL �̒��� MFC ���g�p����ꍇ�ɂ͂������Ăяo���Ă��������B
#else
	Enable3dControlsStatic();	// MFC �ƐÓI�Ƀ����N���Ă���ꍇ�ɂ͂������Ăяo���Ă��������B
#endif

	// �ݒ肪�ۑ�����鉺�̃��W�X�g�� �L�[��ύX���܂��B
	// ��Ж��܂��͏����ȂǁA�K�؂ȕ������
	// �ύX���Ă��������B
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // �W���� INI �t�@�C���̃I�v�V���������[�ނ��܂� (MRU ���܂�)

	// �A�v���P�[�V�����p�̃h�L�������g �e���v���[�g��o�^���܂��B�h�L�������g �e���v���[�g
	//  �̓h�L�������g�A�t���[�� �E�B���h�E�ƃr���[���������邽�߂ɋ@�\���܂��B
	

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CEasyToonDoc),
		RUNTIME_CLASS(CMainFrame),       // ���C�� SDI �t���[�� �E�B���h�E
		RUNTIME_CLASS(CEasyToonView));
	AddDocTemplate(pDocTemplate);

	// DDE Execute open ���g�p�\�ɂ��܂��B
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// DDE�Afile open �ȂǕW���̃V�F�� �R�}���h�̃R�}���h���C������͂��܂��B
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// �R�}���h���C���Ńf�B�X�p�b�` �R�}���h���w�肵�܂��B
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// ���C�� �E�B���h�E�����������ꂽ�̂ŁA�\���ƍX�V���s���܂��B
	m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
	m_pMainWnd->UpdateWindow();

	// �h���b�O/�h���b�v �I�[�v���������܂�
	m_pMainWnd->DragAcceptFiles();
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// �A�v���P�[�V�����̃o�[�W�������Ŏg���� CAboutDlg �_�C�A���O

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard ���z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // // DDX/DDV �̃T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	//{{AFX_MSG(CAboutDlg)
	afx_msg void OnWebbutton();
	afx_msg void OnWebbutton2();
	afx_msg void OnWebbutton3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_BN_CLICKED(IDC_WEBBUTTON, OnWebbutton)
	ON_BN_CLICKED(IDC_WEBBUTTON2, OnWebbutton2)
	ON_BN_CLICKED(IDC_WEBBUTTON3, OnWebbutton3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// �_�C�A���O�����s���邽�߂̃A�v���P�[�V���� �R�}���h
void CEasyToonApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CEasyToonApp �R�}���h

void CAboutDlg::OnWebbutton() 
{
	ShellExecute(AfxGetMainWnd()->GetSafeHwnd(),NULL,"http://www.radiumsoftware.com",NULL,NULL,0);
}

void CAboutDlg::OnWebbutton2() 
{
	ShellExecute(AfxGetMainWnd()->GetSafeHwnd(),NULL,"http://www.F-Team.org/setagaya/index.html",NULL,NULL,0);
}

void CAboutDlg::OnWebbutton3() 
{
	ShellExecute(AfxGetMainWnd()->GetSafeHwnd(),NULL,"http://www.flatd2d.info",NULL,NULL,0);
}

bool CEasyToonApp::GetDem()
{
	return m_demarrage;
}

void CEasyToonApp::SetDem(bool Demarrage)
{
	m_demarrage=Demarrage;
}


