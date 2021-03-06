#pragma once
class Scene
{
protected:
	bool mIsGameOver;
	bool mIsGameClear;
	
	bool mIsSpecial;

	//카메라 렉트
	RECT mCameraRect;

public:
	Scene();
	virtual void Init() = 0;
	virtual void Release();
	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;
	virtual void mapRender(HDC map) {};

	void SpecialFunc();
	void CameraWalk();
	void FollowPlayer();

	bool GetIsGameOver() const { return mIsGameOver; }
	void SetIsGameOver(bool isGameOver) { mIsGameOver = isGameOver; }

	bool GetIsGameClear() const { return mIsGameClear; }
	void SetIsGameClear(bool isGameClear) { mIsGameClear = isGameClear; }
};

