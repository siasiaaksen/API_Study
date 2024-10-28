#pragma once
#include <Windows.h>

// 이녀석이 이미지 역할을 대신할 겁니다.
// 이녀석은 당연히 로드도 됩니다.

// 설명 : API 이번 랜더링 구조의 핵심 클래스
// 
class UEngineWinImage
{
public:
	// constrcuter destructer
	UEngineWinImage();
	~UEngineWinImage();

	// delete Function
	UEngineWinImage(const UEngineWinImage& _Other) = delete;
	UEngineWinImage(UEngineWinImage&& _Other) noexcept = delete;
	UEngineWinImage& operator=(const UEngineWinImage& _Other) = delete;
	UEngineWinImage& operator=(UEngineWinImage&& _Other) noexcept = delete;

	// void Load(std::string_view _Path);
	HDC GetDC()
	{
		return ImageDC;
	}
	
	// 이미 만들어진 DC를 통해서 이미지를 만드는 타입
	void Create(HDC _DC)
	{
		ImageDC = _DC;
	}

	void Create(FVector2D _Scale);


protected:

private:
	// BMP 이미지 파일 그 자체에요
	// FVector2D Size;
	HDC ImageDC = nullptr;
	HBITMAP BitMap = nullptr;

};

