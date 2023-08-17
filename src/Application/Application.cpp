
#include"../BaseIncluder.h"
#include"Application.h"
#include"../FrameList/IntroFrame.h"
#include"../FrameList/TitleFrame.h"

void Application::Init()
{
	InitWindow();
	
	InitDirectX();

	frameList.SetFrame<IntroFrame>();
	frameList.SetFrame<TitleFrame>();
}

void Application::Release()
{	
	ChD3D11::Shader11().Release();

	d3d11.Release();

	windows.Release();

	windClass.Release();
}

int Application::Update()
{
	Init();

	while (windows.IsUpdate())
	{
		if (windows.IsPushKey(VK_ESCAPE))
		{
			PostQuitMessage(0);
			continue;
		}

		frameList.Update();

		ChD3D11::Shader11().DrawStart();


		ChD3D11::Shader11().DrawEnd();

	}

	Release();

	return (int)windows.GetReturnMassage();
}

void Application::InitWindow()
{
	auto&& hInstance = ChWin::GetInstanceHandle();
	auto&& screenSize = ChWin::GetScreenSize();

	screenSize.x -= 10;
	screenSize.y -= 10;

#if true

	windClass.Init();
	windClass.SetInstance(hInstance);

	windClass.RegistClass(L"ChGameClass");

	windows.Init(L"The Custom Fighter", windClass.GetWindClassName(), screenSize, ChINTPOINT(5, 5), hInstance, true);

#else

	windClass.Init();

	{
		ChWin::WindClassStyle style;
		style.AddSaveBits();

		windClass.SetStyle(&style);
		windClass.RegistClass(L"ChEditor");
	}


	ChWin::WindCreater creater = ChWin::WindCreater(hInstance);

	creater.SetInitPosition(5, 5);
	creater.SetInitSize(screenSize.w, screenSize.h);

	{
		ChWin::WindStyle style;
		style.AddOverlappedWindow();
		style.AddClipChildren();
		style.AddSizeBox();
		style.AddVisible();

		creater.SetWindStyle(&style);
	}

	windows.Init(creater, L"ChFileEditorFor3D", windClass.GetWindClassName(), hInstance, true);

#endif
}

void Application::InitDirectX()
{
	if (!windows.IsInit())return;

	d3d11.Init(windows.GethWnd(), false, GAME_WINDOW_WITDH_LONG, GAME_WINDOW_HEIGHT_LONG);

	if (!d3d11.IsInit())return;

	ChD3D11::Shader11().Init(d3d11, GAME_WINDOW_WITDH, GAME_WINDOW_HEIGHT);

	ChD3D11::Shader11().SetBackColor(ChVec4(0.0f, 0.0f, 1.0f, 1.0f));
}