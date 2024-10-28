#include "PreCompile.h"
#include <ContentsProject/EduContentsCore.h>

#include <EngineCore/EngineAPICore.h>

#pragma comment (lib, "EngineCore.lib")
#pragma comment (lib, "ContentsProject.lib")


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	// 우리의 컨텐츠를 넣기 위해 EngineStart전에 컨텐츠 코어 생성 후 User로 넣어줌
	EduContentsCore User;
	return UEngineAPICore::EngineStart(hInstance, &User);
}