#pragma once

class Application
{
public:

	enum class FrameNameList
	{
		Intro,
		Title,
		Battle,
		Assemble
	};

	void Init();

	void Release();

	int Update();

private:

	void InitWindow();

	void InitDirectX();

	ChWin::WindClassObject windClass;
	ChSystem::Windows windows;
	ChD3D11::DirectX3D11 d3d11;

	ChCpp::FrameList frameList;

};