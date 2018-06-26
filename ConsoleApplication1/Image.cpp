#include "stdafx.h"
#include "Image.h"


Image::Image() : _imageInfo(NULL), _fileName(NULL), _isTrans(FALSE)
{
}


Image::~Image()
{
}

HRESULT Image::init(int width, int height)
{
	// ���ʱ�ȭ ������, �̹��� ������ ���� ����ִٸ� ��������� ����
	if (_imageInfo != NULL) this->release();

	// DC ��������
	HDC hdc = GetDC(_hWnd);

	// �̹��� ���� ����ü ���� ������ �ʱ�ȭ �ϱ�
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->redID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);	// hdc�� ȣȯ�Ǵ� HDC�� �����Ͽ� hMemDC �ʱ�ȭ
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOldBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	// ���� �̸�
	_fileName = NULL;

	// ����Ű �÷� ����
	_isTrans = FALSE;
	_transColor = RGB(0, 0, 0);

	// ���ҽ� ��µ� �����ϸ� ����
	if (_imageInfo->hBit == 0)
	{
		this->release();
		return E_FAIL;
	}

	// DC �����ϱ�
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT Image::init(DWORD resID, int width, int height, bool isTrans, COLORREF transColor)
{
	// ���ʱ�ȭ ������, �̹��� ������ ���� ����ִٸ� ��������� ����
	if (_imageInfo != NULL) this->release();

	// DC ��������
	HDC hdc = GetDC(_hWnd);

	// �̹��� ���� ����ü ���� ������ �ʱ�ȭ �ϱ�
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_RESOURCE;
	_imageInfo->redID = resID;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);	// hdc�� ȣȯ�Ǵ� HDC�� �����Ͽ� hMemDC �ʱ�ȭ
	_imageInfo->hBit = (HBITMAP)LoadBitmap(_hInstance, MAKEINTRESOURCE(_imageInfo->redID));
	_imageInfo->hOldBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	// ���� �̸�
	_fileName = NULL;

	// ����Ű �÷� ����
	_isTrans = isTrans;
	_transColor = transColor;

	// ���ҽ� ��µ� �����ϸ� ����
	if (_imageInfo->hBit == 0)
	{
		this->release();
		return E_FAIL;
	}

	// DC �����ϱ�
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT Image::init(char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{// ���ʱ�ȭ ������, �̹��� ������ ���� ����ִٸ� ��������� ����
	if (_imageInfo != NULL) this->release();

	// DC ��������
	HDC hdc = GetDC(_hWnd);

	// �̹��� ���� ����ü ���� ������ �ʱ�ȭ �ϱ�
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->redID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);	// hdc�� ȣȯ�Ǵ� HDC�� �����Ͽ� hMemDC �ʱ�ȭ
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOldBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	// ���� �̸�
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	// ����Ű �÷� ����
	_isTrans = isTrans;
	_transColor = transColor;

	// ���ҽ� ��µ� �����ϸ� ����
	if (_imageInfo->hBit == 0)
	{
		this->release();
		return E_FAIL;
	}

	// DC �����ϱ�
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

void Image::release(void)
{
	// �̹��� ������ ���� �ִٸ� ���� ���Ѷ�
	if (_imageInfo != NULL)
	{
		// �̹��� ����
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOldBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		// ������ ����
		SAFE_DELETE(_imageInfo);
		SAFE_DELETE_ARRAY(_fileName);

		// ���� �÷�Ű �ʱ�ȭ
		_isTrans = FALSE;
		_transColor = RGB(0, 0, 0);
	}
}

void Image::render(HDC hdc)
{
}

void Image::render(HDC hdc, int destX, int destY)
{
}
