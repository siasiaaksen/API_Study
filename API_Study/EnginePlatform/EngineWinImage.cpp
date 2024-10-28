#include "PreCompile.h"
#include "EngineWinImage.h"

UEngineWinImage::UEngineWinImage()
{
}

UEngineWinImage::~UEngineWinImage()
{
}

void UEngineWinImage::Create(FVector2D _Scale)
{
	// HDC 아무것도 없곳에서
	// HDC 넣어달라고 하는데 window HDC
	// int X; 만들려는 빈 이미지의 x크기
	// int Y; 만들려는 빈 이미지의 y크기

	// 도화지 1280, 720
	HBITMAP NewBitmap = static_cast<HBITMAP>(CreateCompatibleBitmap(nullptr, _Scale.iX(), _Scale.iY()));

	// 이미지 그자체
	// 이미지를 수정할수 있는 권한 HDC
	// 이미지의 데이터 권한 HBITMAP
	// HDC<=>HBITMAP 이 합쳐져서 이미지와 이미지를 수정하는 권한이 연결되는 개념

	// 붓
	HDC NewImageDC = CreateCompatibleDC(nullptr);

	// 윈도우가 정하기를 붓과 도화지를 한쌍으로 안엮으면 못그림.
	// 붓을 만들기만 해도  1, 1 이미지랑 연결해 놓는다. window 

	// 붓과 도화지를 연결하는 작업을 거쳐야 한다.
	HBITMAP OldBitMap = static_cast<HBITMAP>(SelectObject(NewImageDC, NewBitmap));
	// 가만히 내버려두면 leck
	DeleteObject(OldBitMap);


	BitMap = NewBitmap;
	ImageDC = NewImageDC;


}