////////////////////////////////////////////////////////////////////////////
//
//	LZW���k �G���R�[�_���f�R�[�_ (GIF�`���Ή�)
//
//	1998 (C) Keijiro Takahashi (keijiro@din.or.jp)
//
#ifndef __LZW_H_
#define __LZW_H_

#define LZW_MAXBITWIDTH		12
#define LZW_NULL			0xffff

//
//	�G���R�[�_
//
class CLzwEncoder
{
protected:
	int		m_nCodeSize;		// �R�[�h�E�r�b�g��
	int		m_nBitWidth;		// �r�b�g��

	int		m_nImageWidth;		// �C���[�W��
	int		m_nWidthCtr;		// ���J�E���^

	WORD	m_wCC;				// Clear Code
	WORD	m_wEOI;				// End Of Input

	WORD*	m_pwStrTbl;			// �X�g�����O�e�[�u��
	WORD	m_nStrTblCtr;		// �X�g�����O�e�[�u���E�J�E���^
	WORD*	m_pwSearchTbl;		// �T�[�`�p�n�b�V���E�e�[�u��

	BYTE*	m_pSrcBuf;			// �\�[�X�f�[�^�E�o�b�t�@
	BYTE*	m_pRead;			// ���[�h�E�|�C���^
	int		m_nReadBit;			// ���[�h�E�|�C���^�i�r�b�g�j

	BYTE*	m_pOutBuf;			// �o�̓o�b�t�@
	BYTE*	m_pWrite;			// ���C�g�E�|�C���^
	int		m_nWriteBit;		// ���C�g�E�|�C���^�i�r�b�g�j

	void	InitStrTbl ();							// �X�g�����O�E�e�[�u���̏�����
	void	AddString ( WORD w1, WORD w2 );			// �X�g�����O�̓o�^
	WORD	SearchString ( WORD w1, WORD w2 );		// �X�g�����O�̌���
	
	void	InitBuffer( BYTE* pSrc ,BYTE* pOut );	// �o�b�t�@�̏�����
	BYTE	Read();									// �ǂݍ���
	void	Write ( WORD w );						// �����o��

public:
	CLzwEncoder ();									// �R���X�g���N�^
	~CLzwEncoder ();								// �f�X�g���N�^
	int	Encode ( BYTE* pSrc, int nLength, int nImageWidth,  int nBitWidth ,BYTE* pOut );	// �G���R�[�f�B���O
};


//
//	�f�R�[�_
//
class CLzwDecoder
{
protected:
	int		m_nCodeSize;		// �R�[�h�E�r�b�g��
	int		m_nBitWidth;		// �r�b�g��

	int		m_nImageWidth;		// �C���[�W��
	int		m_nWidthCtr;		// ���J�E���^

	WORD	m_wCC;				// Clear Code
	WORD	m_wEOI;				// End Of Input

	WORD*	m_pwStrTblPrefix;		// �X�g�����O�e�[�u���i�v���t�B�N�X�j
	BYTE*	m_pbStrTblSuffix;		// �X�g�����O�e�[�u���i�T�t�B�N�X�j
	WORD	m_nStrTblCtr;			// �X�g�����O�e�[�u���E�J�E���^

	BYTE*	m_pOutBuf;				// �o�̓o�b�t�@
	BYTE*	m_pWrite;				// ���C�g�E�|�C���^
	int		m_nWriteBit;			// ���C�g�E�|�C���^�i�r�b�g�j

	BYTE*	m_pSrcBuf;				// �\�[�X�f�[�^
	BYTE*	m_pRead;				// ���[�h�E�|�C���^
	int		m_nReadBit;				// ���[�h�E�|�C���^�i�r�b�g�j

	void	InitStrTbl ();									// �X�g�����O�E�e�[�u���̏�����
	void	AddString ( WORD w, BYTE b );					// �X�g�����O�ǉ�
	BYTE	GetString ( WORD wIndex, WORD* w );				// �X�g�����O�擾

	void	InitBuffer( BYTE* pSrc ,BYTE* pOut );			// �o�b�t�@�̏�����
	WORD	Read();											// �ǂݍ���
	void	Write ( BYTE b );								// �����o��

public:
	CLzwDecoder();							// �R���X�g���N�^
	~CLzwDecoder();							// �f�X�g���N�^
	int	Decode  ( BYTE* pSrc, int nImageWidth, int nCodeSize, BYTE* pOut );	// �f�R�[�f�B���O
};


#endif
