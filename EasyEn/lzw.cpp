////////////////////////////////////////////////////////////////////////////
//
//	LZW���k �G���R�[�_���f�R�[�_ (GIF�`���Ή�)
//
//	1998 (C) Keijiro Takahashi (keijiro@din.or.jp)
//
#include "stdafx.h"
#include "lzw.h"


////////////////////////////////////////////////////////////////////////////
//
//	�G���R�[�_
//

// �R���X�g���N�^
CLzwEncoder::CLzwEncoder()
{
	m_pwStrTbl		= new WORD[ (1 << LZW_MAXBITWIDTH) * 2 ];
	m_pwSearchTbl	= new WORD[ (1 << LZW_MAXBITWIDTH) * 2 ];
}
// �f�X�g���N�^
CLzwEncoder::~CLzwEncoder()
{
	delete m_pwStrTbl;
	delete m_pwSearchTbl;
}

//
//	�X�g�����O�E�e�[�u���֘A
//
//	�X�g�����O�E�e�[�u��������
void CLzwEncoder::InitStrTbl ()
{
	for ( int i=0 ; i < (1 << LZW_MAXBITWIDTH) * 2 ; i++ ) m_pwSearchTbl[i] = LZW_NULL;
	for ( int i=0 ; i < (m_wEOI + 1) * 2 ; i+=2 )
	{
		m_pwStrTbl [i  ] = i;
		m_pwStrTbl [i+1] = LZW_NULL;
	}
	m_nStrTblCtr = m_wEOI + 1;
}
// �X�g�����O�̓o�^
void CLzwEncoder::AddString ( WORD w1, WORD w2 )
{
	m_pwStrTbl [ m_nStrTblCtr*2     ] = w1;
	m_pwStrTbl [ m_nStrTblCtr*2 + 1 ] = w2;
	m_pwSearchTbl [ w1*2 + w2 ] = m_nStrTblCtr;
	if ( ++m_nStrTblCtr > 1 << m_nBitWidth ) 
	{
		if ( m_nBitWidth < LZW_MAXBITWIDTH )
		{
			m_nBitWidth++;
		}
		else
		{
			Write ( m_wCC );
			m_nStrTblCtr = m_wEOI + 1;
			m_nBitWidth  = m_nCodeSize + 1;
			for ( int i=0 ; i < (1 << LZW_MAXBITWIDTH) * 2 ; i++ ) m_pwSearchTbl[i] = LZW_NULL;
		}
	}
}
//	�X�g�����O�̌���
WORD CLzwEncoder::SearchString ( WORD w1, WORD w2 )
{
	return m_pwSearchTbl [ w1*2 + w2 ];
}

//
//	�o�b�t�@����
//
// ������
void CLzwEncoder::InitBuffer( BYTE* pSrc ,BYTE* pOut )
{
	m_pSrcBuf	= pSrc;
	m_pRead		= pSrc;
	m_pOutBuf	= pOut;
	m_pWrite	= pOut;
	m_nReadBit	= 0;
	m_nWriteBit	= 8;
	*m_pWrite	= 0;
}
// �ǂݍ���
BYTE CLzwEncoder::Read ()
{
	BYTE rval = (*m_pRead >> (7 - m_nReadBit)) & 1;
	if ( --m_nWidthCtr == 0 )
	{
		m_nReadBit = 0;
		m_pRead += (m_nImageWidth & 15) > 8 ? 1 : (m_nImageWidth & 15) ? 2 : 1;
		m_nWidthCtr = m_nImageWidth;
	}
	else if ( ++m_nReadBit == 8 )
	{
		m_nReadBit = 0;
		m_pRead++;
	}
	return rval;
}
// �����o��
void CLzwEncoder::Write ( WORD w )
{
	int nBit = m_nBitWidth;
	while ( nBit > m_nWriteBit )
	{
		*m_pWrite |=  w << (8 - m_nWriteBit);
		w >>= m_nWriteBit;
		*++m_pWrite = 0;
		nBit -= m_nWriteBit;
		m_nWriteBit = 8;
	}
	*m_pWrite |=  w << (8 - m_nWriteBit);
	m_nWriteBit -= nBit;
}

//
// lzw�G���R�[�f�B���O
//
int CLzwEncoder::Encode ( BYTE* pSrc, int nLength, int nImageWidth, int nCodeSize, BYTE* pOut )
{
	// ������
	m_nCodeSize		= (nCodeSize == 1) ? 2 : nCodeSize;
	m_nBitWidth		= m_nCodeSize + 1;
	m_wCC			= 1 << m_nCodeSize;
	m_wEOI			= m_wCC + 1;
	m_nImageWidth	= nImageWidth;
	m_nWidthCtr		= nImageWidth;
	// �o�b�t�@������
	InitBuffer ( pSrc, pOut );
	// �e�[�u��������
	InitStrTbl ();

	// lzw���C��
	WORD wPrev = Read();
	Write ( m_wCC );
	for ( int i=0 ; i < nLength-1 ; i++ )
	{
		WORD wInp  = Read();
		WORD wCode = SearchString ( wPrev, wInp );
		if ( wCode != LZW_NULL )
		{
			wPrev = wCode;
		}
		else
		{
			Write ( wPrev );
			AddString ( wPrev, wInp );
			wPrev = wInp;
		}
	}
	Write ( wPrev );
	Write ( m_wEOI );
	return m_pWrite - m_pOutBuf + 1;
}



////////////////////////////////////////////////////////////////////////////
//
//	�f�R�[�_
//

// �R���X�g���N�^
CLzwDecoder::CLzwDecoder()
{
	m_pwStrTblPrefix	= new WORD [ 1 << LZW_MAXBITWIDTH ];
	m_pbStrTblSuffix	= new BYTE [ 1 << LZW_MAXBITWIDTH ];
}
// �f�X�g���N�^
CLzwDecoder::~CLzwDecoder()
{
	delete m_pwStrTblPrefix;
	delete m_pbStrTblSuffix;
}

//
//	�X�g�����O�E�e�[�u���֘A
//
//	�X�g�����O�E�e�[�u��������
void CLzwDecoder::InitStrTbl ()
{
	for ( int i=0 ; i <= m_wEOI ; i++ )
	{
		m_pwStrTblPrefix [i] = LZW_NULL;
		m_pbStrTblSuffix [i] = i;
	}
	m_nStrTblCtr = m_wEOI + 1;
}
// �X�g�����O�̓o�^
void CLzwDecoder::AddString ( WORD w, BYTE b )
{
	m_pwStrTblPrefix [m_nStrTblCtr] = w;
	m_pbStrTblSuffix [m_nStrTblCtr] = b;
	m_nStrTblCtr++;
}
// �X�g�����O�̎擾
BYTE CLzwDecoder::GetString ( WORD wIndex, WORD* w )
{
	*w = m_pwStrTblPrefix [wIndex];
	return m_pbStrTblSuffix [wIndex];
}

//
//	�o�b�t�@����
//
// ������
void CLzwDecoder::InitBuffer( BYTE* pSrc ,BYTE* pOut )
{
	m_pSrcBuf	= pSrc;
	m_pRead		= pSrc;
	m_pOutBuf	= pOut;
	m_pWrite	= pOut;
	m_nReadBit	= 8;
	m_nWriteBit	= 0;
	*m_pWrite	= 0;
}
// �ǂݍ���
WORD CLzwDecoder::Read()
{
	WORD rval = 0;
	int nBit = m_nBitWidth;
	while ( nBit > m_nReadBit )
	{
		rval |= ( *m_pRead >> (8 - m_nReadBit) ) << (m_nBitWidth - nBit);
		nBit -= m_nReadBit;
		m_pRead ++;
		m_nReadBit = 8;
	}
	rval |= ( (*m_pRead >> (8 - m_nReadBit) ) & ((1 << nBit) - 1) ) << (m_nBitWidth - nBit);
	m_nReadBit -= nBit;
	return rval;
}
// �����o��
void CLzwDecoder::Write ( BYTE b )
{
	if ( m_nWidthCtr == 0 )
	{
		m_nWriteBit = 0;
		*( m_pWrite += (m_nImageWidth & 15) > 8 ? 1 : (m_nImageWidth & 15) ? 2 : 1 ) = 0;
		m_nWidthCtr = m_nImageWidth;
	}
	else if ( m_nWriteBit == 8 )
	{
		m_nWriteBit = 0;
		*++m_pWrite = 0;
	}
	*m_pWrite |= b << (7 - m_nWriteBit++);
	m_nWidthCtr--;
}

//
// Lzw�f�R�[�f�B���O
//
int	CLzwDecoder::Decode ( BYTE* pSrc, int nImageWidth, int nCodeSize, BYTE* pOut )
{
	// ������
	m_nCodeSize		= (nCodeSize == 1) ? 2 : nCodeSize;
	m_nBitWidth		= m_nCodeSize + 1;
	m_wCC			= 1 << m_nCodeSize;
	m_wEOI			= m_wCC + 1;
	m_nImageWidth	= nImageWidth;
	m_nWidthCtr		= nImageWidth;
	// �o�b�t�@������
	InitBuffer ( pSrc, pOut );
	// �e�[�u��������
	InitStrTbl ();

	// ���C��
	WORD	wPrev = LZW_NULL;
	WORD	wInp;
	while ( ( wInp = Read() ) != m_wEOI )
	{
		if ( wInp == m_wCC )
		{
			m_nStrTblCtr = m_wEOI + 1;
			m_nBitWidth	 = m_nCodeSize + 1;
			wPrev		 = LZW_NULL;
		}
		else
		{
			BYTE	abTmp[1024]; // ���[�h���ɗ�����悤�Ȃ�R�R��傫������΂Ȃ�Ƃ��Ȃ邩��
			int		nTmpCtr = 0;
			WORD	wPrefix;

			if ( wInp < m_nStrTblCtr )
			{
				wPrefix = wInp;
				while ( wPrefix != LZW_NULL ) abTmp[nTmpCtr++] = GetString ( wPrefix, &wPrefix );
				for ( int i=nTmpCtr-1 ; i>=0 ; i-- ) Write ( abTmp[i] );
				if ( wPrev != LZW_NULL ) AddString ( wPrev, abTmp[nTmpCtr-1] );
			}
			else
			{
				wPrefix = wPrev;
				while ( wPrefix != LZW_NULL ) abTmp[nTmpCtr++] = GetString ( wPrefix, &wPrefix );
				for ( int i=nTmpCtr-1 ; i>=0 ; i-- ) Write ( abTmp[i] );
				Write ( abTmp[nTmpCtr-1] );
				AddString ( wPrev, abTmp[nTmpCtr-1] );
			}
			wPrev = wInp;
			if ( m_nStrTblCtr == 1 << m_nBitWidth && m_nBitWidth < LZW_MAXBITWIDTH ) m_nBitWidth++;
		}
	}
	return m_pWrite - m_pOutBuf;
}


