#pragma once

enum PIVOT
{
	LEFT_TOP,
	CENTER,
	BOTTOM,
	RIGHT_BOTTOM,
	LEFT_BOTTOM,
	TOP,
};

class Graphic
{
private:
	static ID2D1HwndRenderTarget* _RT;

public:
	static void SetRendertarget();

public:
	typedef struct tagGraphicInfo
	{
		ID2D1Bitmap*				bitmap;
		Vector2						size;
		Vector2						scale;
		float						angle;
		float						alpha;
		int							frameWidth;
		int							frameHeight;
		int							maxFrameX;
		int							maxFrameY;
		int							curFrameX;
		int							curFrameY;
		string						imgKey;
		wstring						imgPath;
		bool						isFlipX;
		bool						isCameraAffect;

		tagGraphicInfo()
		{
			bitmap = nullptr;
			size = Vector2(1.0f, 1.0f);
			scale = Vector2(1.0f, 1.0f);
			angle = 0.0f;
			alpha = 1.0f;
			frameWidth = 0;
			frameHeight = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			curFrameX = 0;
			curFrameY = 0;
			isFlipX = false;
		}
	}GRAPHIC_INFO, *LPGRAPHIC_INFO;

private:
	LPGRAPHIC_INFO					_graphicInfo;

	vector<WICRect>					_vFrameRect;
	vector<WICRect>::iterator		_viFrameRect;

public:
	Graphic() {};
	~Graphic() {};

	HRESULT Init(ID2D1Bitmap* bitmap, string key, wstring path);
	HRESULT Init(ID2D1Bitmap* bitmap, string key, wstring path, int maxFrameX, int maxFrameY);
	void Release();
	//void Render(float x, float y);
	void Render(float x, float y, PIVOT pivot = PIVOT::CENTER);
	void Render(Vector2 pos, float alpha = 1.0f, PIVOT pivot = PIVOT::CENTER, bool cameraAffect = true);
	void Render(Vector2 pos, Vector2 scale, float angle, bool flipX = false, float alpha = 1.0f, PIVOT pivot = PIVOT::CENTER, bool cameraAffect = true);
	void RenderUI(float x, float y, PIVOT pivot = PIVOT::CENTER);
	void RenderUI(Vector2 pos, PIVOT pivot = PIVOT::CENTER);
	void FrameRender(float x, float y, int curFrameX, int curFrameY, PIVOT pivot = PIVOT::CENTER);
	void FrameRender(Vector2 pos, int curFrameX, int curFrameY, float alpha = 1.0f, PIVOT pivot = PIVOT::CENTER, bool cameraAffect = true);
	void FrameRender(Vector2 pos, int curFrameX, int curFrameY, Vector2 scale, float angle, bool flipX = false, float alpha = 1.0f, PIVOT pivot = PIVOT::CENTER, bool cameraAffect = true);

	void SetFlipX(bool isFlip) { _graphicInfo->isFlipX = isFlip; }
	void SetSize(Vector2 size);// { _graphicInfo->size = size; }
	//void SetFrameWidth(float w) { _graphicInfo->frameWidth = w; }
	//void SetFrameHeight(float h) { _graphicInfo->frameHeight = h; }

	void SetFrameSize(Vector2 size); //{ Vector2(_graphicInfo->frameWidth, _graphicInfo->frameHeight) = size; }

	void SetAngle(float angle) { _graphicInfo->angle = angle; }
	void SetScale(Vector2 scale) { _graphicInfo->scale = scale; }
	void SetAlpha(float alpha) { _graphicInfo->alpha = alpha; }
	void SetCameraAffect(bool affect) { _graphicInfo->isCameraAffect = affect; }

	void SetCurrentFrameX(int frame) { _graphicInfo->curFrameX = frame; }
	void SetCurrentFrameY(int frame) { _graphicInfo->curFrameY = frame; }

	bool GetFlipX() { return _graphicInfo->isFlipX; }
	UINT GetWidth() { return _graphicInfo->size.x; }
	UINT GetHeight() { return _graphicInfo->size.y; }
	Vector2 GetFrameSize(int frame) { return Vector2(_vFrameRect[frame].Width, _vFrameRect[frame].Height); }

	int GetMaxFrameX() { return _graphicInfo->maxFrameX - 1; }
	int GetMaxFrameY() { return _graphicInfo->maxFrameY - 1; }

	int GetCurrentFrameX() { return _graphicInfo->curFrameX; }
	int GetCurrentFrameY() { return _graphicInfo->curFrameY; }

	int GetFrameWidth() { return _graphicInfo->frameWidth; }
	int GetFrameHeight() { return _graphicInfo->frameHeight; }

	LPGRAPHIC_INFO GetGraphicInfo() { return _graphicInfo; }

	string GetImageKey() { return _graphicInfo->imgKey; }
};
