// EasyToon.h : EASYTOON �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C��
//

#if !defined(AFX_EASYTOON_H__EE57B9C9_A60C_11D1_AB14_444553540000__INCLUDED_)
#define AFX_EASYTOON_H__EE57B9C9_A60C_11D1_AB14_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // ���C�� �V���{��

#define FRAMEDOC_DEFAULTWIDTH		160
#define FRAMEDOC_DEFAULTHEIGHT		120
#define FRAMEVIEW_DEFAULTMAGNIFY	2
#define FRAMEVIEW_MAXMAGNIFY		30
#define FRAMEVIEW_CANVASMARGIN		2

/////////////////////////////////////////////////////////////////////////////
// CEasyToonApp:
// ���̃N���X�̓���̒�`�Ɋւ��Ă� EasyToon.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

class CEasyToonApp : public CWinApp
{
public:
	CEasyToonApp();
	bool GetDem ();
	void SetDem (bool);
	
private:
	bool m_demarrage;

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CEasyToonApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����

	//{{AFX_MSG(CEasyToonApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileOpen();
	afx_msg void OnFileNew();
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_EASYTOON_H__EE57B9C9_A60C_11D1_AB14_444553540000__INCLUDED_)
