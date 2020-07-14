#pragma once
#include"DrawComponent.h"

class Object;

class Sprite : public DrawComponent
{
private:
	bool _isFlipX;
	bool _isFillRect;
	bool _isShowRect;
	bool _isCameraAffect;

	bool _isFrame;
	bool _isLoop;
	bool _isPlay;

	int _curFrameX;
	int _curFrameY;

	int _maxFrameX;

	float _count;
	float _FPS;
	float _strokeWidth;

	float _alpha;

	string _imgKey;
	Graphic* _graphic;

	ColorF _color = NULL;
	PIVOT _pivot;

	Vector2 _scale;
	Vector2 _pos;

public:
	Sprite();
	virtual void Init(BOOL isFrame = false, BOOL isLoop = false);
	virtual void Render();
	virtual void Update() override;

	inline void SetFlipX(bool value) { _isFlipX = value; }
	inline void SetFrameX(int frameX) { _curFrameX = frameX; }
	inline void SetFrameY(int frameY) { _curFrameY = frameY; }
	inline void SetFPS(float time) { _FPS = 1.0f / time; }
	inline void SetAlpha(float alpha) { _alpha = alpha; }
	inline void SetStrokeWidth(float strokeWidth) { _strokeWidth = strokeWidth; }
	inline void SetFillRect(bool fillRect) { _isFillRect = fillRect; }
	inline void SetShowRect(bool show) { _isShowRect = show; }
	inline void SetCameraAffect(bool isAffect) { _isCameraAffect = isAffect; }
	inline void SetSize(Vector2(scale)) { _scale = scale; }
	inline void SetPosition(Vector2(pos)) { _pos = pos; }

	inline string GetImgKey() { return _imgKey; }
	inline float GetAlpha() { return _alpha; }
	inline bool GetFlipX() { return _isFlipX; }
	inline bool GetFillRect() { return _isFillRect; }
	inline bool GetShowRect() { return _isShowRect; }
	inline bool GetCameraAffect() { return _isCameraAffect; }
	inline Vector2 GetSize() { return _scale; }
	inline Vector2 GetPosition() { return _pos; }
	inline int GetCurrentFrameX() { return _curFrameX; }
	inline int GetCurrentFrameY() { return _curFrameY; }
	inline int GetMaxFrameX() { return _maxFrameX; }

	void Start();
	void Stop();
	void Pause();
	void Resume();
	void PlayAnimation();

	void SetImgName(string key);
	void SetMaxFrameX(int maxFrameX) { _maxFrameX = maxFrameX - 1; }
	inline void SetRectColor(ColorF color) { _color = color; }
	inline void SetPivot(PIVOT pivot) { _pivot = pivot; }
	void SetIsFrame(bool isFrame) { _isFrame = isFrame; }
	void SetIsLoop(bool isLoop) { _isLoop = isLoop; }


	bool IsFrameEnd();
	inline Graphic* GetGraphic() { return _graphic; }
};