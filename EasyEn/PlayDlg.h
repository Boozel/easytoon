#include "afxcmn.h"
#if !defined(AFX_PLAYDLG_H__EE57B9DD_A60C_11D1_AB14_444553540000__INCLUDED_)
#define AFX_PLAYDLG_H__EE57B9DD_A60C_11D1_AB14_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PlayDlg.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CPlayDlg �_�C�A���O

class CPlayDlg : public CDialog
{
protected:
	CEasyToonDoc*	m_pDoc;			// �h�L�������g�ւ̃|�C���^
	int				m_nZoom;		// �L�����o�X�̃Y�[���䗦
	int				m_nTimerID;		// �^�C�}�h�c
	DWORD			m_dwDelay;		// �x������
	DWORD			m_dwStart;		// �҂��n��
	int				m_nFrame;		// �t���[���ԍ�
	void DrawCanvas();

  int m_nStart, m_nEnd;

// �R���X�g���N�V����
public:
	CPlayDlg(CWnd* pParent, CEasyToonDoc* pDoc, int nZoom, int nStart, int nEnd );   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CPlayDlg)
	enum { IDD = IDD_PLAY };
		// ����: ClassWizard �͂��̈ʒu�Ƀf�[�^ �����o��ǉ����܂��B
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CPlayDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CPlayDlg)
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CProgressCtrl m_progress;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_PLAYDLG_H__EE57B9DD_A60C_11D1_AB14_444553540000__INCLUDED_)
