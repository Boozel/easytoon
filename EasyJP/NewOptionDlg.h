#if !defined(AFX_NEWOPTIONDLG_H__EE57B9DA_A60C_11D1_AB14_444553540000__INCLUDED_)
#define AFX_NEWOPTIONDLG_H__EE57B9DA_A60C_11D1_AB14_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// NewOptionDlg.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CNewOptionDlg �_�C�A���O

class CNewOptionDlg : public CDialog
{
// �R���X�g���N�V����
public:
	CNewOptionDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CNewOptionDlg)
	enum { IDD = IDD_NEWOPTION };
	int		m_nFrameHeight;
	int		m_nFrameWidth;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CNewOptionDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CNewOptionDlg)
		// ����: ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ����܂��B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_NEWOPTIONDLG_H__EE57B9DA_A60C_11D1_AB14_444553540000__INCLUDED_)
