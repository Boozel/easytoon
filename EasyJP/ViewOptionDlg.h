#if !defined(AFX_VIEWOPTIONDLG_H__EE57B9DB_A60C_11D1_AB14_444553540000__INCLUDED_)
#define AFX_VIEWOPTIONDLG_H__EE57B9DB_A60C_11D1_AB14_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ViewOptionDlg.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CViewOptionDlg �_�C�A���O

class CViewOptionDlg : public CDialog
{
// �R���X�g���N�V����
public:
	CViewOptionDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CViewOptionDlg)
	enum { IDD = IDD_VIEWOPTION };
	int		m_nZoomMagnify;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CViewOptionDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CViewOptionDlg)
		// ����: ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ����܂��B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_VIEWOPTIONDLG_H__EE57B9DB_A60C_11D1_AB14_444553540000__INCLUDED_)
