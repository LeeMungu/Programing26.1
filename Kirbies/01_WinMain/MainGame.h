#pragma once

/*
1. �ִϸ��̼� 
2. �̺�Ʈ ����� ��
*/

class Image;

class MainGame
{
	Image* mBackBuffer;	//�ĸ����(�ǵ�������)
	Image* mScaleBuffer;
	Image* mMapBuffer;
public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);
	void mapRender(HDC map);

	
	void RenderTime(HDC hdc);

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};

