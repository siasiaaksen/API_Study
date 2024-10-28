#include "PreCompile.h"
#include "EngineWindow.h"
#include <EngineBase/EngineDebug.h>


HINSTANCE UEngineWindow::hInstance = nullptr;
std::map<std::string, WNDCLASSEXA> UEngineWindow::WindowClasses;
int WindowCount = 0;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
        EndPaint(hWnd, &ps);
    }
    break;
    //case WM_SIZING:
    //{
    //    int a = 0;
    //}
    break;
    case WM_DESTROY:
        --WindowCount;
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


void UEngineWindow::EngineWindowInit(HINSTANCE _Instance)
{
    hInstance = _Instance;

    // 어차피 무조건 해줘야 한다면 여기서 하려고 한것.
    // 디폴트 윈도우 클래스 등록
    WNDCLASSEXA wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = nullptr;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = "Default";
    wcex.hIconSm = nullptr;
    CreateWindowClass(wcex);
}

int UEngineWindow::WindowMessageLoop(EngineDelegate _StartFunction, EngineDelegate _FrameFunction)
{
    // 단축키 인데 게임에서는 사용하지 않음
    // HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT2));
    MSG msg = MSG();

    // 기본 메시지 루프입니다:
    // 메세지 루프가 getMessage라면 게임의 루프를 돌릴수 없다.
    // 동기 함수이기 때문이다.
    // 동기 자신의 목적이 끝날때까지 정지하는 함수.

    // GetMessage
    // 메세지가 없다 => 영원히 기다림
    // 메세지가 있다 => 처리하고 리턴

    // 처리하고 리턴
    // 메세지가 없다 => 리턴
    // 메세지가 있다 => 처리하고 리턴

    // WindowCount
    // 떠있는 윈도우의 갯수

    // 프로그램 시작하고 딱 1번 해야할일 있다면 여기에 넣어라.
    // 최대한 예외처리 해주는게 좋다.
    if (true == _StartFunction.IsBind())
    {
        _StartFunction();
    }

    while (0 != WindowCount)
    {
        // if (!TranslateAccelerator(msg.hwnd, nullptr, &msg))
        // => 윈도우 단축키 자체를 사용하지 않을 것이므로 그냥 무시
        
        // PM_REMOVE == 내가 처리할때 지금까지 쌓인 메세지 다지워.
        if(0 != PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // 메세지가 없는 시간에 내 게임을 돌리는거야.
        // 메세지 처리하고 나서 내 게임엔진을 돌린다.
        if (true == _FrameFunction.IsBind())
        {
            _FrameFunction();
        }
    }

    return (int)msg.wParam;
}

void UEngineWindow::CreateWindowClass(const WNDCLASSEXA& _Class)
{
    std::map<std::string, WNDCLASSEXA>::iterator EndIter = WindowClasses.end();
    std::map<std::string, WNDCLASSEXA>::iterator FindIter = WindowClasses.find(std::string(_Class.lpszClassName));

    if (EndIter != FindIter)
    {
        // std::string ErrorText = "같은 이름의 윈도우 클래스를 2번 등록했습니다" + std::string(_Class.lpszClassName);

        // std::string 내부에 들고 있는 맴버변수
        // => std::string => std::vector<char>
        // std::vector<char> char* = new char[100];
        // ErrorText const char* 리턴해주는 함수가 c_str()
        // const char* Text = ErrorText.c_str();
        MSGASSERT(std::string(_Class.lpszClassName) + " 같은 이름의 윈도우 클래스를 2번 등록했습니다");
        return;
    }

    RegisterClassExA(&_Class);

    WindowClasses.insert(std::pair{ _Class.lpszClassName, _Class });
}

UEngineWindow::UEngineWindow() 
{
}

UEngineWindow::~UEngineWindow()
{
    if (nullptr != WindowImage)
    {
        delete WindowImage;
        WindowImage = nullptr;
    }
}

void UEngineWindow::Create(std::string_view _TitleName, std::string_view _ClassName)
{
    if (false == WindowClasses.contains(_ClassName.data()))
    {
        MSGASSERT(std::string(_ClassName) + " 등록하지 않은 클래스로 윈도우창을 만들려고 했습니다");
        return;
    }

    WindowHandle = CreateWindowA(_ClassName.data(), _TitleName.data(), WS_OVERLAPPEDWINDOW,
        0, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (nullptr == WindowHandle)
    {
        MSGASSERT(std::string(_TitleName) + " 윈도우 생성에 실패했습니다.");
        return;
    }

    // 윈도우가 만들어지면 hdc를 여기서 얻어올 겁니다.
    HDC WindowMainDC = GetDC(WindowHandle);

    // BackBufferImage.Copy({ 100,100 }, {50, 50}, PlayerImage);

    WindowImage = new UEngineWinImage();

    // 이건 만든다는 개념이 아니다.
    WindowImage->Create(WindowMainDC);
}

void UEngineWindow::Open(std::string_view _TitleName /*= "Window"*/)
{
    // 어 window 안만들고 띄우려고 하네?
    if (0 == WindowHandle)
    {
        // 만들어
        Create(_TitleName);
    }

    if (0 == WindowHandle)
    {
        return;
    }

	// 단순히 윈도우창을 보여주는 것만이 아니라
    // 인자를 통해 보여줄지 말지 결정해줌
	// ShowWindow(WindowHandle, SW_HIDE);
	ShowWindow(WindowHandle, SW_SHOW);
    UpdateWindow(WindowHandle);
    ++WindowCount;
}

void UEngineWindow::SetWindowPosAndScale(FVector2D _Pos, FVector2D _Scale)
{
    // 이 함수를 여러번 호출하면
    //if (nullptr != BackBufferImage)
    //{
    //    // 기존 백버퍼는 지워버리고
    //    delete BackBufferImage;
    //    BackBufferImage = nullptr;
    //}

    // 다시 new하고 create
    //BackBufferImage = new UEngineWinImage();
    //BackBufferImage->Create(_Scale);

    RECT Rc = { 0, 0, _Scale.iX(), _Scale.iY() };

    // 이게 그 계산해주는 함수이다.
    // 타이틀바 크기까지 합쳐진 크기로 준다.
    // 윈도우 입장에서
    // 현재 윈도우의 스타일을 넣어줘야 한다.
    // 그러면 또 이녀석은 
    // 윈도우에서 가져야할 위치를 포함한 크기를 주게 된다.
    AdjustWindowRect(&Rc, WS_OVERLAPPEDWINDOW, FALSE);
    
    // 창에 대한 핸들(, z순서로 배치된 창 앞에 오는 창에 대한 핸들: 그냥 nullptr)
    // 창 왼쪽의 x위치, 창 왼쪽의 y위치
    // 창의 너비(픽셀), 창의 높이(픽셀)
    // (창 크기 조정 및 위치 지정 플래그)
    ::SetWindowPos(WindowHandle, nullptr, _Pos.iX(), _Pos.iY(), Rc.right - Rc.left, Rc.bottom - Rc.top, SWP_NOZORDER);
}