#include "stdafx.h"
#include "Graphic.h"

ID2D1HwndRenderTarget* Graphic::_RT = nullptr;

void Graphic::SetRendertarget()
{
	assert(_RT == nullptr);
	_RT = GRAPHICMANAGER->GetRenderTarget();
}

HRESULT Graphic::Init(ID2D1Bitmap* bitmap, string key, wstring path)
{
	_graphicInfo = new GRAPHIC_INFO;
	_graphicInfo->bitmap = bitmap;

	_graphicInfo->imgKey = key;
	_graphicInfo->imgPath = path;

	_graphicInfo->size.x = (int)_graphicInfo->bitmap->GetPixelSize().width;
	_graphicInfo->size.y = (int)_graphicInfo->bitmap->GetPixelSize().height;

	_graphicInfo->scale = Vector2(1.0f, 1.0f);
	_graphicInfo->alpha = 1.0f;
	_graphicInfo->angle = 0.0f;

	_graphicInfo->frameWidth = _graphicInfo->size.x;
	_graphicInfo->frameHeight = _graphicInfo->size.y;

	if (_graphicInfo->bitmap == nullptr)
	{
		Release();
		return E_FAIL;
	}

	return S_OK;
}

HRESULT Graphic::Init(ID2D1Bitmap * bitmap, string key, wstring path, int maxFrameX, int maxFrameY)
{
	if (_graphicInfo != nullptr) Release();

	_graphicInfo = new GRAPHIC_INFO;
	_graphicInfo->bitmap = bitmap;

	_graphicInfo->imgKey = key;
	_graphicInfo->imgPath = path;

	_graphicInfo->size.x = (int)_graphicInfo->bitmap->GetPixelSize().width;
	_graphicInfo->size.y = (int)_graphicInfo->bitmap->GetPixelSize().height;

	_graphicInfo->scale = Vector2(1.0f, 1.0f);
	_graphicInfo->alpha = 1.0f;
	_graphicInfo->angle = 0.0f;
	_graphicInfo->frameWidth = _graphicInfo->size.x / maxFrameX;
	_graphicInfo->frameHeight = _graphicInfo->size.y / maxFrameY;
	_graphicInfo->maxFrameX = maxFrameX;
	_graphicInfo->maxFrameY = maxFrameY;
	_graphicInfo->curFrameX = 0;
	_graphicInfo->curFrameY = 0;

	if (_graphicInfo->bitmap == nullptr)
	{
		Release();
		return E_FAIL;
	}

	WICRect rc;
	for (int i = 0; i < _graphicInfo->maxFrameY; ++i)
	{
		for (int j = 0; j < _graphicInfo->maxFrameX; ++j)
		{
			rc.X = _graphicInfo->frameWidth * j;
			rc.Y = _graphicInfo->frameHeight * i;
			rc.Width = _graphicInfo->frameWidth;
			rc.Height = _graphicInfo->frameHeight;
			_vFrameRect.push_back(rc);
		}
	}

	return S_OK;
}

void Graphic::Release()
{
	if (_graphicInfo)
	{
		_graphicInfo->bitmap->Release();
		_graphicInfo->bitmap = nullptr;
	}
}

void Graphic::Render(float x, float y, PIVOT pivot)
{
	_graphicInfo->size.x *= _graphicInfo->scale.x;
	_graphicInfo->size.y *= _graphicInfo->scale.y;

	Matrix3x2F rotation = Matrix3x2F::Rotation(_graphicInfo->angle, Point2F());
	Matrix3x2F trans = Matrix3x2F::Translation(x, y);

	D2D1_RECT_F dxArea;

	switch (pivot)
	{
	case LEFT_TOP:
		dxArea = RectF(0, 0, _graphicInfo->size.x, _graphicInfo->size.y);
		break;
	case CENTER:
		dxArea = RectF(-_graphicInfo->size.x / 2, -_graphicInfo->size.y / 2, _graphicInfo->size.x / 2, _graphicInfo->size.y / 2);
		break;
	case TOP:
		dxArea = RectF(-_graphicInfo->size.x / 2, 0, _graphicInfo->size.x / 2, _graphicInfo->size.y);
		break;
	case BOTTOM:
		dxArea = RectF(-_graphicInfo->size.x / 2, -_graphicInfo->size.y, _graphicInfo->size.x / 2, 0);
		break;
	case RIGHT_BOTTOM:
		dxArea = RectF(-_graphicInfo->size.x, -_graphicInfo->size.y, 0, 0);
		break;
	case LEFT_BOTTOM:
		dxArea = RectF(0, -_graphicInfo->size.y, _graphicInfo->size.x, 0);
		break;
	}

	_RT->SetTransform(Matrix3x2F::Identity() * rotation * trans* CAMERA->GetMatrix());
	if (_graphicInfo->bitmap) _RT->DrawBitmap(_graphicInfo->bitmap, dxArea, _graphicInfo->alpha);
}

void Graphic::Render(Vector2 pos, float alpha, PIVOT pivot, bool cameraAffect)
{
	_graphicInfo->size.x *= _graphicInfo->scale.x;
	_graphicInfo->size.y *= _graphicInfo->scale.y;

	Matrix3x2F sacle = Matrix3x2F::Scale(1, 1);
	Matrix3x2F rotation = Matrix3x2F::Rotation(_graphicInfo->angle, Point2F());
	Matrix3x2F trans = Matrix3x2F::Translation(pos.x, pos.y);

	D2D1_RECT_F dxArea;

	switch (pivot)
	{
	case LEFT_TOP:
		dxArea = RectF(0, 0, _graphicInfo->size.x, _graphicInfo->size.y);
		break;
	case CENTER:
		dxArea = RectF(-_graphicInfo->size.x / 2, -_graphicInfo->size.y / 2, _graphicInfo->size.x / 2, _graphicInfo->size.y / 2);
		break;
	case TOP:
		dxArea = RectF(-_graphicInfo->size.x / 2, 0, _graphicInfo->size.x / 2, _graphicInfo->size.y);
		break;
	case BOTTOM:
		dxArea = RectF(-_graphicInfo->size.x / 2, -_graphicInfo->size.y, _graphicInfo->size.x / 2, 0);
		break;
	case RIGHT_BOTTOM:
		dxArea = RectF(-_graphicInfo->size.x, -_graphicInfo->size.y, 0, 0);
		break;
	case LEFT_BOTTOM:
		dxArea = RectF(0, -_graphicInfo->size.y, _graphicInfo->size.x, 0);
		break;
	}

	_RT->SetTransform(sacle * rotation * trans);
	if (cameraAffect) _RT->SetTransform(sacle * rotation * trans * CAMERA->GetMatrix());

	if (_graphicInfo->bitmap) _RT->DrawBitmap(_graphicInfo->bitmap, dxArea, alpha);
}

void Graphic::Render(Vector2 pos, Vector2 scale, float angle, bool flipX, float alpha, PIVOT pivot, bool cameraAffect)
{
	// 20200117 �̷��� ũ�� �������� ����� ����..!
	_graphicInfo->size.x = scale.x;
	_graphicInfo->size.y = scale.y;

	Matrix3x2F scale_ = Matrix3x2F::Scale(1, 1);

	// 20200117 TODO : Flip���� ��ƺ���
	if (flipX) scale_ = scale_ * Matrix3x2F::Scale(-1, 1);

	//Matrix3x2F scale_ = Matrix3x2F::Identity();
	//scale_ = Matrix3x2F::Scale(scale.x, scale.y);
	//if (_isFlip) scale_ = Matrix3x2F::Scale(-1, 1);

	// 20200106 MUST TODO : scale ����..
	//D2D1_MATRIX_3X2_F scale_ = Matrix3x2F::Identity();
	//Matrix3x3* size = new Matrix3x3(scale.x, 0,		0,
	//								   0, scale.y,	0,
	//								   0,	 0,		1);
	//
	//scale_ = scale_ * size->To_D2D1_Matrix_3x2_F() * Matrix3x2F::Scale(0.01f, 0.01f);
	//scale_ = scale_ * size->To_D2D1_Matrix_3x2_F();// *Matrix3x2F::Scale(1 / scale.x, 1 / scale.y);
	//if (_isFlip) scale_ = Matrix3x2F::Scale(-scale.x, scale.y);

	Matrix3x2F rotation = Matrix3x2F::Rotation(angle, Point2F());
	Matrix3x2F trans = Matrix3x2F::Translation(pos.x, pos.y);

	D2D1_RECT_F dxArea;

	switch (pivot)
	{
	case LEFT_TOP:
		dxArea = RectF(0, 0, _graphicInfo->size.x, _graphicInfo->size.y);
		break;
	case CENTER:
		dxArea = RectF(-_graphicInfo->size.x / 2, -_graphicInfo->size.y / 2, _graphicInfo->size.x / 2, _graphicInfo->size.y / 2);
		break;
	case TOP:
		dxArea = RectF(-_graphicInfo->size.x / 2, 0, _graphicInfo->size.x / 2, _graphicInfo->size.y);
		break;
	case BOTTOM:
		dxArea = RectF(-_graphicInfo->size.x / 2, -_graphicInfo->size.y, _graphicInfo->size.x / 2, 0);
		break;
	case RIGHT_BOTTOM:
		dxArea = RectF(-_graphicInfo->size.x, -_graphicInfo->size.y, 0, 0);
		break;
	case LEFT_BOTTOM:
		dxArea = RectF(0, -_graphicInfo->size.y, _graphicInfo->size.x, 0);
		break;
	}

	_RT->SetTransform(scale_ * rotation * trans);
	if (cameraAffect) _RT->SetTransform(scale_ * rotation * trans * CAMERA->GetMatrix());
	//_RT->SetTransform(Matrix3x2F::Identity() * rotation * trans * CAMERA->GetMatrix());
	if (_graphicInfo->bitmap) _RT->DrawBitmap(_graphicInfo->bitmap, dxArea, alpha);
}

void Graphic::RenderUI(float x, float y, PIVOT pivot)
{
	_graphicInfo->size.x *= _graphicInfo->scale.x;
	_graphicInfo->size.y *= _graphicInfo->scale.y;

	Matrix3x2F rotation = Matrix3x2F::Rotation(_graphicInfo->angle, Point2F());
	Matrix3x2F trans = Matrix3x2F::Translation(x, y);

	D2D1_RECT_F dxArea;

	switch (pivot)
	{
	case LEFT_TOP:
		dxArea = RectF(0, 0, _graphicInfo->size.x, _graphicInfo->size.y);
		break;
	case CENTER:
		dxArea = RectF(-_graphicInfo->size.x / 2, -_graphicInfo->size.y / 2, _graphicInfo->size.x / 2, _graphicInfo->size.y / 2);
		break;
	case TOP:
		dxArea = RectF(-_graphicInfo->size.x / 2, 0, _graphicInfo->size.x / 2, _graphicInfo->size.y);
		break;
	case BOTTOM:
		dxArea = RectF(-_graphicInfo->size.x / 2, -_graphicInfo->size.y, _graphicInfo->size.x / 2, 0);
		break;
	case RIGHT_BOTTOM:
		dxArea = RectF(-_graphicInfo->size.x, -_graphicInfo->size.y, 0, 0);
		break;
	case LEFT_BOTTOM:
		dxArea = RectF(0, -_graphicInfo->size.y, _graphicInfo->size.x, 0);
		break;
	}

	_RT->SetTransform(Matrix3x2F::Identity() * rotation * trans);
	if (_graphicInfo->bitmap) _RT->DrawBitmap(_graphicInfo->bitmap, dxArea, _graphicInfo->alpha);
}

void Graphic::RenderUI(Vector2 pos, PIVOT pivot)
{
	_graphicInfo->size.x *= _graphicInfo->scale.x;
	_graphicInfo->size.y *= _graphicInfo->scale.y;

	Matrix3x2F rotation = Matrix3x2F::Rotation(_graphicInfo->angle, Point2F());
	Matrix3x2F trans = Matrix3x2F::Translation(pos.x, pos.y);

	D2D1_RECT_F dxArea;

	switch (pivot)
	{
	case LEFT_TOP:
		dxArea = RectF(0, 0, _graphicInfo->size.x, _graphicInfo->size.y);
		break;
	case CENTER:
		dxArea = RectF(-_graphicInfo->size.x / 2, -_graphicInfo->size.y / 2, _graphicInfo->size.x / 2, _graphicInfo->size.y / 2);
		break;
	case TOP:
		dxArea = RectF(-_graphicInfo->size.x / 2, 0, _graphicInfo->size.x / 2, _graphicInfo->size.y);
		break;
	case BOTTOM:
		dxArea = RectF(-_graphicInfo->size.x / 2, -_graphicInfo->size.y, _graphicInfo->size.x / 2, 0);
		break;
	case RIGHT_BOTTOM:
		dxArea = RectF(-_graphicInfo->size.x, -_graphicInfo->size.y, 0, 0);
		break;
	case LEFT_BOTTOM:
		dxArea = RectF(0, -_graphicInfo->size.y, _graphicInfo->size.x, 0);
		break;
	}

	_RT->SetTransform(Matrix3x2F::Identity() * rotation * trans);
	if (_graphicInfo->bitmap) _RT->DrawBitmap(_graphicInfo->bitmap, dxArea, _graphicInfo->alpha);
}

void Graphic::FrameRender(float x, float y, int curFrameX, int curFrameY, PIVOT pivot)
{
	_graphicInfo->curFrameX = curFrameX;
	_graphicInfo->curFrameY = curFrameY;


	if (_graphicInfo->curFrameX > _graphicInfo->maxFrameX - 1) _graphicInfo->curFrameX = _graphicInfo->maxFrameX - 1;
	if (_graphicInfo->curFrameY > _graphicInfo->maxFrameY - 1) _graphicInfo->curFrameY = _graphicInfo->maxFrameY - 1;

	int frame = _graphicInfo->curFrameY * _graphicInfo->maxFrameX + _graphicInfo->curFrameX;

	_graphicInfo->size = GetFrameSize(frame);

	_graphicInfo->size.x *= _graphicInfo->scale.x;
	_graphicInfo->size.y *= _graphicInfo->scale.y;

	Matrix3x2F rotation = Matrix3x2F::Rotation(_graphicInfo->angle, Point2F());
	Matrix3x2F trans = Matrix3x2F::Translation(x, y);

	D2D1_RECT_F dxArea;

	switch (pivot)
	{
	case LEFT_TOP:
		dxArea = RectF(0, 0, _graphicInfo->size.x, _graphicInfo->size.y);
		break;
	case CENTER:
		dxArea = RectF(-_graphicInfo->size.x / 2, -_graphicInfo->size.y / 2, _graphicInfo->size.x / 2, _graphicInfo->size.y / 2);
		break;
	case TOP:
		dxArea = RectF(-_graphicInfo->size.x / 2, 0, _graphicInfo->size.x / 2, _graphicInfo->size.y);
		break;
	case BOTTOM:
		dxArea = RectF(-_graphicInfo->size.x / 2, -_graphicInfo->size.y, _graphicInfo->size.x / 2, 0);
		break;
	case RIGHT_BOTTOM:
		dxArea = RectF(-_graphicInfo->size.x, -_graphicInfo->size.y, 0, 0);
		break;
	case LEFT_BOTTOM:
		dxArea = RectF(0, -_graphicInfo->size.y, _graphicInfo->size.x, 0);
		break;
	}


	D2D1_RECT_F dxSrc = RectF(_vFrameRect[frame].X, _vFrameRect[frame].Y, _vFrameRect[frame].X + _vFrameRect[frame].Width, _vFrameRect[frame].Y + _vFrameRect[frame].Height);

	_RT->SetTransform(Matrix3x2F::Identity() * rotation * trans* CAMERA->GetMatrix());

	if (_graphicInfo->bitmap) _RT->DrawBitmap(_graphicInfo->bitmap, dxArea, _graphicInfo->alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, dxSrc);
}

void Graphic::FrameRender(Vector2 pos, int curFrameX, int curFrameY, float alpha, PIVOT pivot, bool cameraAffect)
{
	_graphicInfo->curFrameX = curFrameX;
	_graphicInfo->curFrameY = curFrameY;

	if (_graphicInfo->curFrameX > _graphicInfo->maxFrameX - 1) _graphicInfo->curFrameX = _graphicInfo->maxFrameX - 1;
	if (_graphicInfo->curFrameY > _graphicInfo->maxFrameY - 1) _graphicInfo->curFrameY = _graphicInfo->maxFrameY - 1;

	int frame = _graphicInfo->curFrameY * _graphicInfo->maxFrameX + _graphicInfo->curFrameX;

	_graphicInfo->size = GetFrameSize(frame);

	_graphicInfo->size.x *= _graphicInfo->scale.x;
	_graphicInfo->size.y *= _graphicInfo->scale.y;

	Matrix3x2F scale;
	scale = Matrix3x2F::Scale(1, 1);
	if (_graphicInfo->isFlipX) scale = Matrix3x2F::Scale(-1, 1);
	Matrix3x2F rotation = Matrix3x2F::Rotation(_graphicInfo->angle, Point2F());
	Matrix3x2F trans = Matrix3x2F::Translation(pos.x, pos.y);

	D2D1_RECT_F dxArea;

	switch (pivot)
	{
	case LEFT_TOP:
		dxArea = RectF(0, 0, _graphicInfo->size.x, _graphicInfo->size.y);
		break;
	case CENTER:
		dxArea = RectF(-_graphicInfo->size.x / 2, -_graphicInfo->size.y / 2, _graphicInfo->size.x / 2, _graphicInfo->size.y / 2);
		break;
	case TOP:
		dxArea = RectF(-_graphicInfo->size.x / 2, 0, _graphicInfo->size.x / 2, _graphicInfo->size.y);
		break;
	case BOTTOM:
		dxArea = RectF(-_graphicInfo->size.x / 2, -_graphicInfo->size.y, _graphicInfo->size.x / 2, 0);
		break;
	case RIGHT_BOTTOM:
		dxArea = RectF(-_graphicInfo->size.x, -_graphicInfo->size.y, 0, 0);
		break;
	case LEFT_BOTTOM:
		dxArea = RectF(0, -_graphicInfo->size.y, _graphicInfo->size.x, 0);
		break;
	}

	D2D1_RECT_F dxSrc = RectF(_vFrameRect[frame].X, _vFrameRect[frame].Y, _vFrameRect[frame].X + _vFrameRect[frame].Width, _vFrameRect[frame].Y + _vFrameRect[frame].Height);
	int a = 10;
	//D2D1_MATRIX_3X2_F cameraMatrix;
	//cameraMatrix = Matrix3x2F::Scale(D2D1::SizeF(1, 1));
	//cameraMatrix = cameraMatrix * Matrix3x2F::Rotation(0);
	//cameraMatrix = cameraMatrix * Matrix3x2F::Translation(100, 100);

	//Matrix3x2F::in // �����

	//_RT->SetTransform(Matrix3x2F::Identity() * rotation * trans * cameraMatrix);

	//_RT->SetTransform(Matrix3x2F::Identity() * rotation * trans * CAMERA->GetMatrix());
	_RT->SetTransform(scale * rotation * trans);
	if (cameraAffect) _RT->SetTransform(scale * rotation * trans * CAMERA->GetMatrix());

	if (_graphicInfo->bitmap) _RT->DrawBitmap(_graphicInfo->bitmap, dxArea, alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, dxSrc);
}

void Graphic::FrameRender(Vector2 pos, int curFrameX, int curFrameY, Vector2 scale, float angle, bool flipX, float alpha, PIVOT pivot, bool cameraAffect)
{
#pragma region Origin
	//_graphicInfo->curFrameX = curFrameX;
	//_graphicInfo->curFrameY = curFrameY;
	//
	//if (_graphicInfo->curFrameX > _graphicInfo->maxFrameX - 1) _graphicInfo->curFrameX = _graphicInfo->maxFrameX - 1;
	//if (_graphicInfo->curFrameY > _graphicInfo->maxFrameY - 1) _graphicInfo->curFrameY = _graphicInfo->maxFrameY - 1;
	//
	//int frame = _graphicInfo->curFrameY * _graphicInfo->maxFrameX + _graphicInfo->curFrameX;
	//
	//// TODO : �̹��� ũ�� ����
	//_graphicInfo->size.x = scale.x;
	//_graphicInfo->size.y = scale.y;
	//
	//_vFrameRect.clear();
	//
	//WICRect rc;
	//for (int i = 0; i < _graphicInfo->maxFrameY; ++i)
	//{
	//	for (int j = 0; j < _graphicInfo->maxFrameX; ++j)
	//	{
	//		rc.X = _graphicInfo->frameWidth * j;
	//		rc.Y = _graphicInfo->frameHeight * i;
	//		rc.Width = _graphicInfo->frameWidth;
	//		rc.Height = _graphicInfo->frameHeight;
	//		_vFrameRect.push_back(rc);
	//	}
	//}
	//
	//_graphicInfo->size = GetFrameSize(frame);
	//
	//Matrix3x2F scale_;
	//scale_ = Matrix3x2F::Scale(1, 1);
	//if (flipX) scale_ = scale_ * Matrix3x2F::Scale(-1, 1);
	//Matrix3x2F rotation = Matrix3x2F::Rotation(angle, Point2F());
	//Matrix3x2F trans = Matrix3x2F::Translation(pos.x, pos.y);
	//
	//D2D1_RECT_F dxArea;
	//
	//switch (pivot)
	//{
	//case LEFT_TOP:
	//	dxArea = RectF(0, 0, _graphicInfo->size.x, _graphicInfo->size.y);
	//	break;
	//case CENTER:
	//	dxArea = RectF(-_graphicInfo->size.x / 2, -_graphicInfo->size.y / 2, _graphicInfo->size.x / 2, _graphicInfo->size.y / 2);
	//	break;
	//case TOP:
	//	dxArea = RectF(-_graphicInfo->size.x / 2, 0, _graphicInfo->size.x / 2, _graphicInfo->size.y);
	//	break;
	//case BOTTOM:
	//	dxArea = RectF(-_graphicInfo->size.x / 2, -_graphicInfo->size.y, _graphicInfo->size.x / 2, 0);
	//	break;
	//case RIGHT_BOTTOM:
	//	dxArea = RectF(-_graphicInfo->size.x, -_graphicInfo->size.y, 0, 0);
	//	break;
	//case LEFT_BOTTOM:
	//	dxArea = RectF(0, -_graphicInfo->size.y, _graphicInfo->size.x, 0);
	//	break;
	//}
	//
	//D2D1_RECT_F dxSrc = RectF(_vFrameRect[frame].X, _vFrameRect[frame].Y, _vFrameRect[frame].X + _vFrameRect[frame].Width, _vFrameRect[frame].Y + _vFrameRect[frame].Height);
	//
	//_RT->SetTransform(scale_ * rotation * trans);
	//if (cameraAffect) _RT->SetTransform(scale_ * rotation * trans * CAMERA->GetMatrix());
	//if (_graphicInfo->bitmap) _RT->DrawBitmap(_graphicInfo->bitmap, &dxArea, alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &dxSrc);
#pragma endregion

	_graphicInfo->curFrameX = curFrameX;
	_graphicInfo->curFrameY = curFrameY;

	if (_graphicInfo->curFrameX > _graphicInfo->maxFrameX - 1) _graphicInfo->curFrameX = _graphicInfo->maxFrameX - 1;
	if (_graphicInfo->curFrameY > _graphicInfo->maxFrameY - 1) _graphicInfo->curFrameY = _graphicInfo->maxFrameY - 1;

	int frame = _graphicInfo->curFrameY * _graphicInfo->maxFrameX + _graphicInfo->curFrameX;

	// TODO : �̹��� ũ�� ����
	_graphicInfo->size.x = scale.x;
	_graphicInfo->size.y = scale.y;

	if (_graphicInfo->imgKey.compare("will_dungeon") == 0)
	{
		cout << "size x_1 : " << _graphicInfo->size.x << endl;
		cout << "size y_1 : " << _graphicInfo->size.y << endl << endl;
	}

	_graphicInfo->frameWidth = _graphicInfo->size.x / _graphicInfo->maxFrameX;
	_graphicInfo->frameHeight = _graphicInfo->size.y / _graphicInfo->maxFrameY;

	//_graphicInfo->size = GetFrameSize(frame);
	_graphicInfo->size = Vector2(_graphicInfo->frameWidth, _graphicInfo->frameHeight);

	if (_graphicInfo->imgKey.compare("will_dungeon") == 0)
	{
		cout << "size x : " << _graphicInfo->size.x << endl;
		cout << "size y : " << _graphicInfo->size.y << endl << endl;
	}

	Matrix3x2F scale_;
	scale_ = Matrix3x2F::Scale(1,1);
	if (flipX) scale_ = scale_ * Matrix3x2F::Scale(-1, 1);
	Matrix3x2F rotation = Matrix3x2F::Rotation(angle, Point2F());
	Matrix3x2F trans = Matrix3x2F::Translation(pos.x, pos.y);

	D2D1_RECT_F dxArea;

	switch (pivot)
	{
	case LEFT_TOP:
		dxArea = RectF(0, 0, _graphicInfo->size.x, _graphicInfo->size.y);
		break;
	case CENTER:
		dxArea = RectF(-_graphicInfo->size.x / 2, -_graphicInfo->size.y / 2, _graphicInfo->size.x / 2, _graphicInfo->size.y / 2);
		break;
	case TOP:
		dxArea = RectF(-_graphicInfo->size.x / 2, 0, _graphicInfo->size.x / 2, _graphicInfo->size.y);
		break;
	case BOTTOM:
		dxArea = RectF(-_graphicInfo->size.x / 2, -_graphicInfo->size.y, _graphicInfo->size.x / 2, 0);
		break;
	case RIGHT_BOTTOM:
		dxArea = RectF(-_graphicInfo->size.x, -_graphicInfo->size.y, 0, 0);
		break;
	case LEFT_BOTTOM:
		dxArea = RectF(0, -_graphicInfo->size.y, _graphicInfo->size.x, 0);
		break;
	}

	//D2D1_RECT_F dxSrc = RectF(_vFrameRect[frame].X, _vFrameRect[frame].Y, _vFrameRect[frame].X + _vFrameRect[frame].Width, _vFrameRect[frame].Y + _vFrameRect[frame].Height);
	D2D1_RECT_F dxSrc = RectF(_graphicInfo->curFrameX * _graphicInfo->frameWidth, _graphicInfo->curFrameY * _graphicInfo->frameHeight, 
		_graphicInfo->curFrameX * _graphicInfo->frameWidth + _graphicInfo->frameWidth,
		_graphicInfo->curFrameY * _graphicInfo->frameHeight + _graphicInfo->frameHeight);


	_RT->SetTransform(scale_ * rotation * trans);
	if (cameraAffect) _RT->SetTransform(scale_ * rotation * trans * CAMERA->GetMatrix());
	if (_graphicInfo->bitmap) _RT->DrawBitmap(_graphicInfo->bitmap, &dxArea, alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &dxSrc);
}

void Graphic::SetSize(Vector2 size)
{
	_graphicInfo->size = size;

	//_graphicInfo->frameWidth = size.x / _graphicInfo->maxFrameX;
	//_graphicInfo->frameHeight = size.y / _graphicInfo->maxFrameY;
	//
	//_vFrameRect.clear();
	//
	//WICRect rc;
	//for (int i = 0; i < _graphicInfo->maxFrameY; ++i)
	//{
	//	for (int j = 0; j < _graphicInfo->maxFrameX; ++j)
	//	{
	//		rc.X = _graphicInfo->frameWidth * j;
	//		rc.Y = _graphicInfo->frameHeight * i;
	//		rc.Width = _graphicInfo->frameWidth;
	//		rc.Height = _graphicInfo->frameHeight;
	//		_vFrameRect.push_back(rc);
	//	}
	//}
}

void Graphic::SetFrameSize(Vector2 size)
{
	_graphicInfo->size *= 2;
	WICRect rc;
	//_graphicInfo->scale *= size;

	_graphicInfo->frameWidth = _graphicInfo->size.x / _graphicInfo->maxFrameX;
	_graphicInfo->frameHeight = _graphicInfo->size.y / _graphicInfo->maxFrameY;
	for (int i = 0; i < _graphicInfo->maxFrameY*_graphicInfo->maxFrameX; i++)
	{
		_vFrameRect[i].X = _graphicInfo->frameWidth * i;
		_vFrameRect[i].Y = _graphicInfo->frameHeight * i;
		_vFrameRect[i].Width = _graphicInfo->frameWidth;
		_vFrameRect[i].Height = _graphicInfo->frameHeight;
		int a=10;
	}
}
