#if !defined(AFX_ANIMPROPERTYDLG_H__EE57B9DC_A60C_11D1_AB14_444553540000__INCLUDED_)
#define AFX_ANIMPROPERTYDLG_H__EE57B9DC_A60C_11D1_AB14_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// AnimPropertyDlg.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CAnimPropertyDlg �_�C�A���O

class CAnimPropertyDlg : public CDialog
{
// �R���X�g���N�V����
public:
	CAnimPropertyDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CAnimPropertyDlg)
	enum { IDD = IDD_ANIMPROPERTY };
	int		m_nDefaultDelay;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CAnimPropertyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CAnimPropertyDlg)
		// ����: ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ����܂��B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_ANIMPROPERTYDLG_H__EE57B9DC_A60C_11D1_AB14_444553540000__INCLUDED_)
