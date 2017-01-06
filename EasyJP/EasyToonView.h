#if !defined(AFX_EASYTOONVIEW_H__EE57B9D1_A60C_11D1_AB14_444553540000__INCLUDED_)
#define AFX_EASYTOONVIEW_H__EE57B9D1_A60C_11D1_AB14_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000



#define VIEW_MARGIN		2

//
// CFrameView�N���X
//
class CEasyToonView : public CScrollView
{
public:
	// �A�N�Z�X���\�b�h
	// �֘A�t����ꂽ�h�L�������g�̎擾
	CEasyToonDoc* GetDocument();
	// �t���[���E�B���h�E�̎擾
	CMainFrame* GetMainFrame()					{ return (CMainFrame*)GetParentFrame(); }
	// �J�����g�t���[���ԍ��̎擾
	int			GetCurrentFrame()				{ return m_nCurrentFrame; }
	// �t���[���E�C���^�[�o���̐ݒ�
	void		SetFrameDelay ( int nDelay )	{ GetDocument()->SetFrameDelay ( m_nCurrentFrame, nDelay ); }
	// �y���T�C�Y�̕ύX
	void		SetPenSize ( int nSize )		{ m_nPenSize = nSize; }

	// �����S���T�C�Y�ύX
	void		SetEraseSize ( int nSize )		{ m_nRPenSize = nSize; }


protected:
	// �I�u�W�F�N�g
enum TOOL { select, pen, fill, line, linestrip, rect, fillRect, ellipse, fillEllipse,paraline,move,Text } m_nTool;	// �`�惂�[�h
enum MOVESUBSTAT { stretchout, stretchmove, stretchlefttop, stretchtop, stretchrighttop, stretchleft, stretchright, stretchleftbottom, stretchbottom, stretchrightbottom, stretchview } m_nMoveSubStat;

  enum {Horizontal,Vertical};

  int			m_nCurrentFrame;		// �J�����g�t���[���ԍ�
	// �L�����o�X
	CBitmap*	m_pbmpCanvas;			// �L�����o�X�̉��z���
	CDC			m_dcCanvas;				// �L�����o�X�̃������c�b
  bool m_bDrawPrev;
  bool m_bDrawNext;
  // �t���[���W�F�\���p
  CBitmap *m_pbmpBackFrame;
  CDC m_dcBackFrame;

  // ���C����g��k���Ȃǂ̃C���^�[�t�F�C�X�\���p
  CBitmap *m_pbmpInterface;
  CDC m_dcInterface;
  int m_nInterfacePenSize;
  COLORREF m_crInterfacePenColor;

  // �A���h�D
	BOOL		m_blCanUndo;			// �A���h�D�\���H
	BOOL		m_blCanRedo;			// ���h�D�\���H
	enum UNDOTYPE { restoreBitmap, restoreFrame, deleteFrame } m_nUndoType;	// �A���h�D�̎��
	CBitmap*	m_pbmpUndoBuf;			// �A���h�D�p�o�b�t�@
	CBitmap*	m_pbmpRedoBuf;			// ���h�D�p�o�b�t�@
	CDC			m_dcUndoBuf;			// �A���h�D�p�o�b�t�@�ւ̃������c�b
	// �J�b�g���y�[�X�g
//	CRect		m_rectSelect;			// �I��͈�
//	CBitmap*	m_pbmpSelectBuf;		// �I��p�o�b�t�@
//	CDC			m_dcSelectBuf;			// �I��p�o�b�t�@�ւ̃������c�b
//	CRect		m_rectCutBuf;			// �J�b�g�o�b�t�@�̋�`���
//	CBitmap*	m_pbmpCutBuf;			// �J�b�g�o�b�t�@
//	CDC			m_dcCutBuf;				// �J�b�g�o�b�t�@�̃������c�b
	// �A�g���r���[�g
	CSize		m_sizeFrame;			// �t���[���̃T�C�Y
	int			m_nZoomMagnify;			// �Y�[����
	int			m_nTraceDepth;			// �g���X����[��
	double		m_dTraceFade;			// �g���X�̃��C�g���x
	int			m_nPenSize;				// �y���T�C�Y
	int     m_nRPenSize;
	COLORREF	m_crLeftPen;			// ���y���̐F
	COLORREF	m_crRightPen;			// �E�y���̐F
  bool    m_bLine;          // ���C���X�g���b�v�̂Ƃ��Ƀ��C���`�撆
  bool    m_bButton;        // ���C���X�g���b�v�̂Ƃ��̃N���b�N����
  int     m_nLastButton;    // ���C���X�g���b�v���̍Ō�ɉ�����Ă��{�^��
  // �G�p�I�u�W�F�N�g
	CPoint		m_ptFrom;				// �|�C���g�w��E�G�p
	CPoint		m_ptTo;					// �|�C���g�w��E�G�p
	CRect		m_rectTmp;				// ��`�w��E�G�p
	CPen		m_penDraw;				// �`��p�y��

  // �J�b�g���y�[�X�g
  CRect m_rectCopyDst; // �R�s�[���`�ۑ�
  CRect m_rectCopySrc; // �R�s�[����`�ۑ�
  CBitmap *m_pbmpCopySrc;
  CDC m_dcCopySrc;

  CPoint m_ptCopyDst[4]; // ���R�ό`�R�s�[��ۑ�
  float m_fRotate; // ����������]�p��ۑ����Ƃ�
  CPoint m_ptCopyCenterSrc; // �����������S���ۑ����Ƃ�
  CPoint m_ptCopyCenterDst; 

  //Variables pour l'utilisation de paraline
  double m_paraline_coefdir;
  double m_paraline_B;
  CRect m_paraline_rect;

  bool m_bFirstUsePara;
  bool consty;
  bool constx;

  bool m_shift;

  int m_CanvasMarginH,m_CanvasMarginW;

  enum COPYMODE { SCALEFREE, SCALEFIX, ROTATE, FREE };

  int m_iCopyMode; // �R�s�[���[�h

  // �p�^�[��
  CBitmap *m_pbmpPattern;
  int m_nBrush;

  bool m_nZoomMax;
	// �`�惁�\�b�h
	void	DrawFrames( CRect* pRect = NULL, BOOL blSelReg = TRUE );	// �t���[�����L�����o�X�ɕ`��
	void	DrawCanvas( CDC* pDC, CRect* pRect = NULL );		// �L�����o�X���E�B���h�E�ɕ`��
	// �}�E�X�n���h���⏕
	void	ScreenToCanvas( POINT* pt, BOOL blClip = TRUE );	// ���W���L�����o�X�̃��[�J�����W�ɕϊ�
	void	QuantizeForCanvas( POINT* pt, BOOL blClip = TRUE );	// �L�����o�X�̉𑜓x�ɍ��킹�ėʎq��
	void	PasteSelectBuf();									// �͈͎w��o�b�t�@��f���o��
	void	BeginDraw( CPoint point, int nBtn );				// �`��J�n�iButtonDown�j
	void	KeepDraw( CPoint point, int nBtn );					// �`�掝�� (ButtonMove)
	void	EndDraw( CPoint point, int nBtn );					// �`��I�� (ButtonUp)
	void	StopDraw( );										// �`�撆�~ (��dButtonDown)
	// ���̑�
	void	UpdateUndoBuffer ( UNDOTYPE nType );			// �A���h�D�o�b�t�@���X�V
	void	SquareRect(CRect Rect, CPoint & PtFrom, CPoint & PtTo);
	POINT	TranslatePoint( POINT pt, BOOL blClip );		// ���W���L�����o�X�̃��[�J�����W�ɕϊ�
	


protected:
	CEasyToonView();
	DECLARE_DYNCREATE(CEasyToonView)
public:
	//{{AFX_VIRTUAL(CEasyToonView)
	public:
	virtual void OnDraw(CDC* pDC);  // ���̃r���[��`�悷��ۂɃI�[�o�[���C�h����܂��B
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL
public:
	void _DrawSelectionArea( CDC *pDC, CPoint point[], int nPick);
	void _CopyBufferToClipboard();

	void SetZoomMagnify( int nZoomMagnify );
	void _EndLineStrip();
	virtual ~CEasyToonView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
protected:
protected:
	//{{AFX_MSG(CEasyToonView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnFramePrev();
	afx_msg void OnFrameNext();
	afx_msg void OnFrameInsert();
	afx_msg void OnFrameDelete();
	afx_msg void OnFrameClear();
	afx_msg void OnEditCopy();
	afx_msg void OnEditCut();
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
	afx_msg void OnEditRedo();
	afx_msg void OnUpdateEditRedo(CCmdUI* pCmdUI);
	afx_msg void OnToolSelect();
	afx_msg void OnUpdateToolSelect(CCmdUI* pCmdUI);
	afx_msg void OnFileExportgif();
	afx_msg void OnViewOption();
	afx_msg void OnViewPlay();
	afx_msg void OnViewProperty();
	afx_msg void OnUpdateFramePrev(CCmdUI* pCmdUI);
	afx_msg void OnFileExportbmp();
	afx_msg void OnFileImportgif();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnDrawNextframe();
	afx_msg void OnUpdateDrawNextframe(CCmdUI* pCmdUI);
	afx_msg void OnDrawPrevframe();
	afx_msg void OnUpdateDrawPrevframe(CCmdUI* pCmdUI);
	afx_msg void OnSwapColor();
	afx_msg void OnViewPlayseg();
	afx_msg void OnFileImportezt();
	afx_msg void OnEditPastefromfile();
	afx_msg void OnMaskcopy();
	afx_msg void OnTbselectScalefree();
	afx_msg void OnUpdateTbselectScalefree(CCmdUI* pCmdUI);
	afx_msg void OnTbselectScalefix();
	afx_msg void OnUpdateTbselectScalefix(CCmdUI* pCmdUI);
	afx_msg void OnTbselectRotate();
	afx_msg void OnUpdateTbselectRotate(CCmdUI* pCmdUI);
	afx_msg void OnTbselectFree();
	afx_msg void OnUpdateTbselectFree(CCmdUI* pCmdUI);
	afx_msg void OnMoveEnd();
	afx_msg void OnMoveNext1();
	afx_msg void OnMoveNext10();
	afx_msg void OnMovePrev1();
	afx_msg void OnMovePrev10();
	afx_msg void OnMoveStart();
	//}}AFX_MSG
	afx_msg void OnBrushBtn( UINT nID );
	afx_msg void OnUpdateBrushBtn( CCmdUI* pCmdUI );
	afx_msg void OnToolBoxBtn( UINT nID );
	afx_msg void OnUpdateToolBoxBtn( CCmdUI* pCmdUI );
	afx_msg void Flip(int type);
	afx_msg void OnFlipVertical();
	afx_msg void OnFlipHorizontal();
	afx_msg void OnNegatif();
	afx_msg void OnText();
	DECLARE_MESSAGE_MAP()
private:
	void _DrawInterfaceEllipse( void );
	void _DrawInterfaceRectangle();
	void _CreatePatternBrush();
	int _PickSelectionArea( CPoint ptSrc[], int nPick, CPoint ptTarget );
	void _CurrentFrameToCopyBuffer( CRect rectCopySrc );
	void _ClipboardToCopyBuffer();
	void _CurrentFrameToClipboard( CRect rect );
	void _EndCopy();
	void _DrawInterfaceMove();
	void _DrawInterface();
	void _DrawBackFrame();
	void _DrawInterfaceLine();
	int _PickSelectionRect( CRect rect, int nPick, CPoint point );
	int _ClipCanvasH( int pos );
	int _ClipCanvasV( int pos );
	int _CanvasToScreen( int pos );
  int _QuantizeForCanvas(int pos);
	CRect _QuantizeForCanvas( CRect rect, bool bClip = true );
	void _DrawSelectionRect( CDC *pDC, CRect rect, int nPick );
	CRect _CanvasToScreen( CRect rect );
public:
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	int GetZoomMagnify(void);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
};


#ifndef _DEBUG
inline CEasyToonDoc* CEasyToonView::GetDocument()
   { return (CEasyToonDoc*)m_pDocument; }
#endif

//{{AFX_INSERT_LOCATION}}

#endif
