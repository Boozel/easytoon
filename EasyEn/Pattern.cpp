#include "stdafx.h"
#include "Pattern.h"
#include "Utils.h"


CBitmap *Pattern::_pattern;
CBitmap *Pattern::_patterns;
CBitmap *Pattern::_patternsMenu;

bool Pattern::_isInitialized;
int Pattern::_rowsNumber;
int Pattern::_colsNumber;
int Pattern::_rowPos;

Pattern::Pattern()
{
	
	
}

Pattern::~Pattern()
{
	
}

//Loop forward through the available patterns.
void Pattern::NextPattern()
{
	if(!Pattern::_isInitialized)
	{
		throw ("Pattern has not been initialized !");
	}

	_rowPos++;

	if(Pattern::_rowPos >= Pattern::_rowsNumber)
	{
		Pattern::_rowPos = 0;
	}
}

//Loop backward through the available patterns.
void Pattern::PreviousPattern()
{
	if(!Pattern::_isInitialized)
	{
		throw ("Pattern has not been initialized !");
	}

	_rowPos--;

	if(Pattern::_rowPos < 0 )
	{
		Pattern::_rowPos = Pattern::_rowsNumber - 1;
	}
}

//Get the current pattern according to it's column position.
 CBitmap* Pattern::GetPattern(int patternCol)
{
	
	if(!Pattern::_isInitialized)
	{
		throw ("Pattern has not been initialized !");
	}

	if( (patternCol < 0) || (patternCol > _colsNumber))
	{
		throw ("Numbers of rows or numbers of columns provided are incorrect !");
	}

	return &_patterns[(_rowPos*_colsNumber)+patternCol];
}

 //Get the bitmap that will be displayed in the menu
 CBitmap* Pattern::GetPatternForMenu()
{
	if(!_isInitialized)
	{
		throw ("Pattern has not been initialized !");
	}

	//Here we have to supply a copy of the bitmap because the bitmap is disposed each time
	//we change the bitmap associated to the brush toolbar.
	return Utils::CopyBitmap(&_patternsMenu[_rowPos]);
}

 //Initialize the class
void Pattern::InitializePattern(int resourceId)
{
	if(_isInitialized)
	{
		throw ("Pattern cannot be initialized twice !");
	}

	_pattern= new CBitmap();

	if(!_pattern->LoadBitmapA(resourceId))
	{
		throw ("Cannot load resource !");
	}
	
	_rowPos=0;

	BITMAP bmp;

	//Unable to get the dimensions of the bitmap using LoadBitmapA. 
	//According to Microsoft, bitmap dimensions should be set using SetDimensions
	//To retrieve the dimensions, we must retrieve a BITMAP object first.
	if(_pattern->GetBitmap(&bmp) == 0)
	{
		throw ("Unable to get the bitmap associated to the resource !");
	}

	_rowsNumber = bmp.bmHeight / PATTERN_SIZE;
	_colsNumber = bmp.bmWidth / PATTERN_SIZE;

	_patternsMenu = new CBitmap[_rowsNumber];
	_patterns = new CBitmap[_rowsNumber * _colsNumber];

	CDC srcDC;
	CDC dstDC;

	srcDC.CreateCompatibleDC(NULL);
	dstDC.CreateCompatibleDC(NULL);
	
	//-------- Re-initialization of various bit maps
	DWORD* pBmpSrc = new DWORD[ PATTERN_SIZE * PATTERN_SIZE ];
	memset ( pBmpSrc, 0xff,  PATTERN_SIZE * PATTERN_SIZE * 4 );

	for (int row = 0; row < _rowsNumber ; row++)
	{
		_patternsMenu[row].CreateBitmap(16*_colsNumber, 15, 1,  1, pBmpSrc);

		for (int col = 0; col <_colsNumber ; col++)
		{
			int index = (row*_colsNumber)+col;

			_patterns[index].CreateBitmap(PATTERN_SIZE, PATTERN_SIZE, 1,  1, pBmpSrc);
			
			srcDC.SelectObject(_pattern);
			dstDC.SelectObject(_patterns[index]);
			
			dstDC.BitBlt(0,0 , PATTERN_SIZE, PATTERN_SIZE, &srcDC, col*PATTERN_SIZE, row*PATTERN_SIZE, SRCCOPY);
		
			
			dstDC.SelectObject(_patternsMenu[row]);

			CBrush brush(&_patterns[index]);
			dstDC.SelectObject(&brush);
			dstDC.Rectangle( col*16, 0, (col+1)*16, 15 );
		}

		
	}

	dstDC.RestoreDC( -1 );
	srcDC.RestoreDC( -1 );	
	
	_isInitialized = true;
}

