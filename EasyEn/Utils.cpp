#include "stdafx.h"
#include "Utils.h"
#include <atlimage.h>
#include <Gdiplusimaging.h>

static int counter=0;
CBitmap* Utils::CopyBitmap(CBitmap* bmp)
{
	CBitmap* aMemBtmp; 
	BITMAP srcBmp;
	BYTE * aBmpBytes;
	BYTE * aMemBtmpBytes;

	try
	{
		bmp->GetBitmap(&srcBmp);
		bmp->SetBitmapDimension(srcBmp.bmWidth,srcBmp.bmHeight);

		int	 wFrameSize = (bmp->GetBitmapDimension().cy * srcBmp.bmWidthBytes * bmp->GetBitmapDimension().cx * srcBmp.bmBitsPixel ) / 8;

		aBmpBytes = new BYTE[wFrameSize];
		aMemBtmpBytes = new BYTE[wFrameSize];
		aMemBtmp = new CBitmap();

		aMemBtmp->CreateBitmap(bmp->GetBitmapDimension().cx,bmp->GetBitmapDimension().cy,srcBmp.bmPlanes,srcBmp.bmBitsPixel,aMemBtmpBytes);
		bmp->GetBitmapBits(wFrameSize,aBmpBytes);

		aMemBtmp->SetBitmapBits(wFrameSize,aBmpBytes);
		aMemBtmp->SetBitmapDimension(bmp->GetBitmapDimension().cx,bmp->GetBitmapDimension().cy);

		if(aBmpBytes)
			delete[] aBmpBytes;
		if(aMemBtmpBytes)
			delete[] aMemBtmpBytes;
	}
	catch(int nError )
	{
		if(aBmpBytes)
			delete[] aBmpBytes;
		if(aMemBtmpBytes)
			delete[] aMemBtmpBytes;

		if(aMemBtmp)
			delete aMemBtmp;
	}
	

	return aMemBtmp;
}

CBitmap* Utils::ResizeBitmap(CBitmap *bmp, int x, int y)
{
	CDC TempDc;
	CDC ResizeDc;
	
	CBitmap* ResizeBmp= new CBitmap();
			
	WORD	 wFrameSize = y* (x / 8 + (x & 15 ? 2 : 0) );
	BYTE * aBmpBytes = new BYTE[wFrameSize];
	
	ResizeDc.CreateCompatibleDC(NULL);
	TempDc.CreateCompatibleDC(NULL);

	TempDc.SelectObject(bmp);

	ResizeBmp->CreateBitmap(x,y,1,1,aBmpBytes);
	ResizeDc.SelectObject(ResizeBmp);
	
	ResizeDc.StretchBlt(0,0,x,y,&TempDc,0,0,bmp->GetBitmapDimension().cx-1,bmp->GetBitmapDimension().cy-1, SRCCOPY   );
	
	ResizeDc.SelectStockObject(NULL_BRUSH);
	ResizeDc.Rectangle(0,0,x,y);

	delete bmp;
	delete[] aBmpBytes;

	return ResizeBmp;
}

void Utils::SaveBitmapToFile(CBitmap * bmp)
{
	CImage image;
	CString Path;
	
	Path.Format("C:\\temp\\test%d.bmp", counter);
    image.Attach(*bmp);

    image.Save(Path, Gdiplus::ImageFormatBMP);
	image.Detach();
	counter++;
}