#if !defined(AFX_EASYTOONDOC_H__EE57B9CF_A60C_11D1_AB14_444553540000__INCLUDED_)
#define AFX_EASYTOONDOC_H__EE57B9CF_A60C_11D1_AB14_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000



// �萔
#define FRAMEDOC_DEFAULTDELAY 10

//
// �t���[���E�N���X
//
class CFrame : public CObject
{
protected:
	CBitmap	m_bmp;			// �r�b�g�}�b�v
	CDC		m_dc;			// �r�b�g�}�b�v�̃������c�b
	int		m_nDelay;		// �x������
public:
	CFrame ( SIZE size );
	~CFrame ();
	// �e��A�N�Z�X���\�b�h
	CBitmap* GetBitmap () { return &m_bmp; }
	CDC*     GetDC ()     { return &m_dc; }
	int		 GetDelay ()  { return m_nDelay; }
	void	 SetDelay ( int nDelay ) { m_nDelay = nDelay; }
};

//
// �h�L�������g�E�N���X
//
class CEasyToonDoc : public CDocument
{
protected:
	CObList	m_frameList;		// �t���[���̃��X�g
	CObList	m_MemoryList;
	int		m_nDefaultDelay;	// �x�����Ԃ̃f�t�H���g�l
	CSize	m_sizeFrame;		// �t���[���̃T�C�Y
	int			m_nTracePrevFrameNb;
	int			m_nTraceNextFrameNb;

public:
	// get
	CBitmap*	GetFrameBmp ( int nFrame );			// �t���[���̎擾�i�r�b�g�}�b�v�j
	CDC*		GetFrameDC  ( int nFrame );			// �t���[���̎擾�i�������c�b�j
	int			GetFrameDelay ( int nFrame );		// �x�����Ԃ̎擾
	int			GetDefaultDelay ();					// �x�����Ԃ̃f�B�t�H���g�̎擾
	SIZE		GetFrameSize ();					// �t���[���T�C�Y�̎擾
	int			GetCount ();						// �S�t���[�����̎擾
	// set
	void		SetFrameDelay ( int nFrame, int nDelay );	// �x�����Ԃ̐ݒ�
	void		SetDefaultDelay ( int nDelay );				// �x�����Ԃ̃f�B�t�H���g�̐ݒ�
	void		SetFrameSize ( SIZE size );					// �t���[���T�C�Y�̐ݒ�

	int GetPrevFrameNb(){return m_nTracePrevFrameNb;}
	int GetNextFrameNb(){return m_nTraceNextFrameNb;};
	void SetPrevFrameNb( int NbFrame );
	void SetNextFrameNb( int NbFrame );
	// �t���[������
	int			AppendNewFrame ();					// �V�K�t���[���̒ǉ�
	void		DeleteFrameFromMemory(int nFrame);
	void		CopyFrameToMemory(int nFrame);
	CBitmap*	GetBitmapFromMemoryList(int mFrame);
	CObList*    GetMemoryList();
	void		InsertNewFrame ( int nFrame );		// �V�K�t���[���̑}��
	void		DeleteFrame ( int nFrame );			// �t���[���̍폜
	// ����
	void		ExportGif ( LPCTSTR lpszFileName );	// GIF�`���ł̃G�N�X�|�[�g
	void		ImportGif ( CArchive* ar , BOOL IsOpening, int m_nCurrentFrame );
	void    ExportBmp( LPCTSTR lpszFilename ); // BMP�`���ł̃G�N�X�|�[�g

	static void _SetPixelColor1( BYTE *pPixel, int nWidth, int nHeight, int x, int y, int color );
	static int _GetPixelColor1( BYTE *pPixel, int nWidth, int nHeight, int x, int y );
	static void _SetPixelColor24( BYTE *pPixel, int nWidth, int nHeight, int x, int y, COLORREF color );
	static COLORREF _GetPixelColor24( BYTE *pPixel, int nWidth, int nHeight, int x, int y );

protected:
	CEasyToonDoc();
public:
	DECLARE_DYNCREATE(CEasyToonDoc)
	//{{AFX_VIRTUAL(CEasyToonDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void DeleteContents();
	//}}AFX_VIRTUAL
public:
	void ImportEzt( LPCTSTR lpszFilename, int nInsertPos );
	virtual ~CEasyToonDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
protected:
	//{{AFX_MSG(CEasyToonDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}

#endif
