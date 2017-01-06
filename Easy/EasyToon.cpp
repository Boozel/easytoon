// EasyToon.cpp : �A�v���P�[�V�����p�N���X�̋@�\��`���s���܂��B
//

#include "stdafx.h"
#include "mmsystem.h"
#include "EasyToon.h"
#include "MainFrm.h"
#include "EasyToonDoc.h"
#include "EasyToonView.h"
#include "resource.h"


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
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
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

void CEasyToonApp::OnFileNew()
{
	/*this->DoPromptFileName(*/
	CWinApp::OnFileNew();
}

void CEasyToonApp::OnFileOpen()
{
	/*this->*/
	static char szFilter[] = "EasyToon Files (*.ezt)|*.ezt|GIF Files (*.gif)|*.gif|All Files (*.*)|*.*||";
	CFileDialog fileDlg ( true, "gif", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_ENABLEHOOK, szFilter);


	if ( fileDlg.DoModal() == IDOK ) this->OpenDocumentFile(fileDlg.GetFileName());

	/*CWinApp::OnFileOpen();*/
}

BOOL CEasyToonApp::InitInstance()
{
	AfxInitRichEdit();
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
	m_pMainWnd->ShowWindow(SW_SHOWNORMAL);
	m_pMainWnd->UpdateWindow();

	// �h���b�O/�h���b�v �I�[�v���������܂�
	m_pMainWnd->DragAcceptFiles();
	return TRUE;
}

class CPaletteBitmap: public CWnd
//===============================
{
protected:
	LPBITMAPINFO m_lpBmp, m_lpCopy;
	HPALETTE m_hPal;
	LPBYTE m_lpRotoZoom;
	DWORD m_dwStartTime, m_dwFrameTime;
	UINT m_nRotoWidth, m_nRotoHeight;
	BOOL m_bFirst;

public:
	CPaletteBitmap() { m_hPal = NULL; m_lpBmp = NULL; m_lpRotoZoom = NULL; m_lpCopy = NULL; m_bFirst = TRUE; }
	~CPaletteBitmap();
	void LoadBitmap(LPCSTR lpszResource);
	void Start(){m_dwStartTime = timeGetTime();}
	BOOL Animate();
	UINT GetWidth() const { return (m_lpBmp) ? m_lpBmp->bmiHeader.biWidth : 0; }
	UINT GetHeight() const { return (m_lpBmp) ? m_lpBmp->bmiHeader.biHeight : 0; }

protected:
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC *) { return TRUE; }
	
	afx_msg void OnLButtonDblClk(UINT, CPoint) { m_dwStartTime = timeGetTime(); } 
	DECLARE_MESSAGE_MAP()
};

static CPaletteBitmap *gpRotoZoom = NULL;
BEGIN_MESSAGE_MAP(CPaletteBitmap, CWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

void CPaletteBitmap::LoadBitmap(LPCSTR lpszResource)//--------------------------------------------------
{
	m_hPal = NULL;
	m_lpBmp = NULL;
	// True Color Mode ?
	HDC hdc = ::GetDC(AfxGetApp()->m_pMainWnd->m_hWnd);
	int nbits = GetDeviceCaps(hdc, BITSPIXEL);
	::ReleaseDC(AfxGetApp()->m_pMainWnd->m_hWnd, hdc);
	// Creating palette
	HINSTANCE hInstance = AfxGetInstanceHandle();
	HRSRC hrsrc = FindResource(hInstance, lpszResource, RT_BITMAP);
	HGLOBAL hglb = LoadResource(hInstance, hrsrc);
	LPBITMAPINFO p = (LPBITMAPINFO)LockResource(hglb);
	m_lpBmp = p;
	m_nRotoWidth = m_nRotoHeight = 0;
	if (p)
	{
		char pal_buf[sizeof(LOGPALETTE) + 512*sizeof(PALETTEENTRY)];
		LPLOGPALETTE pal = (LPLOGPALETTE)&pal_buf[0];
		for (int i=0; i<256; i++)
		{
			pal->palPalEntry[i].peRed = p->bmiColors[i].rgbRed;
			pal->palPalEntry[i].peGreen = p->bmiColors[i].rgbGreen;
			pal->palPalEntry[i].peBlue = p->bmiColors[i].rgbBlue;
			pal->palPalEntry[i].peFlags = 0;
		}
		pal->palVersion = 0x300;
		pal->palNumEntries = 256;
		if (nbits <= 8) m_hPal = CreatePalette(pal);
		if ((p->bmiHeader.biWidth == 256) && (p->bmiHeader.biHeight == 128))
		{
			UINT n;
			CRect rect;
			GetClientRect(&rect);
			m_nRotoWidth = (rect.Width() + 3) & ~3;
			m_nRotoHeight = rect.Height();
			if ((n = m_nRotoWidth - rect.Width()) > 0)
			{
				GetWindowRect(&rect);
				SetWindowPos(NULL, 0,0, rect.Width()+n, rect.Height(), SWP_NOMOVE | SWP_NOZORDER);
			}
			m_lpRotoZoom = new BYTE[m_nRotoWidth*m_nRotoHeight];
			if (m_lpRotoZoom)
			{
				memset(m_lpRotoZoom, 0, m_nRotoWidth*m_nRotoHeight);
				m_lpCopy = (LPBITMAPINFO)(new char [sizeof(BITMAPINFO) + 256*sizeof(RGBQUAD)]);
				if (m_lpCopy)
				{
					memcpy(m_lpCopy, p, sizeof(BITMAPINFO) + 256*sizeof(RGBQUAD));
					m_lpCopy->bmiHeader.biWidth = m_nRotoWidth;
					m_lpCopy->bmiHeader.biHeight = m_nRotoHeight;
					m_lpCopy->bmiHeader.biSizeImage = m_nRotoWidth * m_nRotoHeight;
				}
				gpRotoZoom = this;
			}

		}
	}
	m_dwStartTime = timeGetTime();
	m_dwFrameTime = 0;
}


CPaletteBitmap::~CPaletteBitmap()
//-------------------------------
{
	if (gpRotoZoom == this) gpRotoZoom = NULL;
	if (m_hPal)
	{
		DeleteObject(m_hPal);
		m_hPal = NULL;
	}
	if (m_lpRotoZoom)
	{
		delete m_lpRotoZoom;
		m_lpRotoZoom = NULL;
	}
	if (m_lpCopy)
	{
		delete m_lpCopy;
		m_lpCopy = NULL;
	}
}


void CPaletteBitmap::OnPaint()
//----------------------------
{
	CPaintDC dc(this);
	HDC hdc = dc.m_hDC;
	HPALETTE oldpal = NULL;
	LPBITMAPINFO lpdib;
	if (m_hPal)
	{
		oldpal = SelectPalette(hdc, m_hPal, FALSE);
		RealizePalette(hdc);
	}
	if ((lpdib = m_lpBmp) != NULL)
	{
		if ((m_lpRotoZoom) && (m_lpCopy))
		{
			lpdib = m_lpCopy;
			SetDIBitsToDevice(hdc,
						0,
						0,
						m_nRotoWidth,
						m_nRotoHeight,
						0,
						0,
						0,
						lpdib->bmiHeader.biHeight,
						m_lpRotoZoom,
						lpdib,
						DIB_RGB_COLORS);
		} else
		{
			CRect rect;
			GetClientRect(&rect);
			StretchDIBits(hdc,
						0,
						0,
						rect.right,
						rect.bottom,
						0,
						0,
						lpdib->bmiHeader.biWidth,
						lpdib->bmiHeader.biHeight,
						&lpdib->bmiColors[256],
						lpdib,
						DIB_RGB_COLORS,
						SRCCOPY);
		}
	}
	if (oldpal) SelectPalette(hdc, oldpal, FALSE);
	Animate();
}

////////////////////////////////////////////////////////////////////
// RotoZoomer

const int __SinusTable[256] =
{
	   0,   6,  12,  18,  25,  31,  37,  43,  49,  56,  62,  68,  74,  80,  86,  92,
	  97, 103, 109, 115, 120, 126, 131, 136, 142, 147, 152, 157, 162, 167, 171, 176,
	 181, 185, 189, 193, 197, 201, 205, 209, 212, 216, 219, 222, 225, 228, 231, 234,
	 236, 238, 241, 243, 244, 246, 248, 249, 251, 252, 253, 254, 254, 255, 255, 255,
	 256, 255, 255, 255, 254, 254, 253, 252, 251, 249, 248, 246, 244, 243, 241, 238,
	 236, 234, 231, 228, 225, 222, 219, 216, 212, 209, 205, 201, 197, 193, 189, 185,
	 181, 176, 171, 167, 162, 157, 152, 147, 142, 136, 131, 126, 120, 115, 109, 103,
	  97,  92,  86,  80,  74,  68,  62,  56,  49,  43,  37,  31,  25,  18,  12,   6,
	   0,  -6, -12, -18, -25, -31, -37, -43, -49, -56, -62, -68, -74, -80, -86, -92,
	 -97,-103,-109,-115,-120,-126,-131,-136,-142,-147,-152,-157,-162,-167,-171,-176,
	-181,-185,-189,-193,-197,-201,-205,-209,-212,-216,-219,-222,-225,-228,-231,-234,
	-236,-238,-241,-243,-244,-246,-248,-249,-251,-252,-253,-254,-254,-255,-255,-255,
	-256,-255,-255,-255,-254,-254,-253,-252,-251,-249,-248,-246,-244,-243,-241,-238,
	-236,-234,-231,-228,-225,-222,-219,-216,-212,-209,-205,-201,-197,-193,-189,-185,
	-181,-176,-171,-167,-162,-157,-152,-147,-142,-136,-131,-126,-120,-115,-109,-103,
	 -97, -92, -86, -80, -74, -68, -62, -56, -49, -43, -37, -31, -25, -18, -12,  -6
};

#define Sinus(x)	__SinusTable[(x)&0xFF]
#define Cosinus(x)	__SinusTable[((x)+0x40)&0xFF]

#define PI	3.14159265358979323f
BOOL CPaletteBitmap::Animate()
//----------------------------
{	
	//included random hacking by rewbs to get funny animation.
	LPBYTE dest, src;
	DWORD t = (timeGetTime() - m_dwStartTime) / 10;
	LONG Dist, Phi, srcx, srcy, spdx, spdy, sizex, sizey;
	bool dir;

	if ((!m_lpRotoZoom) || (!m_lpBmp) || (!m_nRotoWidth) || (!m_nRotoHeight)) return FALSE;
	Sleep(2); 	//give away some CPU

	if (t > 256)
		m_bFirst = FALSE;

	dir = (t/256) % 2; //change dir every 256 t
	t = t%256;
	if (!dir) t = (256-t);
	
	sizex = m_nRotoWidth;
	sizey = m_nRotoHeight;
	m_dwFrameTime = t;
	src = (LPBYTE)&m_lpBmp->bmiColors[256];
	dest = m_lpRotoZoom;
	Dist = t;
	Phi = t;
	spdx = 70000 + Sinus(Phi) * 10000 / 256;
	spdy = 0;
	//spdx =(Cosinus(Phi)+Sinus(Phi<<2))*(Dist<<9)/sizex;
	//spdy =(Sinus(Phi)+Cosinus(Phi>>2))*(Dist<<9)/sizey;
	srcx = 0x800000 - ((spdx * sizex) >> 1) + (spdy * sizey);	
	srcy = 0x800000 - ((spdy * sizex) >> 1) + (spdx * sizey);	
	for (UINT y=sizey; y; y--)
	{
		UINT oldx = srcx, oldy = srcy;
		for (UINT x=sizex; x; x--)
		{
			srcx += spdx;
			srcy += spdy;
			*dest++ = src[((srcy & 0x7F0000) >> 8) | ((srcx & 0xFF0000) >> 16)];
		}
		srcx=oldx-spdy;
		srcy=oldy+spdx;
	}
	InvalidateRect(NULL, FALSE);
	UpdateWindow();
	return TRUE;
}

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
	BOOL OnInitDialog(void);
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	//{{AFX_MSG(CAboutDlg)
	afx_msg void OnWebbutton();
	afx_msg void OnWebbutton2();
	afx_msg void OnWebbutton3();
	afx_msg void OnWebbutton4();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CRichEditCtrl m_REAbout;
	CPaletteBitmap m_bmp;


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
	DDX_Control(pDX, IDC_RICHEDIT23, m_REAbout);
}

BOOL CAboutDlg::OnInitDialog()
{

	CDialog::OnInitDialog();

	HGLOBAL hResourceLoaded;  // handle to loaded resource

    HRSRC   hRes;              // handle/ptr to res. info.

    char    *lpResLock;        // pointer to resource data

    hRes = FindResource(NULL, 
		MAKEINTRESOURCE(IDR_TXT1), 
                        "txt"
                    );

    hResourceLoaded = LoadResource(NULL, hRes);
    lpResLock = (char *) LockResource(hResourceLoaded);

	DWORD dwSize = SizeofResource(NULL, hRes);

	lpResLock[dwSize]='\0';

	m_REAbout.SetSel(0,-1);
	m_REAbout.ReplaceSel(lpResLock,0);
 
	m_bmp.SubclassDlgItem(IDC_BITMAP111, this);
	m_bmp.LoadBitmap(MAKEINTRESOURCE(IDB_MPTRACK));

	return true;
}


BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_BN_CLICKED(IDC_WEBBUTTON, OnWebbutton)
	ON_BN_CLICKED(IDC_WEBBUTTON2, OnWebbutton2)
	ON_BN_CLICKED(IDC_WEBBUTTON3, OnWebbutton3)
	ON_BN_CLICKED(IDC_WEBBUTTON4, OnWebbutton4)
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
	ShellExecute(AfxGetMainWnd()->GetSafeHwnd(),NULL,"http://www.flat2d.com",NULL,NULL,0);
}

void CAboutDlg::OnWebbutton4()
{
	ShellExecute(AfxGetMainWnd()->GetSafeHwnd(),NULL,"http://ddoodd.ddo.jp/delta/soft.html",NULL,NULL,0);
}


bool CEasyToonApp::GetDem()
{
	return m_demarrage;
}

void CEasyToonApp::SetDem(bool Demarrage)
{
	m_demarrage=Demarrage;
}




